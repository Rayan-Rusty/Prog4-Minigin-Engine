//
// Created by omen on 29/04/2026.
//

#ifndef MINIGIN_SDL_SOUND_SYSTEM_H
#define MINIGIN_SDL_SOUND_SYSTEM_H
#include "SoundSystem.h"
#include <memory>

namespace dae
{
    class sdl_sound_system final : public SoundSystem
    {
    public:
        sdl_sound_system();
        ~sdl_sound_system() override;

        void play(sound_id id, float volume) override;
        void load_sound(sound_id id, const std::string& path) override;
    private:
        class Impl;
        std::unique_ptr<Impl> m_Impl;
    };
}
#endif //MINIGIN_SDL_SOUND_SYSTEM_H