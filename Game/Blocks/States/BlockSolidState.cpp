#include "BlockSolidState.h"

#include "GameObject.h"
#include "../../../Minigin/Components/Text/SpriteAnimationComponent.h"

namespace DigDug {
    void BlockSolidState::Enter(BlockBehaviour &owner)
    {
        auto* obj = owner.GetOwner();
        if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
        {
            std::vector<SDL_FRect> solidFrame =
            {
                {0, 0, 16, 16}  // frame 0 = solid block
            };
            spriteComp->SetAnimation(solidFrame, 0.f, false);
        }
    }

    std::unique_ptr<State<BlockBehaviour>> BlockSolidState::Update(float , BlockBehaviour &)
    {
        return nullptr;
    }

    void BlockSolidState::Exit(BlockBehaviour &) {
    }

    std::type_index BlockSolidState::GetType() const
    {
        return std::type_index(typeid(BlockSolidState));
    }
} // DigDug