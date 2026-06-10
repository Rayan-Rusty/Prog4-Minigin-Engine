//
// Created by omen on 15/05/2026.
//

#ifndef MINIGIN_MENUNAVIGATECOMMAND_H
#define MINIGIN_MENUNAVIGATECOMMAND_H
#include "GameActorCommand.h"


namespace DigDug
{

    class MenuNavigateCommand final : public dae::GameActorCommand
    {
    public:
        MenuNavigateCommand(dae::GameObject* actor , int dir);
        ~MenuNavigateCommand();

        void Execute() override;
    private:
        int m_Direction{0};
    };
} // dae

#endif //MINIGIN_MENUNAVIGATECOMMAND_H