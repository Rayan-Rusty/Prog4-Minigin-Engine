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

    class ObserverManager : public Singleton<ObserverManager>
    {
    public:
        ObserverManager();
        ~ObserverManager();
    private:

    };

}


#endif //MINIGIN_OBSERVERMANAGER_H