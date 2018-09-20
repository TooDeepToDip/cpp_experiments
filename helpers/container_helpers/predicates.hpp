#ifndef PREDICATES_HPP
#define PREDICATES_HPP

namespace helpers
{
    template<typename T, typename Func>
    struct getValueViaFunc
    {
        getValueViaFunc(const T& id, Func fun)
            : m_id(id)
            , m_fun(fun)
        {}
        template<typename T2>
        bool operator()(const T2& oth)
        {
            return (oth.*m_fun)() == m_id;
        }
        template<typename T2>
        bool operator()(T2* oth)
        {
            return (oth->*m_fun)() == m_id;
        }
    private:
        T m_id;
        Func m_fun;
    };

    template<typename Func, typename T>
    static getValueViaFunc<T, Func>
    getter(Func fun, const T& value)
    {
        return getValueViaFunc<T, Func>(value, fun);
    }
}

#endif /* PREDICATES_HPP */
