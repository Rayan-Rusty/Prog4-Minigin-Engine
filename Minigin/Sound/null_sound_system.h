//
// Created by omen on 29/04/2026.
//

#ifndef MINIGIN_NULL_SOUND_SYSTEM_H
#define MINIGIN_NULL_SOUND_SYSTEM_H

#pragma once
#include "SoundSystem.h"

namespace dae
{
    class null_sound_system final : public SoundSystem
    {
    public:
        void play(sound_id, float) override {}
        void load_sound(sound_id , const std::string& ){}
    };
}


#endif //MINIGIN_NULL_SOUND_SYSTEM_H