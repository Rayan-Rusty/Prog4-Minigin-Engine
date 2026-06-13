//
// Created by omen on 19/03/2026.
//

#ifndef MINIGIN_OBSERVERMANAGER_H
#define MINIGIN_OBSERVERMANAGER_H


#include "Singleton.h"
//TODO finish observers
namespace dae
{
    class IObserver;

    class ObserverManager final : public Singleton<ObserverManager>
    {
    public:
        ObserverManager() = default ;
        ~ObserverManager() override = default;
    private:

    };

}


#endif //MINIGIN_OBSERVERMANAGER_H