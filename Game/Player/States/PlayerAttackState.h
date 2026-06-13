#ifndef MINIGIN_PLAYERATTACK_H
#define MINIGIN_PLAYERATTACK_H
#include "PlayerBehaviour.h"

namespace DigDug {
    class PlayerAttackState final : public State<PlayerBehaviour>
    {
    public:
        void Enter(PlayerBehaviour &owner) override;

        std::unique_ptr<State<PlayerBehaviour>> Update(float DeltaTime, PlayerBehaviour &Data) override;

        void Exit(PlayerBehaviour &owner) override;

        std::type_index GetType() const override;
    };
} // DigDug

#endif //MINIGIN_PLAYERATTACK_H