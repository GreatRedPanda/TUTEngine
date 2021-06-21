#pragma once
#include <map>
#include <string>

#define CONSTRUCT(n) ComponentFactory::construct(#n)
#define REGISTER_CLASS(n) ComponentFactory::register_class<n>(#n)
template <class T> void* constructor() { return (void*)new T(); }
struct ComponentFactory
{

    typedef void* (*constructor_t)();
    typedef std::map<std::string, constructor_t> map_type;
    static   map_type m_classes;
    
    template <class T>
    static   void register_class(std::string const& n)
    {
        m_classes.insert(std::make_pair(n, &constructor<T>));
    }

    static  void* construct(std::string const& n)
    {
        map_type::iterator i = m_classes.find(n);
        if (i == m_classes.end()) return 0; // or throw or whatever you want
        return i->second();
    }

};

