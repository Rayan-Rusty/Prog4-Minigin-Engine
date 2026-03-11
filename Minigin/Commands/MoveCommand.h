//
// Created by omen on 11/03/2026.
//

#ifndef MINIGIN_MOVELEFTCOMMAND_H
#define MINIGIN_MOVELEFTCOMMAND_H
#include "GameActorCommand.h"

namespace dae
{
    class MoveCommand final : public GameActorCommand
    {
    public:
        MoveCommand(GameObject* actor , glm::vec3 direction);
        void Execute() override;
    private:
        glm::vec3 m_direction;
    };

}



#endif //MINIGIN_MOVELEFTCOMMAND_H