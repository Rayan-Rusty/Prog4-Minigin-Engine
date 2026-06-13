#ifndef MINIGIN_PUMPIDLESTATE_H
#define MINIGIN_PUMPIDLESTATE_H
#include "State.h"
#include "PumpBehaviour.h"

namespace DigDug {
    class PumpIdleState final : public State<PumpBehaviour> {
    public:
        PumpIdleState() = default;
        ~PumpIdleState() override = default;
        void Enter(PumpBehaviour &owner) override;
        std::unique_ptr<State<PumpBehaviour>> Update(float DeltaTime, PumpBehaviour &Data) override;
        void Exit(PumpBehaviour &owner) override;

        std::type_index GetType() const override;
    };
} // DigDug

#endif //MINIGIN_PUMPIDLESTATE_H