//
// Created by omen on 11/03/2026.
//

#ifndef MINIGIN_INPUTDEVICE_H
#define MINIGIN_INPUTDEVICE_H

#include <variant>
#include "../DataStructs/GamepadDataStructs.h"
#include <SDL3/SDL.h>

namespace dae
{
    class InputDevice
    {
    public:

        virtual ~InputDevice() = default;
        enum class InputState { Down, Up, Pressed };

        virtual void Update() = 0;
        virtual int GetDeviceID() const = 0;
        virtual bool IsPressed(std::variant<GamepadButton, SDL_Scancode> keyOrButton) const = 0;
        virtual bool IsDown(std::variant<GamepadButton, SDL_Scancode> keyOrButton) const = 0;
        virtual bool IsUp(std::variant<GamepadButton, SDL_Scancode> keyOrButton) const = 0;
    };
}



#endif //MINIGIN_INPUTDEVICE_H