//
// Created by omen on 01/06/2026.
//

#ifndef MINIGIN_HEALTHCOMPONENT_H
#define MINIGIN_HEALTHCOMPONENT_H

namespace dae
{
    class HealthComponent
    {
    public:
        int GetCurrentHealth();
        void ChangeHealth(int health);
        void DoDamage(int damage);
        void ResetResetHealth();
    private:
    };
}



#endif //MINIGIN_HEALTHCOMPONENT_H