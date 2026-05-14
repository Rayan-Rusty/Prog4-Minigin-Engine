#pragma once
#include <memory>

#include "IGame.h"
#include "Scene.h"
namespace DigDug
{

    class Game : public DigDug::IGame
    {
    public:
        Game() = default;
        ~Game() = default;

        void Init() override;
        void Update(float deltaTime) override;
        void Draw() const override;
    private:

        void InitializeGame();
        void InitializeMenuScreen();
        void InitializeIMGUIScene();
        void InitFirstLevel();

    };
}