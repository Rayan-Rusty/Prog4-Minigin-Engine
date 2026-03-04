#pragma once
#include <memory>
#include "Scene.h"
namespace dae
{
    struct TransformObj
    {
        float matrix[16] = {
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            0,0,0,1 };
    };

    class GameObject3D
    {
    public:
        TransformObj transform{};
        int ID{1};
    };

    struct GameObject3DAlt
    {
        int ID = 1;
        TransformObj* transform{};
    };

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

        void WindowIntBenchmark();
        void WindowGameObjectWindow();

        void RunIntBenchmark();
        void RunGameObject3DBenchmark();
        void RunGameObject3DAltBenchmark();

        int m_sampleCountInt{10};
        int m_sampleCountGameObject{100};
        std::vector<float> m_IntTimings;
        std::vector<float> m_GameObject3D;
        std::vector<float> m_GameObject3DAlt;
        Scene* m_CurrentScene{ nullptr };


    };
}