//
// Created by omen on 31/05/2026.
//

#ifndef MINIGIN_PLAYERCOLLISIONHANDLER_H
#define MINIGIN_PLAYERCOLLISIONHANDLER_H
#include "IObserver.h"


namespace dae {
    class GameObject;
}

namespace DigDug
{



    class PlayerCollisionHandler : public dae::IObserver
    {
    public:
        PlayerCollisionHandler(dae::GameObject* listener);
        void Notify(Event event, dae::GameActor* actor) override;

    private:
        dae::GameObject* m_pListener;
    };
}

#endif //MINIGIN_PLAYERCOLLISIONHANDLER_H