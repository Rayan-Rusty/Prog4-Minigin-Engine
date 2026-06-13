#ifndef MINIGIN_HIGHSCORECOMPONENT_H
#define MINIGIN_HIGHSCORECOMPONENT_H
#include <string>
#include <vector>

#include "../../Minigin/Components/BaseComp/Component.h"
#include "IEventListener.h"

namespace dae {
    class TextComponent;
}

namespace DigDug
{
    struct HighScore
    {
        std::string FullString;
        std::string name;
        size_t score;

    };

    class HighScoreComponent final : public dae::Component, public dae::IEventListener
    {
    public:
        void OnEvent(const dae::Event &e) override;

        HighScoreComponent(dae::GameObject* pOwner, std::vector<dae::TextComponent*> HighscrTextComp,
                           std::vector<dae::TextComponent*> letterTextComps, std::vector<dae::GameObject*> arrws,
                           dae::TextComponent* scrTextComp);

        ~HighScoreComponent() override = default;

        HighScoreComponent(const HighScoreComponent& other) = delete;
        HighScoreComponent(HighScoreComponent&& other) = delete;
        HighScoreComponent& operator=(const HighScoreComponent& other) = delete;
        HighScoreComponent& operator=(HighScoreComponent&& other) = delete;

        void Update(float deltaTime) override;
        void PassScore(size_t score);
        std::type_index GetType() const override;

    private:
        void HighscoresRead();
        void SetTextComponents();
        void ConfirmsLetter();
        void SetHighScore();
        void SaveHighScore();


        size_t m_scoreP1{ 0 };
        size_t m_curLetterIdx{ 0 };
        char m_curChar{'a'};
        float m_secPassed{0.f};
        std::string m_NamePlayer{};
        bool m_SavedHighScore{ false };


        std::vector<dae::TextComponent*> m_pHighscrTextComps;
        std::vector<dae::TextComponent*> m_pLetterTextComps;
        std::vector<dae::GameObject*> m_pArrws;
        std::vector<HighScore> m_highscores;
        dae::TextComponent* m_pScrTextComp;
    };
} // DigDug

#endif //MINIGIN_HIGHSCORECOMPONENT_H