//
// Created by omen on 19/03/2026.
//

#ifndef MINIGIN_GAMEACTOR_H
#define MINIGIN_GAMEACTOR_H
#include <vector>

#include "IObserver.h"


namespace dae
{

    class GameObject;
    class GameActor final

    {
    public:
        explicit GameActor(GameObject* pOwner);
        ~GameActor();
        void AddObserver(IObserver* observer);
        void RemoveObserver(IObserver* observer);
        void NotifyObservers(IObserver::Event event);
        GameObject* GetOwner() const;
    protected:

    private:
        std::vector<IObserver*> m_Observers;
        GameObject* m_pOwner{nullptr};

    };

}




#endif //MINIGIN_GAMEACTOR_H