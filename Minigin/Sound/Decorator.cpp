//
// Created by omen on 29/04/2026.
//

#include "Decorator.h"
#include <iostream>

dae::logging_sound_system::logging_sound_system(std::unique_ptr<SoundSystem> &&ss)
: m_RealSS(std::move(ss))
{

}


void dae::logging_sound_system::play(sound_id id, float volume)
{
    m_RealSS->play(id, volume);
    std::cout << "[Sound] playing " << id << " at volume " << volume << std::endl;
}


void dae::logging_sound_system::load_sound(sound_id id, const std::string &path)
{
    std::cout << "Load sound " << id << " " << path << "\n";
}
