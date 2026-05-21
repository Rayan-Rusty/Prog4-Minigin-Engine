//
// Created by omen on 15/05/2026.
//

#ifndef MINIGIN_MENUNAVIGATECOMMAND_H
#define MINIGIN_MENUNAVIGATECOMMAND_H
#include "GameActorCommand.h"


namespace dae
{

    class MenuNavigateCommand final : public GameActorCommand
    {
    public:
        MenuNavigateCommand(GameObject* actor , int dir);
        ~MenuNavigateCommand();

        void Execute() override;
    private:
        int m_Direction{0};
    };
} // dae

#endif //MINIGIN_MENUNAVIGATECOMMAND_H