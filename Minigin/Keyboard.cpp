//
// Created by omen on 11/03/2026.
//

#include "Keyboard.h"

class dae::Keyboard::Impl
{
public:
    Impl()
    {
        keyState = SDL_GetKeyboardState(&numKeys); // returns const Uint8*
    }

    void Update()
    {
        SDL_PumpEvents();
    }


    bool IsPressed(SDL_Scancode key) const
    {
        if (key >= numKeys) return false;
        return keyState[key] != 0;
    }

private:
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

bool dae::Keyboard::IsPressed(std::variant<SDL_Scancode, int> keyOrButton) const
{
    if (std::holds_alternative<SDL_Scancode>(keyOrButton))
    {
        return pImpl->IsPressed(std::get<SDL_Scancode>(keyOrButton));
    }
    return false; //ignore Xinputkeys
}



