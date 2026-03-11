//
// Created by omen on 11/03/2026.
//

#ifndef MINIGIN_GAMEPAD_H
#define MINIGIN_GAMEPAD_H
#include <memory>

#include "InputDevice.h"

namespace dae
{
    class Gamepad : public InputDevice
    {
    public:
        Gamepad(int index);
        bool IsConnected();
        void Update();
        bool IsButtonPressed(int button) const;
        bool IsPressed(std::variant<SDL_Scancode, int> keyOrButton) const override;

    private:
        class ImplGamePad;
        std::unique_ptr<ImplGamePad> pImpl;
    };
}




#endif //MINIGIN_GAMEPAD_H