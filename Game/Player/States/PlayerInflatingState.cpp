#include "PlayerInflatingState.h"

namespace DigDug {
    void PlayerInflatingState::Enter(PlayerBehaviour &)
    {
    }

    std::unique_ptr<State<PlayerBehaviour>> PlayerInflatingState::Update(float , PlayerBehaviour &)
    {
        return nullptr;
    }

    void PlayerInflatingState::Exit(PlayerBehaviour &) {
    }

    std::type_index PlayerInflatingState::GetType() const
    {
        return std::type_index(typeid(PlayerInflatingState));
    }
} // DigDug