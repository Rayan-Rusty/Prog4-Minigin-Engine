//
// Created by omen on 11/03/2026.
//

#include "../Keyboard.h"

#include <array>

class dae::Keyboard::Impl
{
public:
    Impl()
    {
        keyState = SDL_GetKeyboardState(&numKeys);
    }

    ~Impl() = default;
    void Update()
    {
        SDL_PumpEvents();
        keyState = SDL_GetKeyboardState(nullptr);
        m_Previous = m_Current;

        for (int i = 0; i < SDL_SCANCODE_COUNT; i++)
        {
            m_Current[i] = keyState[i];
        }
    }


    bool IsPressed(SDL_Scancode key) const
    {
        return m_Current[key];
    }

    bool IsDown(SDL_Scancode key) const
    {
        return m_Current[key] && !m_Previous[key];
    }

    bool IsUp(SDL_Scancode key) const
    {
        return !m_Current[key] && m_Previous[key];
    }

private:
    std::array<bool, SDL_SCANCODE_COUNT> m_Current{};
    std::array<bool, SDL_SCANCODE_COUNT> m_Previous{};
    const bool* keyState{nullptr};
    int numKeys{0};
};

dae::Keyboard::Keyboard()
: pImpl(std::make_unique<Impl>())
{
}



void dae::Keyboard::Update() {
    pImpl->Update();
}

dae::Keyboard::~Keyboard() = default;

bool dae::Keyboard::IsPressed(std::variant<GamepadButton, SDL_Scancode> keyOrButton) const {

    if (std::holds_alternative<SDL_Scancode>(keyOrButton))
    {
        return pImpl->IsPressed(std::get<SDL_Scancode>(keyOrButton));
    }
    return false; //ignore Xinputkeys
}

bool dae::Keyboard::IsDown(std::variant<GamepadButton, SDL_Scancode> keyOrButton) const
{
    if (std::holds_alternative<SDL_Scancode>(keyOrButton))
    {
        return pImpl->IsDown(std::get<SDL_Scancode>(keyOrButton));
    }
    return false;
}

bool dae::Keyboard::IsUp(std::variant<GamepadButton, SDL_Scancode> keyOrButton) const
{
    if (std::holds_alternative<SDL_Scancode>(keyOrButton))
    {
        return pImpl->IsUp(std::get<SDL_Scancode>(keyOrButton));
    }
    return false;
}
int dae::Keyboard::GetDeviceID() const
{
    return -1;
}