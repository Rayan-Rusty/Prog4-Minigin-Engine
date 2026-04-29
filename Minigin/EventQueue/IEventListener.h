//
// Created by omen on 29/04/2026.
//

#ifndef MINIGIN_IEVENTLISTENER_H
#define MINIGIN_IEVENTLISTENER_H
#include "Event.h"
namespace dae
{
    class IEventListener
    {
    public:
        virtual ~IEventListener() = default;
        virtual void OnEvent(const dae::Event& e) = 0;
    };
}
#endif //MINIGIN_IEVENTLISTENER_H