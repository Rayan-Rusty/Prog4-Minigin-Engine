//
// Created by omen on 11/03/2026.
//

#ifndef MINIGIN_INPUTDEVICE_H
#define MINIGIN_INPUTDEVICE_H
#include <Windows.h>
#include <variant>
#include <SDL3/SDL.h>
namespace dae
{
    class InputDevice
    {
    public:

        virtual ~InputDevice() = default;
        enum class InputState { Down, Up, Pressed };

        virtual void Update() = 0;

        virtual bool IsPressed(std::variant<SDL_Scancode, int> keyOrButton) const = 0;
    };
}



#endif //MINIGIN_INPUTDEVICE_H