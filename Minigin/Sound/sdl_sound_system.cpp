
#include "sdl_sound_system.h"

#include <iostream>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <SDL3_mixer/SDL_mixer.h>

class dae::sdl_sound_system::Impl
{
public:
    SDL_AudioDeviceID device = 0;
    MIX_Mixer* m_mixer = nullptr;


    void init()
    {
        if (!SDL_Init(SDL_INIT_AUDIO))
            throw std::runtime_error(SDL_GetError());
        if (!MIX_Init())
            throw std::runtime_error(SDL_GetError());

        SDL_AudioSpec spec{};
        spec.freq = 48000;
        spec.format = SDL_AUDIO_S16;
        spec.channels = 2;

        device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);

        if (device == 0)
            throw std::runtime_error(SDL_GetError());

        m_mixer = MIX_CreateMixerDevice(device, &spec);


        if (!m_mixer)
            throw std::runtime_error(SDL_GetError());

        std::cout << "[SDL_mixer] Mixer initialized\n";
    }

    ~Impl()
    {
        if (m_mixer)
        {
            m_mixer = nullptr;
        }

        if (device != 0)
        {
            SDL_CloseAudioDevice(device);
            device = 0;
        }


    }
    void load_sound(sound_id id, const std::string& path)
    {
        auto clip = std::make_unique<AudioClip>();
        clip->path = path;

        // load immediately here OR lazy-load later
        clip->audio = MIX_LoadAudio(m_mixer, path.c_str(), 0);

        if (!clip->audio)
            throw std::runtime_error(SDL_GetError());

        clip->track = MIX_CreateTrack(m_mixer);
        MIX_SetTrackAudio(clip->track, clip->audio);

        audioclips[id] = std::move(clip);

        std::cout << "[SDL_mixer] Registered sound: " << path << "\n";
    }
    void play(sound_id id, float volume)
    {

        auto it = audioclips.find(id);
        if (it == audioclips.end())
            return;

        auto& clip = it->second;

        MIX_SetTrackGain(clip->track, volume);
        MIX_PlayTrack(clip->track, false);
    }

    struct AudioClip {
        MIX_Audio* audio = nullptr;
        MIX_Track* track = nullptr;
        std::string path;
    };

    std::unordered_map<sound_id, std::unique_ptr<AudioClip>> audioclips;

};


dae::sdl_sound_system::sdl_sound_system()
    : m_Impl(std::make_unique<Impl>())
{
    m_Impl->init();
}

dae::sdl_sound_system::~sdl_sound_system() = default;

void dae::sdl_sound_system::load_sound(sound_id id, const std::string& path)
{
    m_Impl->load_sound(id, path);
}


void dae::sdl_sound_system::play(sound_id id, float volume)
{
    m_Impl->play(id, volume);
}
