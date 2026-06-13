//
// Created by omen on 06/05/2026.
//

#ifndef MINIGIN_POOKA_H
#define MINIGIN_POOKA_H
#include <memory>
#include <random>

#include "GameObject.h"
#include "PookaNormalState.h"
#include "State.h"


namespace dae {
    class GameObject;
}
namespace DigDug
{
    class ScoreComponent;
    class PookaState;

    class PookaBehaviour final : public dae::Component , public dae::IObserver
    {
    public:
        explicit PookaBehaviour(dae::GameObject* owner);
        ~PookaBehaviour() override ;


        void Notify(Event event, dae::GameActor *actor) override;

        void Update(float dt) override;
        void ChangeState(std::unique_ptr<State<PookaBehaviour>> newState);
        State<PookaBehaviour>* GetState() const;
        std::type_index GetType() const override;



        PookaBehaviour(const PookaBehaviour& other) = delete;
        PookaBehaviour(PookaBehaviour&& other) = delete;
        PookaBehaviour& operator=(const PookaBehaviour& other) = delete;
        PookaBehaviour& operator=(PookaBehaviour&& other) = delete;


    private:
        float m_GhostChance{ 0.1f };
        std::mt19937 m_Rng{ std::random_device{}() };
        std::uniform_real_distribution<float> m_dist{ 0.f, 1.f };
        std::unique_ptr<State<PookaBehaviour>> m_state{std::make_unique<PookaNormalState>()};
        dae::GameActor* m_pumpActor = nullptr;
        dae::GameActor* m_movementActor = nullptr;
        ScoreComponent* m_scoreComp{nullptr};
    };
}



#endif //MINIGIN_POOKA_H