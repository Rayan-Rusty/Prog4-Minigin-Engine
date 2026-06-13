#ifndef MINIGIN_PLAYERMOVECOMMAND_H
#define MINIGIN_PLAYERMOVECOMMAND_H
#include "GameActorCommand.h"
#include <glm/glm.hpp>
namespace DigDug {
    class PlayerMoveCommand : public dae::GameActorCommand
    {
    public:
        explicit PlayerMoveCommand(dae::GameObject *actor, const glm::ivec2& direction);

        void Execute() override;

        ~PlayerMoveCommand() override = default;

    private:
        glm::ivec2 m_Direction;
    };
} // DigDug

#endif //MINIGIN_PLAYERMOVECOMMAND_H