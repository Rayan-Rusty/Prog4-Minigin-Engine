//
// Created by omen on 19/03/2026.
//

#include "GameActor.h"

#include "IObserver.h"


void dae::AddObserver(IObserver* observer)
{

};


void dae::GameActor::RemoveObserver(IObserver *observer)
{

}

void dae::GameActor::NotifyObservers(Event event)
{
    for (auto observer : m_observers)
        observer->Notify(event, this);
}
