#ifndef MINIGIN_LEVELCOMPONENT_H
#define MINIGIN_LEVELCOMPONENT_H
#include <string>
#include <vector>
#include "LevelStruct.h"
#include "Component.h"
#include "IEventListener.h"

namespace DigDug
{

    class LevelComponent final: public dae::Component, public dae::IEventListener
    {
    public:


        void OnEvent(const dae::Event& e) override;

        LevelComponent(dae::GameObject* owner, std::vector<LevelData> levels );

        ~LevelComponent() override;

        void Update(float deltaTime) override;

        void Render() const override;

        std::type_index GetType() const override;

        void LoadCurrentLevel();

    private:

        std::vector<LevelData> m_Levels;
        int  m_CurrentLevel{ 0 };
        int m_EnemiesAlive{ 0 };
        bool m_IsLoading {false};
        bool m_PendingAdvance  {false};

        bool m_PendingSceneChange{false};

        void AdvanceLevel();

    };
} // DigDug

#endif //MINIGIN_LEVELCOMPONENT_H