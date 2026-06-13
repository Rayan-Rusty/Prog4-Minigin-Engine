//
// Created by omen on 11/03/2026.
//

#ifndef MINIGIN_KEYBOARD_H
#define MINIGIN_KEYBOARD_H
#include "InputDevice.h"
#include <memory>
#include <variant>
#include "GamepadDataStructs.h"

namespace dae
{
    class Keyboard final : public InputDevice
    {
    public:
        explicit Keyboard();
        ~Keyboard() override;
        void Update() override;
        bool IsPressed(std::variant<GamepadButton, SDL_Scancode> keyOrButton) const override;
         bool IsDown(std::variant<GamepadButton, SDL_Scancode> keyOrButton) const override;
         bool IsUp(std::variant<GamepadButton, SDL_Scancode> keyOrButton) const  override;
        int GetDeviceID() const override;
    private:
        class Impl;
        std::unique_ptr<Impl> pImpl;
    };


}


#endif //MINIGIN_KEYBOARD_H