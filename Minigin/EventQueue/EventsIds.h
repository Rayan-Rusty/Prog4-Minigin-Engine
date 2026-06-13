#ifndef MINIGIN_EVENTSIDS_H
#define MINIGIN_EVENTSIDS_H

#include "Event.h"
#include "EventHash.h"


constexpr dae::EventId PLAYER_DIED   = make_sdbm_hash("PlayerDied");
constexpr dae::EventId LEVEL_STARTED = make_sdbm_hash("LevelStarted");
constexpr dae::EventId MOVED = make_sdbm_hash("Moved");
constexpr dae::EventId MENU_NAVIGATE = make_sdbm_hash("MenuNavigate");
constexpr dae::EventId Player_Moving = make_sdbm_hash("PlayerMoving");
constexpr dae::EventId EnemyDied = make_sdbm_hash("EnemyDied");
constexpr dae::EventId EnemySpawned = make_sdbm_hash("EnemySpawned");
constexpr dae::EventId PressedForwardArrow = make_sdbm_hash("PressedForwardArrow");
constexpr dae::EventId PressedPreviousArrow = make_sdbm_hash("PressedPreviousArrow");
constexpr dae::EventId OnConfirmPressed = make_sdbm_hash("OnConfirmPressed");
constexpr dae::EventId Victory = make_sdbm_hash("Victory");
#endif //MINIGIN_EVENTSIDS_H