#include <string>
#include <FL/Fl.H>
#include "layer.hpp"

std::set<layer*> layer::m_instances;

layer::layer() :
    m_name("N/A")
{
    m_instances.insert(this);
};

layer::~layer()
{
    // Not a valid layer instance anymore
    m_instances.erase(m_instances.find(this));
};

const std::string& layer::name()
{
    return m_name;
};

void layer::name(const std::string &name)
{
    m_name = name;
};

void layer::addobserver(layer_observer &o)
{
    m_observers.insert(&o);
};

void layer::removeobserver(layer_observer &o)
{
    m_observers.erase(&o);
};

void layer::notify_observers()
{
    std::set<layer_observer*>::iterator it;
    for (it = m_observers.begin(); it != m_observers.end(); it++)
        (*it)->layer_notify();
};

bool layer::is_instance(layer* l)
{
    std::set<layer*>::iterator it = m_instances.find(l);
    if (it == m_instances.end())
        return false;

    return true;
}
