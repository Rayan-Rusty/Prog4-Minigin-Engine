#ifndef MINIGIN_DESTROYED_H
#define MINIGIN_DESTROYED_H
#include <memory>

#include "State.h"
#include "Blocks/BlockBehaviour.h"

namespace DigDug
{
    class BlockDestroyedState final : public State<BlockBehaviour>
    {
    public:
        BlockDestroyedState() = default;
        ~BlockDestroyedState() override = default;

        void Enter(BlockBehaviour &owner) override;
        std::unique_ptr<State> Update(BlockBehaviour &Data) override;

        void Exit(BlockBehaviour &owner) override;

    private:
    };
}

#endif //MINIGIN_DESTROYED_H