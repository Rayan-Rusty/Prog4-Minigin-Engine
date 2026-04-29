//
// Created by omen on 19/03/2026.
//

#ifndef MINIGIN_ACHIEVEMENT_H
#define MINIGIN_ACHIEVEMENT_H
#include "IObserver.h"


namespace dae
{

    class Achievement final : public IObserver
    {
    public:
        void Notify(Event event,  GameActor* actor) override;
    private:

        void unlock(Achievement achievement);
    };
}


#endif //MINIGIN_ACHIEVEMENT_H