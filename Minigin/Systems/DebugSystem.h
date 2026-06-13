//
// Created by omen on 29/04/2026.
//

#ifndef MINIGIN_DEBUGSYSTEM_H
#define MINIGIN_DEBUGSYSTEM_H
#include "IEventListener.h"


namespace dae
{
    class DebugSystem final : public IEventListener
    {
    public:
        void OnEvent(const Event& e) override;
    private:

    };
}

#endif //MINIGIN_DEBUGSYSTEM_H