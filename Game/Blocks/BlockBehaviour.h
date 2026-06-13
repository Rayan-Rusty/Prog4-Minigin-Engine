#ifndef MINIGIN_BLOCKBEHAVIOUR_H
#define MINIGIN_BLOCKBEHAVIOUR_H
#include "../../Minigin/Components/BaseComp/Component.h"
#include "IObserver.h"
#include "State.h"

namespace DigDug
{

    class BlockBehaviour final : public dae::Component , public dae::IObserver
    {
    public:
        void Notify(dae::IObserver::Event event, dae::GameActor* actor) override;


        BlockBehaviour(dae::GameObject* owner);
        ~BlockBehaviour() = default;

        void Update(float dt) override;
        void ChangeState(std::unique_ptr<State<BlockBehaviour>> newState);
        std::type_index GetType() const override;




        BlockBehaviour(const BlockBehaviour& other) = delete;
        BlockBehaviour(BlockBehaviour&& other) = delete;
        BlockBehaviour& operator=(const BlockBehaviour& other) = delete;
        BlockBehaviour& operator=(BlockBehaviour&& other) = delete;


    private:
        std::unique_ptr<State<BlockBehaviour>> m_state;
        bool m_iSDestroyed{false};
    };
}


#endif //MINIGIN_BLOCKBEHAVIOUR_H