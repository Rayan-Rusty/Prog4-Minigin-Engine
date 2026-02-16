#pragma once




#include <memory>
#include "Scene.h"
namespace dae
{
        class Game
        {
        public:
            Game(dae::Scene& scene);
            ~Game() = default;

            void init() ;
            void Update(float deltaTime);
            void Draw() const ;
        private:
            Scene& m_Scene;
        };
}