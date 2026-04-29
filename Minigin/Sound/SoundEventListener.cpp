//
// Created by omen on 29/04/2026.
//

#include "SoundEventListener.h"

#include "../EventQueue/EventsIds.h"
#include "Sound/ServiceLocator.h"


void dae::SoundEventListener::OnEvent(const Event &e)
{
    if (e.id == MOVED)
    {
        ServiceLocator::get_sound_system().play(1, 0.8f);
    }
}
