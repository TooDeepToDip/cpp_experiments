#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <cassert>
#include <numeric>
#include "../helpers/array_iteration/array_iteration.h"
#include "../helpers/string_helpers/string_helpers.h"

typedef std::vector<std::string> stringvector;

struct internal_checker
{
  internal_checker(size_t sections)
  {
    if(sections == 0)
      throw std::runtime_error("code_edit cannot have 0 sections");
  }
};

namespace section_order
{
  enum Type
  {
    linear
  , cyclic
  };
}

template<typename F>
struct getterStruct
{
  getterStruct(F func) : m_func(func) { }
  template<typename T>
  size_t operator()(size_t base, const T& t)
  {
    return base + (t.*m_func)();
  }
  F m_func;
};

template<typename F>
getterStruct<F> getter(F func)
{
  return getterStruct<F>(func);
}

// TODO refactor here
class code_edit
{
  public:
    code_edit(
        const std::vector<std::string>&
      , const std::string& default_separator = ""
      );
    //void set_default_value(const std::string&);
    void set_separators(const std::vector<std::string>&);
    //void set_sections_order(const std::vector<size_t>&);
    void set_pattern(const stringvector& pattern);
    void reset();
    bool next_section();
    bool next_symbol();
    void set_symbol(char);
    //void set_callback_on_leave_edit_mode();
    //on_leave_edit_mode; callback
    std::string value() const { return string::join(m_value, ""); }
    void set_value(const std::string&);
    std::string format_string() const
    {
      std::stringstream s;
      for(size_t i = 0; i + 1 < m_value.size(); ++i)
      {
        std::string separator = i < m_separators.size() ?
          m_separators[i] :
          "";
        s << m_value[i] << separator;
      }
      if(m_value.size())
        s << m_value[m_value.size() - 1];
      return s.str();
    }
    // TODO fix bugs?
    size_t current_index() const
    {
      typedef stringvector::const_iterator ci;
      ci end = m_value.begin();
      //assert(m_current_section_index < m_value.size());
      //std::cout << m_current_section_index << " " << m_value.size() << std::endl;
      std::advance(end, m_current_section_index);
      size_t res = 0;
      res = std::accumulate(m_value.begin(), end, res, getter(&std::string::size));
      ci s_end = m_separators.begin();
      //std::cout << m_current_section_index << " " << m_separators.size() << std::endl;
      //assert(m_current_section_index < m_separators.size());
      std::advance(s_end, m_current_section_index);
      res = accumulate(m_separators.begin(), s_end, res, getter(&std::string::size));
      res += current_index_internal();
      return res;
    }
  private:
    size_t sections() const { return m_value.size(); }
    size_t current_section() const { return m_current_section_index; }
    bool set_current_section(size_t i)
    {
      if(i < m_value.size())
      {
        m_current_index = 0;
        m_current_section_index = i;
        return true;
      }
      return false;
    }
    size_t current_index_internal() const { return m_current_index; }
    internal_checker m_internal_checker;
    size_t m_current_index;
    bool next_section_internal(section_order::Type t);

    //void set_current_section(size_t i)
    //{
    //  assert(i < m_value.size()
    //      and "Section index is less than value size");
    //  m_current_index = 0;
    //  m_current_section_index = i;
    //}
    size_t m_current_section_index;

    stringvector m_pattern;
    stringvector m_value;
    std::vector<std::string> m_separators;
    std::vector<size_t> m_section_order;
};

code_edit::code_edit(
    const std::vector<std::string>& pattern
  , const std::string& default_separator
    )
  : m_internal_checker(pattern.size())
  , m_current_index(0)
  , m_current_section_index(0)
  , m_pattern(pattern)
  , m_value(pattern)
  , m_separators(pattern.size() - 1, default_separator)
  , m_section_order()
{
}

void code_edit::reset()
{
  m_value = m_pattern;
  set_current_section(0);
}

bool code_edit::next_section()
{
  return next_section_internal(section_order::cyclic);
}

bool code_edit::next_section_internal(section_order::Type t)
{
  assert(m_current_section_index < m_value.size()
      and "Section index is less than value size");
  if(set_current_section(m_current_section_index + 1))
    return true;
  if(section_order::cyclic == t)
  {
    return set_current_section((m_current_section_index + 1)%m_value.size());
  }
  return false;
}

bool code_edit::next_symbol()
{
  assert(m_current_section_index < m_value.size()
      and "Section index is less than value size");
  assert(m_current_index < m_value[m_current_section_index].size()
      and "Symbol index is less than section size");
  if((m_current_index + 1) < m_value[m_current_section_index].size())
    return ++m_current_index;
  else
    return next_section();
}

void code_edit::set_symbol(char c)
{
  assert(m_current_section_index < m_value.size()
      and "Section index is less than value size");
  assert(m_current_index < m_value[m_current_section_index].size()
      and "Symbol index is less than section size");
  m_value[m_current_section_index][m_current_index] = c;
  if(!next_symbol())
    std::cout << "edit is over" << std::endl; //TODO callback to exit from edit mode
}

void code_edit::set_pattern(const stringvector& pattern)
{
  m_pattern = pattern;
  m_value = m_pattern;
}

void code_edit::set_separators(const std::vector<std::string>& separators)
{
  for(size_t i = 0; i < m_separators.size() and i < separators.size(); ++i)
  {
    m_separators[i] = separators[i];
  }
}

void code_edit::set_value(const std::string& val)
{
  m_current_section_index = 0;
  for(std::string::size_type i = 0; i < val.size(); ++i)
  {
    set_symbol(val[i]);
  }
}

int main()
{
  std::string pattern[] = { "00" , "00" };
  namespace h = array_helpers;
  stringvector v(h::begin(pattern), h::end(pattern));
  code_edit editor(v, "-");
  std::cout << "idx: " << editor.current_index() << std::endl;
  editor.set_symbol('4');
  std::cout << "idx: " << editor.current_index() << std::endl;
  editor.set_symbol('2');
  std::cout << "idx: " << editor.current_index() << std::endl;
  editor.set_symbol('1');
  std::cout << "idx: " << editor.current_index() << std::endl;
  editor.set_symbol('0');
  std::cout << "idx: " << editor.current_index() << std::endl;
  editor.set_symbol('8');
  std::cout << "idx: " << editor.current_index() << std::endl;
  std::cout << "editor: '" << editor.value() << "'" << std::endl;
  std::cout << "editor: '" << editor.format_string() << "'" << std::endl;
  code_edit editor2(v, " ");
  std::cout << "idx: " << editor2.current_index() << std::endl;
  editor2.next_section();
  std::cout << "idx: " << editor2.current_index() << std::endl;
  editor2.set_symbol('4');
  std::cout << "idx: " << editor2.current_index() << std::endl;
  editor2.set_symbol('2');
  std::cout << "idx: " << editor2.current_index() << std::endl;
  editor2.set_symbol('1');
  std::cout << "idx: " << editor2.current_index() << std::endl;
  editor2.next_section();
  std::cout << "idx: " << editor2.current_index() << std::endl;
  editor2.set_symbol('0');
  std::cout << "idx: " << editor2.current_index() << std::endl;
  editor2.set_symbol('8');
  std::cout << "idx: " << editor2.current_index() << std::endl;
  std::cout << "editor: '" << editor2.value() << "'" << std::endl;
  std::cout << "editor: '" << editor2.format_string() << "'" << std::endl;
}
