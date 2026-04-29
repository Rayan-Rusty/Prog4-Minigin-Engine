//
// Created by omen on 29/04/2026.
//
#include "ServiceLocator.h"
#include "null_sound_system.h"

std::unique_ptr<dae::SoundSystem> dae::ServiceLocator::_ss_instance =
    std::make_unique<dae::null_sound_system>();