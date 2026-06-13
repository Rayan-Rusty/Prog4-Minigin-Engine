//
// Created by omen on 01/06/2026.
//

#ifndef MINIGIN_ENEMYTRAITS_H
#define MINIGIN_ENEMYTRAITS_H

//this way you don't have to input it everytime into EnemySpawner
// and the classes dont know abt each other so there isnt a hard dependency
#include "PookaBehaviour.h"
#include "FygarBehaviour.h"
#include "Utils.h"
namespace DigDug {


    struct PookaTraits
    {
        static std::unique_ptr<dae::GameObject> Create()
        {
            return Utils::CreatePooka();
        }
        using Behaviour = PookaBehaviour;
        static constexpr const char* SpritePath() { return "Sprites/PookaSprites.png"; }
        static constexpr int Cols() { return 6; }
        static constexpr int Rows() { return 7; }
    };

    struct FygarTraits
    {
        static std::unique_ptr<dae::GameObject> Create()
        {
            return Utils::CreateFygar();
        }
        using Behaviour = FygarBehaviour;
        static constexpr const char* SpritePath() { return "Sprites/Fygarprites.png"; }
        static constexpr int Cols(){ return 8; }
        static constexpr int Rows(){ return 8; }
    };


    struct PlayerTraits
    {
        static std::unique_ptr<dae::GameObject> Create()
        {
            return Utils::CreatePlayer();
        }
        static constexpr const char* SpritePath() { return "Sprites/PlayerSprites.png"; }
        static constexpr int Cols(){ return 3; }
        static constexpr int Rows(){ return 8; }
    };
}

#endif //MINIGIN_ENEMYTRAITS_H