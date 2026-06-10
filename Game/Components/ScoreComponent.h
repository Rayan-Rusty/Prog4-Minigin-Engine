#ifndef MINIGIN_SCORECOMPONENT_H
#define MINIGIN_SCORECOMPONENT_H
#include <algorithm>

#include "Component.h"
#include "Event.h"
#include "IObserver.h"

namespace DigDug
{
    class ScoreComponent final : public dae:: Component, public dae::IObserver
    {
    public:
        explicit ScoreComponent(dae::GameObject* owner);
        ~ScoreComponent();

        void Notify(dae::GameActor *actor, Event event);

        int GetScore();
    private:
        int m_score;
        static int PointsForPooka(int layer)
        {

            static int table[] =  { 200, 300, 400, 500 };
            return table[std::clamp(layer, 0, 3)];

        }
    };
} // DigDug

#endif //MINIGIN_SCORECOMPONENT_H