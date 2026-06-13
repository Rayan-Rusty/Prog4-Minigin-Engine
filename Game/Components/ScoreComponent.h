#ifndef MINIGIN_SCORECOMPONENT_H
#define MINIGIN_SCORECOMPONENT_H
#include <algorithm>

#include "Component.h"

#include "IObserver.h"

namespace DigDug
{
    class ScoreComponent final : public dae:: Component, public dae::IObserver
    {
    public:

        void Notify(Event event, dae::GameActor *actor) override;

        explicit ScoreComponent(dae::GameObject* owner);
        ~ScoreComponent() override = default;


        int GetScore();
        std::type_index GetType() const override;
        static inline int s_LastScore{0};

        ScoreComponent(const ScoreComponent& other) = delete;
        ScoreComponent(ScoreComponent&& other) = delete;
        ScoreComponent& operator=(const ScoreComponent& other) = delete;
        ScoreComponent& operator=(ScoreComponent&& other) = delete;

    private:
        int m_score{0};

        static int PointsForPooka(int layer)
        {

            static int table[] =  { 400, 600, 800, 1000 };
            return table[std::clamp(layer, 0, 3)];

        }

        static int PointsForFygar(int layer)
        {
            static int table[] = { 400, 600, 800, 1000 };
            return table[std::clamp(layer, 0, 3)];
        }
    };


} // DigDug

#endif //MINIGIN_SCORECOMPONENT_H