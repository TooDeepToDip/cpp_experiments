#include <iostream>
#include <cassert>
#include <list>
#include <memory>

#define PRINT_FN() \
  do \
  { \
    std::cout << __PRETTY_FUNCTION__ << std::endl; \
  } while(0) \

class IApplication;

template<typename T>
class IRepository
{
public:
  virtual bool save(const IApplication&, const T&) { return true; }
  virtual bool load(const IApplication&, const T&) { return true; }
  virtual ~IRepository() {}
};

template<typename T, typename Tag>
class Repository;

struct PostgresTag {};
struct MockTag {};
struct Mock2Tag {};

struct Object
{
  int a;
  int b;
};

std::ostream& operator<<(std::ostream& out, const Object& o)
{
  return out << "{ " << o.a << ", " << o.b << " }";
}

struct AnotherObject
{
  int c;
  int d;
};

std::ostream& operator<<(std::ostream& out, const AnotherObject& o)
{
  return out << "{ " << o.c << ", " << o.d << " }";
}

template<>
class Repository<Object, PostgresTag> : public IRepository<Object>
{
public:
  bool save(const IApplication&, const Object& o)
  {
    PRINT_FN();
    std::cout << o << std::endl;
    return true;
  }

  bool load(const IApplication&, const Object& o)
  {
    PRINT_FN();
    std::cout << o << std::endl;
    return true;
  }
};

template<>
class Repository<AnotherObject, PostgresTag> : public IRepository<AnotherObject>
{
public:
  bool save(const IApplication&, const AnotherObject& o)
  {
    PRINT_FN();
    std::cout << o << std::endl;
    return true;
  }

  bool load(const IApplication&, const AnotherObject& o)
  {
    PRINT_FN();
    std::cout << o << std::endl;
    return true;
  }
};

template<typename T>
class Repository<T, MockTag> : public IRepository<T>
{
public:
  bool save(const IApplication&, const T&)
  {
    PRINT_FN();
    std::cout << "---skip---" << std::endl;
    return true;
  }

  bool load(const IApplication&, const T&)
  {
    PRINT_FN();
    std::cout << "---skip---" << std::endl;
    return true;
  }
};

enum RepositoryType
{
  postgresql
, mock
, tag_size
};

class IApplication {};

class RepositoryManager
{
   struct Base
   {
     virtual void destroy() = 0;
   };

   template <typename T, typename Tag>
   struct Holder
      : Repository<T, Tag>, Base
   {
      void destroy()
      {
        RepositoryManager::shutdown_repo<T>();
      }

      ~Holder()
      {
        RepositoryManager::erase(self);
      }

      std::list<Base*>::iterator self;
    };

  template<typename T>
    static IRepository<T>* & repository_pp()
    {
      static IRepository<T> * p_repo;
      return p_repo;
    }

  template<typename T>
    static IRepository<T> * & repository_pp(IRepository<T> * p)
    {
      IRepository<T> * & p_repo = repository_pp<T>();
      std::swap(p_repo, p);
      delete p;
      return p_repo;
    }

  template<typename T>
    static IRepository<T>& repository()
    {
      IRepository<T> * p_repo = repository_pp<T>();
      assert(p_repo);
      return *p_repo;
    }

    static void erase(std::list<Base*>::iterator it)
    {
      g_holders.erase(it);
    }

public:
  template<typename T, typename Tag>
    static IRepository<T>& initialize_repo()
    {
      std::auto_ptr< Holder<T, Tag> > p(new Holder<T, Tag>);
      g_holders.push_front(p.get());
      p->self = g_holders.begin();
      return *repository_pp<T>(p.release());
    }

  template<typename T>
    static void shutdown_repo()
    {
      repository_pp<T>(NULL);
    }

  static void setDefaultRepository(RepositoryType t)
  {
    assert(t < tag_size);
      g_tag = t;
  }

  static void shutdown_all()
  {
      typedef std::list<Base*>::iterator iterator;

      for(iterator it = g_holders.begin(); it != g_holders.end(); )
      {
          iterator next = it;
          ++next;
          (*it)->destroy();
          it = next;
      }
  }

private:
  template<typename T>
    static IRepository<T>& get_repository()
    {
      if(!repository_pp<T>())
      {
        switch(g_tag)
        {
          case mock: return initialize_repo<T, MockTag>();
          case postgresql:
          default: return initialize_repo<T, PostgresTag>();
        }
      }
      return repository<T>();
    }

public:
  RepositoryManager(const IApplication& app)
    : m_app(app)
  {}

  template<typename T>
    bool save(const T& t)
    {
      return get_repository<T>().save(m_app, t);
    }

  template<typename T>
    bool load(const T& t)
    {
      return get_repository<T>().load(m_app, t);
    }
private:
  const IApplication& m_app;
  static RepositoryType g_tag;
  static std::list<Base *> g_holders;
};

RepositoryType RepositoryManager::g_tag = postgresql;
std::list<RepositoryManager::Base *> RepositoryManager::g_holders;

int main()
{
  IApplication a;

  Object o = { 3, 23 };
  AnotherObject n = { 33, 66 };

  RepositoryManager repo(a);
  repo.save(o);
  repo.save(n);
  RepositoryManager::shutdown_repo<Object>();
  RepositoryManager::shutdown_repo<AnotherObject>();
  RepositoryManager::setDefaultRepository(mock);
  repo.save(o);
  repo.save(n);
  RepositoryManager::initialize_repo<Object, PostgresTag>();
  repo.save(o);
  repo.save(n);
  RepositoryManager::initialize_repo<AnotherObject, PostgresTag>();
  repo.save(o);
  repo.save(n);
  RepositoryManager::initialize_repo<Object, MockTag>();
  RepositoryManager::initialize_repo<AnotherObject, MockTag>();
  repo.save(o);
  repo.save(n);
  RepositoryManager::shutdown_all();
  RepositoryManager::setDefaultRepository(postgresql);
  repo.save(o);
  repo.save(n);
}
