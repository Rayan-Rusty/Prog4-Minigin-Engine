
#ifndef MINIGIN_POOKAINFLATEDSTATE_H
#define MINIGIN_POOKAINFLATEDSTATE_H
#include "State.h"

namespace DigDug
{
    class PookaBehaviour;

    class PookaInflatedState final: public State<PookaBehaviour>
    {
    public:
        PookaInflatedState() = default;
        ~PookaInflatedState() override = default;
        void Enter(PookaBehaviour& Data) override;
        std::unique_ptr<State> Update(float DeltaTime, PookaBehaviour& Data) override;
        void Exit(PookaBehaviour& Data) override;

        std::type_index GetType() const override;

    private:
        float m_timer{0.f};
        float m_DeflateTime{1.f};
    };
} // game

#endif //MINIGIN_POOKAINFLATEDSTATE_H