//
// Created by omen on 31/05/2026.
//

#include "PlayerCollisionHandler.h"

DigDug::PlayerCollisionHandler::PlayerCollisionHandler(dae::GameObject *listener)
    : m_pListener(listener)
{
}

void DigDug::PlayerCollisionHandler::Notify(IObserver::Event event, dae::GameActor *)
{
    switch(event)
    {
        case Event::ItemCollected:
            break;

        case Event::ActorHit:
            break;

        case Event::ActorDied:

            break;
    }
}
