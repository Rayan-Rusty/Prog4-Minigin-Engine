//
// Created by omen on 29/04/2026.
//

#ifndef MINIGIN_DECORATOR_H
#define MINIGIN_DECORATOR_H
#include "SoundSystem.h"
#include <memory>


namespace dae
{
    class logging_sound_system final : public SoundSystem
    {
    public:
        logging_sound_system(std::unique_ptr<SoundSystem>&& ss);

        void play(sound_id id, float volume) override;
        void load_sound(sound_id id, const std::string& path) override;
    private:
        std::unique_ptr<SoundSystem> m_RealSS;
    };
}


#endif //MINIGIN_DECORATOR_H