#include <iostream>
#include <cassert>
//#include <typeindex> c++11 only
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

class IApplication {};

template<typename T>
class Repository
{
public:
  virtual bool save(const IApplication&, T&) { return true; }
  virtual bool load(const IApplication&, T&) { return true; }
  virtual ~Repository() {}
};

template<typename T, typename Tag>
class RepositoryTagged;

struct PostgresTag {};
struct MockTag {};
struct Mock2Tag {};

enum Tag
{
  postgresql
, mock
};

struct Object
{
  int a;
  int b;
  static void initialize_repo(Tag t);
  static Repository<Object>& repo()
  {
    assert(m_repo);
    return *m_repo;
  }
private:
  static Repository<Object>* m_repo;
};

Repository<Object>* Object::m_repo = NULL;

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
  static void initialize_repo(Tag t);
  static Repository<AnotherObject>& repo()
  {
    assert(m_repo);
    return *m_repo;
  }
private:
  static Repository<AnotherObject>* m_repo;
};

Repository<AnotherObject>* AnotherObject::m_repo = NULL;

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
  bool save(const IApplication&, Object& o)
  {
    PRINT_FN();
    std::cout << o << std::endl;
    return true;
  }

  bool load(const IApplication&, Object& o)
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
  bool save(const IApplication&, AnotherObject& o)
  {
    PRINT_FN();
    std::cout << o << std::endl;
    return true;
  }

  bool load(const IApplication&, AnotherObject& o)
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
  bool save(const IApplication&, T&)
  {
    PRINT_FN();
    std::cout << "---skip---" << std::endl;
    return true;
  }

  bool load(const IApplication&, T&)
  {
    PRINT_FN();
    std::cout << "---skip---" << std::endl;
    return true;
  }
};

void Object::initialize_repo(Tag t)
{
  delete m_repo;
  switch(t)
  {
    case postgresql:  m_repo = new RepositoryTagged<Object, PostgresTag>;
                      break;
    case mock:        m_repo = new RepositoryTagged<Object, MockTag>;
                      break;
    default:          m_repo = NULL;
                      break;
  }
}

void AnotherObject::initialize_repo(Tag t)
{
  delete m_repo;
  switch(t)
  {
    case postgresql:  m_repo = new RepositoryTagged<AnotherObject, PostgresTag>;
                      break;
    case mock:        m_repo = new RepositoryTagged<AnotherObject, MockTag>;
                      break;
    default:          m_repo = NULL;
                      break;
  }
}

int main()
{
  //typedef std::map<std::type_index, Repository<Object>* > TypeRepositoryMap; // c++11 only
  // map for repository type (tag) <-> object repository relation
  //TypeRepositoryMap repo_map;
  IApplication a;
  typedef RepositoryTagged<Object, PostgresTag> PG_Repo;
  typedef RepositoryTagged<Object, MockTag> Mock_Repo;
  PG_Repo pgrepo;
  Mock_Repo mkrepo;

  Object o = { 3, 23 };
  AnotherObject n = { 33, 66 };
  //Repository<Object>* repo = &pgrepo;
  //repo->save(a, o);
  //repo->load(a, o);
  //repo = &mkrepo;
  //repo->save(a, o);
  //repo->load(a, o);
  Object::initialize_repo(mock);
  Object::repo().save(a, o);
  Object::initialize_repo(postgresql);
  Object::repo().save(a, o);
  AnotherObject::initialize_repo(mock);
  AnotherObject::repo().save(a, n);
  AnotherObject::initialize_repo(postgresql);
  AnotherObject::repo().save(a, n);
}
