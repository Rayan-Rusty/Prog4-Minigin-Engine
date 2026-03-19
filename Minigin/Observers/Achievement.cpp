//
// Created by omen on 19/03/2026.
//

#include "Achievement.h"


void dae::Achievement::Notify(Event event, GameActor *actor)
{
    switch (event)
    {
        case Event::ActorDied:
            break;
        case Event::ActorFell:
            break;
    }
}


void dae::Achievement::unlock(Achievement achievement)
{

}