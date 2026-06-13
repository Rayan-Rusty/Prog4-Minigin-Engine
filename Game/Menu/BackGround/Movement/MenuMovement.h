#ifndef MINIGIN_MENUMOVEMENT_H
#define MINIGIN_MENUMOVEMENT_H
#include "Component.h"
#include "glm/vec2.hpp"

namespace DigDug {
    class MenuMovement final : dae::Component
    {
    public:
        MenuMovement();
        ~MenuMovement();

        void Update(float deltaTime) override;
        void AddPosition(glm::vec2 pos);

    private:


    };
} // DigDug

#endif //MINIGIN_MENUMOVEMENT_H