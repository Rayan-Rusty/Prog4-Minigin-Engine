//
// Created by omen on 11/03/2026.
//

#ifndef MINIGIN_GAMEPAD_H
#define MINIGIN_GAMEPAD_H
#include <memory>
#include "InputDevice.h"
#include <vector>
#include "GamepadDataStructs.h"
namespace dae
{
    class Gamepad final : public InputDevice
    {
    public:
        explicit Gamepad(int index);
        ~Gamepad() override;
        bool IsConnected();
        void Update() override;
        bool IsButtonPressed(GamepadButton button) const;
        bool IsPressed(std::variant<GamepadButton, SDL_Scancode> keyOrButton) const override;
        bool IsDown(std::variant<GamepadButton, SDL_Scancode> keyOrButton) const override;
        bool IsUp(std::variant<GamepadButton, SDL_Scancode> keyOrButton) const  override;
        static std::vector<int> GetConnectedDevices();

        int GetDeviceID() const override;


    private:
        class ImplGamePad;
        std::unique_ptr<ImplGamePad> pImpl;

    };
}




#endif //MINIGIN_GAMEPAD_H