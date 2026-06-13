
#ifndef MINIGIN_POOKADEADSTATE_H
#define MINIGIN_POOKADEADSTATE_H
#include "State.h"

namespace DigDug
{
    class PookaBehaviour;
    class PookaDeadState final : public State<PookaBehaviour>
    {
    public:
        PookaDeadState() = default;
        ~PookaDeadState() override = default;
        void Enter(PookaBehaviour& Data) override;
        std::unique_ptr<State> Update(float DeltaTime, PookaBehaviour& Data) override;
        void Exit(PookaBehaviour& Data) override;

        std::type_index GetType() const override;

    private:
        float m_timer{0.f};
    };
}



#endif //MINIGIN_POOKADEADSTATE_H