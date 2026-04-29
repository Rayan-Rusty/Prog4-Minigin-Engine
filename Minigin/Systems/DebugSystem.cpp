//
// Created by omen on 29/04/2026.
//

#include "../Systems/DebugSystem.h"

#include <iostream>
#include <ostream>

#include "EventQueue/EventsIds.h"


void dae::DebugSystem::OnEvent(const Event &e)
{
    if (e.id == LEVEL_STARTED)
    {
        std::cout << "--------------- level started ---------------" << std::endl;
    }
}
