//
// Created by omen on 11/03/2026.
//

#include "Gamepad.h"

#include <vector>
#include <Windows.h>
#include <XInput.h>

class dae::Gamepad::ImplGamePad
{
public:
    void SetIndex(int index) { m_index = index; }
    int Getindex() const { return m_index; }
    bool IsConnected() const { return m_isConnected; }

    void Update()
    {
        m_isConnected = (XInputGetState(m_index, &m_state) == ERROR_SUCCESS);
    }

    bool IsButtonPressed(int button) const
    {
        return (m_state.Gamepad.wButtons & button) != 0;
    }

private:
    int m_index{};
    XINPUT_STATE m_state{};
    bool m_isConnected{ false };
};

dae::Gamepad::Gamepad(int index) : pImpl(std::make_unique<ImplGamePad>()) {
    pImpl->SetIndex(index);
}


bool dae::Gamepad::IsConnected()
{
    return pImpl->IsConnected();
}

void dae::Gamepad::Update()
{
    pImpl->Update();
}

bool dae::Gamepad::IsButtonPressed(int button) const
{
    return  pImpl->IsButtonPressed(button);
}

bool dae::Gamepad::IsPressed(std::variant<SDL_Scancode, int> keyOrButton) const
{

    if (std::holds_alternative<int>(keyOrButton))
    {
        int button = std::get<int>(keyOrButton);
        return pImpl->IsButtonPressed(button);
    }
    return false; // ignore keyboard keys
}


std::vector<int> dae::Gamepad::GetConnectedDevices()
{
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

}


int dae::Gamepad::GetDeviceID() const
{
    return pImpl->Getindex();
}
