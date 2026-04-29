//
// Created by omen on 29/04/2026.
//

#ifndef MINIGIN_SERVICELOCATOR_H
#define MINIGIN_SERVICELOCATOR_H
#include <memory>
#include "SoundSystem.h"

namespace dae
{
    class ServiceLocator final
    {
        static std::unique_ptr<SoundSystem> _ss_instance;
    public:
        static SoundSystem& get_sound_system()
        {
            return *_ss_instance;
        }

        static void register_sound_system(std::unique_ptr<SoundSystem>&& ss)
        {
            _ss_instance = std::move(ss);
        }
    };
}


#endif //MINIGIN_SERVICELOCATOR_H