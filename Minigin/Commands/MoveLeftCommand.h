//
// Created by omen on 11/03/2026.
//

#ifndef MINIGIN_MOVELEFTCOMMAND_H
#define MINIGIN_MOVELEFTCOMMAND_H
#include "GameActorCommand.h"

namespace dae
{
    class MoveLeftCommand final : public GameActorCommand
    {
    public:
        MoveLeftCommand(GameObject* actor);
        void Execute() override;

    };
}



#endif //MINIGIN_MOVELEFTCOMMAND_H