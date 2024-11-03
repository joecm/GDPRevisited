#ifndef __SHAREDCONTEXT_H__
#define __SHAREDCONTEXT_H__

#include "Window.hpp"
#include "EventManager.hpp"

struct SharedContext
{
    Window* m_wind;
    EventManager* m_eventManager;
    SharedContext() : m_wind{nullptr}, m_eventManager{nullptr} {}
};


#endif // __SHAREDCONTEXT_H__