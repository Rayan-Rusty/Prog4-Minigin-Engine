//
// Created by omen on 11/03/2026.
//

#ifndef MINIGIN_GAMEACTORCOMMAND_H
#define MINIGIN_GAMEACTORCOMMAND_H
#include "Command.h"

namespace dae
{

    class GameActorCommand : public Command
    {
    public:
        GameActorCommand(GameObject* actor);
        virtual ~GameActorCommand() = default;
    protected:
        GameObject* GetGameActor() const { return this->m_GameActor; }

    private:
        GameObject* m_GameActor;
    };
}



#endif //MINIGIN_GAMEACTORCOMMAND_H