#ifndef MINIGIN_PUMPATTACKSTATE_H
#define MINIGIN_PUMPATTACKSTATE_H
#include "IEventListener.h"
#include "State.h"
#include "glm/glm.hpp"
#include "PumpBehaviour.h"

namespace DigDug {
    class PumpAttackState final : public State<PumpBehaviour>, public dae::IEventListener
    {
    public:
        void OnEvent(const dae::Event &e) override;

        ~PumpAttackState() override = default;
        void Enter(PumpBehaviour &owner) override;
        std::unique_ptr<State<PumpBehaviour>> Update(float DeltaTime, PumpBehaviour &Data) override;
        void Exit(PumpBehaviour &owner) override;



        std::type_index GetType() const override;

    private:
        bool m_HitWall{false};
        float m_DistanceTravelled{0.0f};
        float m_MaxRange{100.0f};
        glm::vec2 m_Dir{-1.0f, 0.0f};
        float m_Speed{70.0f};
        glm::vec3 m_StartPos{0.f, 0.f, 0.f};
    };


} // DigDug

#endif //MINIGIN_PUMPATTACKSTATE_H