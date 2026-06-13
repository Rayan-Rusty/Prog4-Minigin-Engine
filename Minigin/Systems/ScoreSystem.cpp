
#include "ScoreSystem.h"
#include "EventsIds.h"


void dae::ScoreSystem::OnEvent(const Event &e)
{
    if (e.id == PLAYER_DIED)
    {
        int playerId = 0;
        m_scores[playerId] += 100;
    }
}
