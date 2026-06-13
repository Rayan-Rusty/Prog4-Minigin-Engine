
#include "SoundEventListener.h"

#include "EventsIds.h"
#include "ServiceLocator.h"


void dae::SoundEventListener::OnEvent(const Event &e)
{
    switch (e.id)
    {
        case MOVED:
            if (!m_isWalking)
            {
                m_isWalking = true;
                ServiceLocator::get_sound_system().play(1, 0.3f);
            }
            break;
        // case PumpShoot:
        //     ServiceLocator::get_sound_system().play(2, 0.8f);
            break;
        case Victory:
            ServiceLocator::get_sound_system().play(3, 0.5f);
            break;
        case EnemyDied:
            ServiceLocator::get_sound_system().play(4, 0.5f);
            break;
    }
}
