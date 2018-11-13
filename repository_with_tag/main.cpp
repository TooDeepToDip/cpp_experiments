#include <iostream>
#include <cassert>
#include <map>

#define PRINT(out, x) \
  do \
  { \
    out << ""#x" = " << x; \
  } while(0)\

#define PRINT_FN() \
  do \
  { \
    std::cout << __PRETTY_FUNCTION__ << std::endl; \
  } while(0) \

class IApplication;

template<typename T>
class Repository
{
public:
  virtual bool save(const IApplication&, const T&) { return true; }
  virtual bool load(const IApplication&, const T&) { return true; }
  virtual ~Repository() {}
};

template<typename T, typename Tag>
class RepositoryTagged;

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
  out << "{ ";
  PRINT(out, o.a);
  out << " ";
  PRINT(out, o.b);
  return out << " }";
}

struct AnotherObject
{
  int c;
  int d;
};

std::ostream& operator<<(std::ostream& out, const AnotherObject& o)
{
  out << "{ ";
  PRINT(out, o.c);
  out << " ";
  PRINT(out, o.d);
  return out << " }";
}

template<>
class RepositoryTagged<Object, PostgresTag> : public Repository<Object>
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
class RepositoryTagged<AnotherObject, PostgresTag> : public Repository<AnotherObject>
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
class RepositoryTagged<T, MockTag> : public Repository<T>
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

class IApplication
{
public:
  template<typename T>
    static Repository<T>** repository_pp()
    {
      static Repository<T>* p_repo = NULL;
      return &p_repo;
    }

  template<typename T>
    static Repository<T>& repository()
    {
      Repository<T>* p_repo = *(repository_pp<T>());
      assert(p_repo);
      return *p_repo;
    }

  template<typename T, typename Tag>
    static Repository<T>& initialize_repo()
    {
      Repository<T>** pp = repository_pp<T>();
      delete *pp;
      *pp = NULL;
      *pp = new RepositoryTagged<T, Tag>;
      return repository<T>();
    }

  template<typename T>
    static Repository<T>& get_repository()
    {
      if(!*(repository_pp<T>()))
        return initialize_repo<T, PostgresTag>();
      return repository<T>();
    }

  template<typename T>
    static bool save(IApplication& a, const T& t)
    {
      return get_repository<T>().save(a, t);
    }

  template<typename T>
    static bool load(IApplication& a, const T& t)
    {
      return get_repository<T>().load(a, t);
    }
};

int main()
{
  IApplication a;

  Object o = { 3, 23 };
  AnotherObject n = { 33, 66 };

  IApplication::save(a, o);
  IApplication::save(a, n);
  IApplication::initialize_repo<Object, MockTag>();
  IApplication::initialize_repo<AnotherObject, MockTag>();
  IApplication::save(a, o);
  IApplication::save(a, n);
  IApplication::initialize_repo<Object, PostgresTag>();
  IApplication::initialize_repo<AnotherObject, PostgresTag>();
  IApplication::save(a, o);
  IApplication::save(a, n);
}
