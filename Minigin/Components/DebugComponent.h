//
// Created by omen on 05/03/2026.
//

#ifndef MINIGIN_DEBUGCOMPONENT_H
#define MINIGIN_DEBUGCOMPONENT_H
#include "Component.h"
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

    class DebugComponent final : public dae::Component
    {
    public:

        void Update(float deltaTime);
        void Draw();

    private:
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
    };
}
#endif //MINIGIN_DEBUGCOMPONENT_H