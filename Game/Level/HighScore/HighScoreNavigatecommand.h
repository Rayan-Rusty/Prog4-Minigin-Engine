#ifndef MINIGIN_HIGHSCORENAVIGATECOMMAND_H
#define MINIGIN_HIGHSCORENAVIGATECOMMAND_H
#include "GameActorCommand.h"

namespace DigDug {
    class HighScoreNavigatecommand final : public dae::GameActorCommand
    {
    public:
        explicit HighScoreNavigatecommand(dae::GameObject* gameObject, int direction);
        void Execute() override;
    private:
        int m_direction;
    };
} // DigDug

#endif //MINIGIN_HIGHSCORENAVIGATECOMMAND_H