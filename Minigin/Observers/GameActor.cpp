//
// Created by omen on 19/03/2026.
//

#include "GameActor.h"

#include "IObserver.h"


void dae::AddObserver(IObserver *observer) {
    m_Observers->push_back(observer);
}

void dae::GameActor::RemoveObserver(IObserver *observer)
{
    m_Observers.erase(
        std::remove(
            m_Observers.begin(),
            m_Observers.end(),
            observer
        ),
        m_Observers.end()
    );
}

void dae::GameActor::NotifyObservers(Event event) {
    for (auto observer: m_Observers)
        observer->Notify(event, this);
}
