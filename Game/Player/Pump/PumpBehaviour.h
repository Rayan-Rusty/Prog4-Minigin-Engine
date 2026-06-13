#ifndef MINIGIN_PUMPBEHAVIOUR_H
#define MINIGIN_PUMPBEHAVIOUR_H
#include <memory>

#include "../../../Minigin/Components/BaseComp/Component.h"
#include "IEventListener.h"
#include <glm/glm.hpp>
#include "State.h"

namespace dae { class GameObject; }
namespace DigDug
{
    class PumpBehaviour final : public dae::Component ,  public dae::IEventListener
    {
    public:
        void OnEvent(const dae::Event &e) override;

        PumpBehaviour(dae::GameObject* owner);
        ~PumpBehaviour() = default;



        void Update(float dt) override;
        void ChangeState(std::unique_ptr<State<PumpBehaviour>> newState);
        std::type_index GetType() const override;
        glm::ivec2 GetDirection() const { return m_Dir; }

        PumpBehaviour(const PumpBehaviour& other) = delete;
        PumpBehaviour(PumpBehaviour&& other) = delete;
        PumpBehaviour& operator=(const PumpBehaviour& other) = delete;
        PumpBehaviour& operator=(PumpBehaviour&& other) = delete;


        private:

        glm::ivec2 m_Dir{};
        std::unique_ptr<State<PumpBehaviour>> m_state;
    };
} // DigDug

#endif //MINIGIN_PUMPBEHAVIOUR_H