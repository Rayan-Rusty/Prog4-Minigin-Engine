//
// Created by omen on 15/05/2026.
//

#ifndef MINIGIN_MENUNAVIGATESYSTEM_H
#define MINIGIN_MENUNAVIGATESYSTEM_H
#include "IEventListener.h"


namespace dae {
    class GameObject;
}

namespace DigDug
{
    class MenuMarker;
    class MenuNavigateSystem final : public dae::IEventListener
    {
    public:

        explicit MenuNavigateSystem(dae::GameObject* Object);
        ~MenuNavigateSystem();

        void OnEvent(const dae::Event& e) override;


    private:
        dae::GameObject* m_MenuObject;
    };
} // dae

#endif //MINIGIN_MENUNAVIGATESYSTEM_H