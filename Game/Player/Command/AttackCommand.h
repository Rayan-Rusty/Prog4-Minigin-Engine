#ifndef MINIGIN_ATTACKCOMMAND_H
#define MINIGIN_ATTACKCOMMAND_H
#include "GameActorCommand.h"

namespace DigDug {
    class AttackCommand : public dae::GameActorCommand
    {
    public:
        explicit AttackCommand(dae::GameObject *actor);

        void Execute() override;

        ~AttackCommand()override= default ;

    private:
    };
} // DigDug

#endif //MINIGIN_ATTACKCOMMAND_H