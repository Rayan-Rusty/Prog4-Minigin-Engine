//
// Created by omen on 11/03/2026.
//

#include "Gamepad.h"

#include <vector>

#include "InputManager.h"

#ifdef _WIN32
#include <Windows.h>
#include <XInput.h>
#endif


class dae::Gamepad::ImplGamePad
{
public:
    void SetIndex(int index) { m_index = index; }
    int Getindex() const { return m_index; }
    bool IsConnected() const { return m_isConnected; }

    void Update()
    {
    #ifdef _WIN32
        m_isConnected = (XInputGetState(m_index, &m_state) == ERROR_SUCCESS);
    #endif
    }

    bool IsButtonPressed(GamepadButton button) const
    {
    #ifdef _WIN32
            return (m_state.Gamepad.wButtons & ToXInput(button)) != 0;
    #else
            return false;
    #endif
    }

#ifdef _WIN32
    WORD ToXInput(GamepadButton button) const
    {
        switch (button)
        {
            case GamepadButton::A: return XINPUT_GAMEPAD_A;
            case GamepadButton::B: return XINPUT_GAMEPAD_B;
            case GamepadButton::X: return XINPUT_GAMEPAD_X;
            case GamepadButton::Y: return XINPUT_GAMEPAD_Y;

            case GamepadButton::DPadUp: return XINPUT_GAMEPAD_DPAD_UP;
            case GamepadButton::DPadDown: return XINPUT_GAMEPAD_DPAD_DOWN;
            case GamepadButton::DPadLeft: return XINPUT_GAMEPAD_DPAD_LEFT;
            case GamepadButton::DPadRight: return XINPUT_GAMEPAD_DPAD_RIGHT;

            case GamepadButton::Start: return XINPUT_GAMEPAD_START;
            case GamepadButton::Back: return XINPUT_GAMEPAD_BACK;

            case GamepadButton::LeftShoulder: return XINPUT_GAMEPAD_LEFT_SHOULDER;
            case GamepadButton::RightShoulder: return XINPUT_GAMEPAD_RIGHT_SHOULDER;

            default:
                return 0;
        }
    }

    XINPUT_STATE m_state{};
#endif

private:
    int m_index{};

    bool m_isConnected{ false };

};

dae::Gamepad::Gamepad(int index) : pImpl(std::make_unique<ImplGamePad>()) {
    pImpl->SetIndex(index);
}

dae::Gamepad::~Gamepad() {

}


bool dae::Gamepad::IsConnected()
{
    return pImpl->IsConnected();
}

void dae::Gamepad::Update()
{
    pImpl->Update();
}

bool dae::Gamepad::IsButtonPressed(GamepadButton button) const
{
    return  pImpl->IsButtonPressed(button);
}

bool dae::Gamepad::IsPressed(std::variant<GamepadButton , SDL_Scancode> keyOrButton) const
{

    if (std::holds_alternative<GamepadButton>(keyOrButton))
    {
        GamepadButton button = std::get<GamepadButton>(keyOrButton);
        return pImpl->IsButtonPressed(button);
    }
    return false; // ignore keyboard keys
}

std::vector<int> dae::Gamepad::GetConnectedDevices()
{
#ifdef _WIN32
    std::vector<int> indices;

    for (int i = 0; i < XUSER_MAX_COUNT; ++i)
    {
        XINPUT_STATE state{};
        if (XInputGetState(i, &state) == ERROR_SUCCESS)
        {
            indices.push_back(i);
        }
    }

    return indices;
#else
    return {};
#endif
}


int dae::Gamepad::GetDeviceID() const
{
    return pImpl->Getindex();
}
