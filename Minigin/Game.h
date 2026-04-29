#pragma once
#include <memory>
#include "Scene.h"
namespace dae
{

    class Game
    {
    public:
        Game() = default;
        ~Game() = default;

        void init() ;
        void Update(float deltaTime);
        void Draw();
    private:

        void InitializeGame();
        void InitializeIMGUIScene();



    };
}