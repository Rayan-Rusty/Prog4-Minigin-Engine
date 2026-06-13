#ifndef MINIGIN_SOLID_H
#define MINIGIN_SOLID_H
#include "BlockBehaviour.h"

namespace DigDug
{
    class BlockSolidState : public State<BlockBehaviour>
    {
    public:
        BlockSolidState() = default;
        ~BlockSolidState() override = default;

        void Enter(BlockBehaviour &owner) override;
        std::unique_ptr<State> Update(float DeltaTime, BlockBehaviour &Data) override;
        void Exit(BlockBehaviour &Data) override;

        std::type_index GetType() const override;

    private:

    };
} // DigDug

#endif //MINIGIN_SOLID_H