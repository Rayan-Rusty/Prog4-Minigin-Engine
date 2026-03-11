#pragma once
#include <memory>
#include "Scene.h"
namespace dae
{

    class Game
    {
    public:
        Game(dae::Scene* scene);
        ~Game() = default;

        void init() ;
        void Update(float deltaTime);
        void Draw();
    private:

        void InitializeGame();
        void InitializeIMGUIScene();


        Scene* m_CurrentScene{ nullptr };


    };
}