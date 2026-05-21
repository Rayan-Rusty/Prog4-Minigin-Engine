//
// Created by omen on 19/03/2026.
//

#ifndef MINIGIN_GAMEACTOR_H
#define MINIGIN_GAMEACTOR_H
#include <vector>

#include "IObserver.h"


namespace dae
{

    class GameActor
    {
    public:
        GameActor() = default;
        ~GameActor();
        void AddObserver(IObserver* observer);
        void RemoveObserver(IObserver* observer);
    protected:
            void NotifyObservers(IObserver::Event event);
    private:
        std::vector<IObserver*> m_Observers;


    };

}




#endif //MINIGIN_GAMEACTOR_H