//
// Created by omen on 29/04/2026.
//

#ifndef MINIGIN_EVENTSIDS_H
#define MINIGIN_EVENTSIDS_H

#include "Event.h"
#include "EventHash.h"


constexpr dae::EventId PLAYER_DIED   = make_sdbm_hash("PlayerDied");
constexpr dae::EventId LEVEL_STARTED = make_sdbm_hash("LevelStarted");
constexpr dae::EventId MOVED = make_sdbm_hash("Moved");
constexpr dae::EventId MENU_NAVIGATE = make_sdbm_hash("MenuNavigate");
#endif //MINIGIN_EVENTSIDS_H