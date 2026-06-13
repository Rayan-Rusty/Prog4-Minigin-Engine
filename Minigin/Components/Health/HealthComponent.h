//
// Created by omen on 01/06/2026.
//

#ifndef MINIGIN_HEALTHCOMPONENT_H
#define MINIGIN_HEALTHCOMPONENT_H
#include "Component.h"

namespace dae
{
    class HealthComponent final : public Component
    {
    public:
        explicit HealthComponent(GameObject* pOwner, int maxhealth , int maxLives);

        ~HealthComponent() override = default;

        int GetCurrentHealth();
        int GetMaxHealth();
        void DoDamage(int damage);
        void ResetResetHealth();

        void LoseLife();
        void GainLife(int amount);

        std::type_index GetType() const override;

    private:

        const int m_maxHealth;
        int m_curHealth;

        const int m_maxLives;
        int m_remainingLives;
    };
}



#endif //MINIGIN_HEALTHCOMPONENT_H