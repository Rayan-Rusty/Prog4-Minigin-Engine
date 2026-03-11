//
// Created by omen on 11/03/2026.
//

#include "Gamepad.h"
#include <Windows.h>
#include <XInput.h>

class dae::Gamepad::ImplGamePad
{



    public:
        void Setindex(int index){m_index = index;}
        int Getindex() const {return m_index;}
        XINPUT_STATE& GetState(){return m_state;}

        bool IsConnected(){return XInputGetState(Getindex(), &GetState()) == ERROR_SUCCESS;}
        void Update(){ XInputGetState(Getindex() ,  &GetState());}
        bool IsButtonPressed(int button){ return (GetState().Gamepad.wButtons & button) != 0;}
    private:
    int m_index{};
    XINPUT_STATE m_state{};
};

dae::Gamepad::Gamepad(int index) : pImpl(std::make_unique<ImplGamePad>()) {
    pImpl->Setindex(index);
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

