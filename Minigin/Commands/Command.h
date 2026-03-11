//
// Created by omen on 11/03/2026.
//

#ifndef MINIGIN_COMMAND_H
#define MINIGIN_COMMAND_H
#include "./GameObject.h"
namespace dae
{
    class Command
    {
    public:
        virtual ~Command() = default;
        virtual void Execute() = 0;
    };
}



#endif //MINIGIN_COMMAND_H