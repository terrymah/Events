#ifndef EVENTS_HEADER
#define EVENTS_HEADER

#include <map>
#ifdef __GNUC__
#include <tr1/functional>
#else
#include <functional>
#endif
#include <algorithm>

namespace mahaffey {
namespace events {

#ifdef __GNUC__

namespace details {
template<typename T>
struct BeMyFriend
{
    typedef T Type;
};
}
#define FRIEND(x) friend class details::BeMyFriend<x>::Type
#else
#define FRIEND(x) friend x
#endif

namespace details {
template<typename T>
void Invoke0(T t)
{
    (t.second)();
}

template<typename T, typename Arg1>
void Invoke1(T t, Arg1 arg1)
{
    (t.second)(arg1);
}

template<typename T, typename Arg1, typename Arg2>
void Invoke2(T t, Arg1 arg1, Arg2 arg2)
{
    (t.second)(arg1, arg2);
}

template<typename T, typename Arg1, typename Arg2, typename Arg3>
void Invoke3(T t, Arg1 arg1, Arg2 arg2, Arg3 arg3)
{
    (t.second)(arg1, arg2, arg3);
}

} // end namespace details

template<typename FunctionType>
class EventN
{
public:
    EventN() : m_key(1) { }
    int Register(FunctionType f) { m_events[m_key] = f; return m_key++; }
    void Unregister(int key) { m_events.erase(key); }

    int operator+=(FunctionType f) { return Register(f); }
    void operator-=(int key) { return Unregister(key); }

protected:
    int m_key;
    std::map<int, FunctionType> m_events;
};

template<class Parent>
class Event0 : public EventN<std::tr1::function<void()> >
{
    FRIEND(Parent);
    void Fire() const;
};

template<typename Parent>
void Event0<Parent>::Fire() const
{
    typedef std::pair<int, std::tr1::function<void()> > elem;
    std::for_each(m_events.begin(), m_events.end(), details::Invoke0<elem>);
}

class PublicEvent0 : public EventN<std::tr1::function<void()> >
{
public:
    void Fire() const;
};

inline void PublicEvent0::Fire() const
{
    typedef std::pair<int, std::tr1::function<void()> > elem;
    std::for_each(m_events.begin(), m_events.end(), details::Invoke0<elem>);
}

template<typename Parent, typename Arg1>
class Event1 : public EventN<std::tr1::function<void(Arg1)> >
{
    FRIEND(Parent);
    void Fire(Arg1 arg1) const;
};

template<typename Parent, typename Arg1>
void Event1<Parent, Arg1>::Fire(Arg1 arg1) const
{
    typedef std::pair<int, std::tr1::function<void(Arg1)> > elem;
    using namespace std::tr1::placeholders;
    std::for_each(this->m_events.begin(), this->m_events.end(), std::tr1::bind(details::Invoke1<elem, Arg1>, _1, arg1));
}

template<typename Arg1>
class PublicEvent1 : public EventN<std::tr1::function<void(Arg1)> >
{
public:
    void Fire(Arg1 arg1) const;
};

template<typename Arg1>
void PublicEvent1<Arg1>::Fire(Arg1 arg1) const
{
    typedef std::pair<int, std::tr1::function<void(Arg1)> > elem;
    using namespace std::tr1::placeholders;
    std::for_each(this->m_events.begin(), this->m_events.end(), std::tr1::bind(details::Invoke1<elem, Arg1>, _1, arg1));
}

template<typename Parent, typename Arg1, typename Arg2>
class Event2 : public EventN<std::tr1::function<void(Arg1, Arg2)> >
{
    FRIEND(Parent);
    void Fire(Arg1 arg1, Arg2 arg2) const;
};

template<typename Parent, typename Arg1, typename Arg2>
void Event2<Parent, Arg1, Arg2>::Fire(Arg1 arg1, Arg2 arg2) const
{
    typedef std::pair<int, std::tr1::function<void(Arg1, Arg2)> > elem;
    using namespace std::tr1::placeholders;
    std::for_each(this->m_events.begin(), this->m_events.end(), std::tr1::bind(details::Invoke2<elem, Arg1, Arg2>, _1, arg1, arg2));
}

template<typename Arg1, typename Arg2>
class PublicEvent2 : public EventN<std::tr1::function<void(Arg1, Arg2)> >
{
public:
    void Fire(Arg1 arg1, Arg2 arg2) const;
};

template<typename Arg1, typename Arg2>
void PublicEvent2<Arg1, Arg2>::Fire(Arg1 arg1, Arg2 arg2) const
{
    typedef std::pair<int, std::tr1::function<void(Arg1, Arg2)> > elem;
    using namespace std::tr1::placeholders;
    std::for_each(this->m_events.begin(), this->m_events.end(), std::tr1::bind(details::Invoke2<elem, Arg1, Arg2>, _1, arg1, arg2));
}

template<typename Parent, typename Arg1, typename Arg2, typename Arg3>
class Event3 : public EventN<std::tr1::function<void(Arg1, Arg2, Arg3)> >
{
    FRIEND(Parent);
    void Fire(Arg1 arg1, Arg2 arg2, Arg3 arg3) const;
};

template<typename Parent, typename Arg1, typename Arg2, typename Arg3>
void Event3<Parent, Arg1, Arg2, Arg3>::Fire(Arg1 arg1, Arg2 arg2, Arg3 arg3) const
{
    typedef std::pair<int, std::tr1::function<void(Arg1, Arg2, Arg3)> > elem;
    using namespace std::tr1::placeholders;
    std::for_each(this->m_events.begin(), this->m_events.end(), std::tr1::bind(details::Invoke3<elem, Arg1, Arg2, Arg3>, _1, arg1, arg2, arg3));
}

template<typename Arg1, typename Arg2, typename Arg3>
class PublicEvent3 : public EventN<std::tr1::function<void(Arg1, Arg2, Arg3)> >
{
public:
    void Fire(Arg1 arg1, Arg2 arg2, Arg3 arg3) const;
};

template<typename Arg1, typename Arg2, typename Arg3>
void PublicEvent3<Arg1, Arg2, Arg3>::Fire(Arg1 arg1, Arg2 arg2, Arg3 arg3) const
{
    typedef std::pair<int, std::tr1::function<void(Arg1, Arg2, Arg3)> > elem;
    using namespace std::tr1::placeholders;
    std::for_each(this->m_events.begin(), this->m_events.end(), std::tr1::bind(details::Invoke3<elem, Arg1, Arg2, Arg3>, _1, arg1, arg2, arg3));
}

}
}

#endif
