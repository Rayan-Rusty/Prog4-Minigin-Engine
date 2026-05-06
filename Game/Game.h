#pragma once
#include <memory>

#include "IGame.h"
#include "../Minigin/Scene.h"
namespace game
{

    class Game : public game::IGame
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

    };
}