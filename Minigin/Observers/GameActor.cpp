//
// Created by omen on 19/03/2026.
//

#include "GameActor.h"

#include "GameObject.h"
#include "IObserver.h"

dae::GameActor::GameActor(dae::GameObject *pOwner)
    : m_pOwner(pOwner)
{

}



dae::GameActor::~GameActor()
{

    m_Observers.clear();
}


void dae::GameActor::AddObserver(IObserver* observer)
{
    if (reinterpret_cast<uintptr_t>(observer) == 0xffffffffffffffff)
    {
        std::cout << "[GameActor] WARNING: AddObserver called with corrupted pointer!\n";
        return;
    }
    if (observer)
        m_Observers.push_back(observer);
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


void dae::GameActor::NotifyObservers(IObserver::Event event)
{

    for (auto observer : m_Observers)
    {
        if (observer)
            observer->Notify(event, this);
    }
}

dae::GameObject * dae::GameActor::GetOwner() const
{
    return m_pOwner;
}
