//
// Created by omen on 06/05/2026.
//

#include "Pooka.h"

#include "States/PookaState.h"


void Pooka::Update(float dt )
{
    if (m_state)
        m_state->Update(*this);
}

void Pooka::Draw()
{

}
