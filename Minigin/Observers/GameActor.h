//
// Created by omen on 19/03/2026.
//

#ifndef MINIGIN_GAMEACTOR_H
#define MINIGIN_GAMEACTOR_H
#include <vector>


namespace dae
{
    class IObserver;
    class GameActor
    {
    public:
        void AddObserver(IObserver* observer);
        void RemoveObserver(IObserver* observer);

    protected:
            void NotifyObservers(Event event);

    private:
        std::vector<IObserver*> m_observers;
    };

}




#endif //MINIGIN_GAMEACTOR_H