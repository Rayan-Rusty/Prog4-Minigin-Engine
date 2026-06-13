//
// Created by omen on 02/05/2026.
//

#ifndef MINIGIN_PLAYER_H
#define MINIGIN_PLAYER_H
#include <memory>

#include "Component.h"
#include "IEventListener.h"
#include "State.h"

namespace dae { class GameObject; }
namespace DigDug
{
    class PlayerBehaviour final : public dae::Component,  public dae::IEventListener
    {
    public:
        void OnEvent(const dae::Event &e) override;


        PlayerBehaviour(dae::GameObject* owner);
        ~PlayerBehaviour() override = default;


        void Update(float dt) override;
        void ChangeState(std::unique_ptr<State<PlayerBehaviour>> newState);
        std::type_index GetType() const override;

        bool GetIsMoving() const;

        PlayerBehaviour(const PlayerBehaviour& other) = delete;
        PlayerBehaviour(PlayerBehaviour&& other) = delete;
        PlayerBehaviour& operator=(const PlayerBehaviour& other) = delete;
        PlayerBehaviour& operator=(PlayerBehaviour&& other) = delete;


    private:
        std::unique_ptr<State<PlayerBehaviour>> m_state;
        bool m_IsMoving{false};

    };
}



#endif //MINIGIN_PLAYER_H