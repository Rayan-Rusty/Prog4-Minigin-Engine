#ifndef MINIGIN_CONFIRMEDCOMMAND_H
#define MINIGIN_CONFIRMEDCOMMAND_H
#include "GameActorCommand.h"

namespace DigDug {
    class ConfirmedCommand final : public dae::GameActorCommand
    {
    public:
        explicit ConfirmedCommand(dae::GameObject* gameObject);
        void Execute() override;
    };
} // DigDug

#endif //MINIGIN_CONFIRMEDCOMMAND_H