//
// Created by omen on 29/04/2026.
//

#ifndef MINIGIN_DEBUGSYSTEM_H
#define MINIGIN_DEBUGSYSTEM_H
#include "../EventQueue/IEventListener.h"


namespace dae
{
    class DebugSystem : public IEventListener
    {
    public:
        void OnEvent(const Event& e) override;
    private:

    };
}

#endif //MINIGIN_DEBUGSYSTEM_H