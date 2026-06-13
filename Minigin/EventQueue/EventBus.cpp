//
// Created by omen on 29/04/2026.
//

#include "EventBus.h"
#include "Event.h"

void dae::EventBus::AddListener(IEventListener *listener)
{
    m_listeners.push_back(listener);
}

void dae::EventBus::QueueEvent(const Event &e)
{
    m_events.push_back(e);
}

void dae::EventBus::Clear()
{
    m_listeners.clear();
    m_events.clear();
}

void dae::EventBus::ProcessEvents()
{
    for (const auto& e : m_events)
    {
        for (auto* listener : m_listeners)
        {
            listener->OnEvent(e);
        }
    }

    m_events.clear();
}
