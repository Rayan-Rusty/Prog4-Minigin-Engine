#ifndef MINIGIN_PLAYERINFLATINGSTATE_H
#define MINIGIN_PLAYERINFLATINGSTATE_H
#include "PlayerBehaviour.h"

namespace DigDug {
    class PlayerInflatingState final : public  State<PlayerBehaviour>{
    public:

        PlayerInflatingState() = default;
        ~PlayerInflatingState() = default;

        void Enter(PlayerBehaviour &owner) override;

        std::unique_ptr<State<PlayerBehaviour>> Update(float DeltaTime, PlayerBehaviour &Data) override;

        void Exit(PlayerBehaviour &owner) override;

        std::type_index GetType() const override;
    };
} // DigDug

#endif //MINIGIN_PLAYERINFLATINGSTATE_H