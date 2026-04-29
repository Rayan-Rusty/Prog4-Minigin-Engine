//
// Created by omen on 29/04/2026.
//

#ifndef MINIGIN_SOUNDSYSTEM_H
#define MINIGIN_SOUNDSYSTEM_H
#include <string>

namespace dae
{
    using sound_id = unsigned short;
    class SoundSystem
    {
    public:
        virtual ~SoundSystem() = default;
        virtual void play(const sound_id id, const float volume) = 0;
        virtual void load_sound(sound_id id, const std::string& path) = 0;
    };
}

#endif //MINIGIN_SOUNDSYSTEM_H