//
// Created by omen on 11/03/2026.
//

#include "Gamepad.h"

#include <array>
#include <vector>

#include "../Input/InputManager.h"

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
        m_Previous = m_Current;

        for (int i = 0; i < BUTTON_COUNT; i++)
        {
            GamepadButton button = static_cast<GamepadButton>(i);
            m_Current[i] = (m_state.Gamepad.wButtons & ToXInput(button)) != 0;
        }
    #endif
    }

    bool IsButtonPressed(GamepadButton button) const
    {
    #ifdef _WIN32
        return m_Current[(int)button];
    #else
        (void)button;
            return false;
    #endif
    }

    bool IsDown(GamepadButton button) const
    {
#ifdef _WIN32
        int i = (int)button;
        return m_Current[i] && !m_Previous[i];
#endif
    }

    bool IsUp(GamepadButton button) const
    {
#ifdef _WIN32
        int i = (int)button;
        return !m_Current[i] && m_Previous[i];

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
    static constexpr int BUTTON_COUNT = 14;
    std::array<bool, BUTTON_COUNT> m_Current{};
    std::array<bool, BUTTON_COUNT> m_Previous{};
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
        return pImpl->IsButtonPressed(std::get<GamepadButton>(keyOrButton));
    }
    return false; // ignore keyboard keys
}

bool dae::Gamepad::IsDown(std::variant<GamepadButton, SDL_Scancode> keyOrButton) const
{
    if (std::holds_alternative<GamepadButton>(keyOrButton))
    {
        return pImpl->IsDown(std::get<GamepadButton>(keyOrButton));
    }
    return false;
}
bool dae::Gamepad::IsUp(std::variant<GamepadButton, SDL_Scancode> keyOrButton) const
{
    if (std::holds_alternative<GamepadButton>(keyOrButton))
    {
        return pImpl->IsUp(std::get<GamepadButton>(keyOrButton));
    }
    return false;
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
