//
// Created by omen on 01/06/2026.
//

#include "HealthComponent.h"

dae::HealthComponent::HealthComponent(GameObject *pOwner, int maxhealth, int maxLives)
    : Component(pOwner) , m_maxHealth(maxhealth) , m_curHealth(maxhealth),  m_maxLives(maxLives), m_remainingLives(maxLives)
{
}

int dae::HealthComponent::GetCurrentHealth()
{
    return m_curHealth;
}

int dae::HealthComponent::GetMaxHealth()
{
    return m_maxHealth;
}

void dae::HealthComponent::DoDamage(int damage)
{
    int oldhealth{m_curHealth};
    m_curHealth = damage;
    if (m_curHealth <= oldhealth)
    {
        m_curHealth = 0;

        if (oldhealth > 0)
        {
            LoseLife();
        }
    }
}

void dae::HealthComponent::ResetResetHealth()
{
}

void dae::HealthComponent::LoseLife()
{
    if (m_remainingLives > 0)
    {
        --m_remainingLives;
        m_curHealth = m_maxHealth;
    }
}

void dae::HealthComponent::GainLife(int amnt)
{
    if (m_remainingLives >= m_maxLives) return;

    if (m_remainingLives == 0)
    {
        m_curHealth = m_maxHealth;
    }

    m_remainingLives += amnt ;
    if (m_remainingLives > m_maxLives)
    {
        m_remainingLives = m_maxLives;
    }
}

std::type_index dae::HealthComponent::GetType() const
{
    return std::type_index(typeid(HealthComponent));
}
