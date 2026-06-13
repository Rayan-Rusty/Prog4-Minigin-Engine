#pragma once


#include "IGame.h"

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


        void InitializeMenuScreen();
        void InitFirstLevel();
        void HighScoreLevel();

    };
}