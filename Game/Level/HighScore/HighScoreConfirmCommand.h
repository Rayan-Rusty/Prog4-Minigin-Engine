#ifndef MINIGIN_HIGHSCORECONFIRMCOMMAND_H
#define MINIGIN_HIGHSCORECONFIRMCOMMAND_H
#include "GameActorCommand.h"


namespace dae {
    class GameObject;
}

namespace DigDug
{
    class HighScoreConfirmCommand final : public dae::GameActorCommand
    {
    public:
        explicit HighScoreConfirmCommand(dae::GameObject* gameObject);
        void Execute() override;
    };
}
#endif //MINIGIN_HIGHSCORECONFIRMCOMMAND_H