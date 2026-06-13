#include "HighScoreComponent.h"

#include <filesystem>
#include <fstream>

#include "EventsIds.h"
#include "SceneManager.h"
#include "TextComponent.h"


DigDug::HighScoreComponent::HighScoreComponent(dae::GameObject *pOwner,
                                               std::vector<dae::TextComponent *> HighscrTextComp, std::vector<dae::TextComponent *> letterTextComps,
                                               std::vector<dae::GameObject *> arrws, dae::TextComponent *scrTextComp)
: Component(pOwner), m_pHighscrTextComps(HighscrTextComp) , m_pLetterTextComps(letterTextComps) , m_pArrws(arrws) , m_pScrTextComp(scrTextComp)
{
    HighscoresRead();
    SetTextComponents();
}

void DigDug::HighScoreComponent::OnEvent(const dae::Event &e)
{

    if ((m_SavedHighScore || m_secPassed < 0.1f) )
        return;

    std::string c{};
    switch (e.id)
    {
        case PressedPreviousArrow:
            if (m_secPassed < 0.1f) break;
            if (m_curChar == '.')
                m_curChar = 'a';

            --m_curChar;
            if (m_curChar < 'a')
                m_curChar = 'z';

            c = m_curChar;
            m_pLetterTextComps[m_curLetterIdx]->SetText(c);
            m_secPassed = 0.f;
            break;

        case PressedForwardArrow:
            if (m_secPassed < 0.1f) break;
            if (m_curChar == '.')
                m_curChar = 'z';

            ++m_curChar;
            if (m_curChar > 'z')
                m_curChar = 'a';

            c = m_curChar;
            m_pLetterTextComps[m_curLetterIdx]->SetText(c);
            m_secPassed = 0.f;
            break;

        case OnConfirmPressed:
            if (m_secPassed < 0.3f) break;
            ConfirmsLetter();
            m_secPassed = 0.f;
            break;
    }
}


void DigDug::HighScoreComponent::Update(float deltaTime)
{
    m_secPassed += deltaTime;
}

std::type_index DigDug::HighScoreComponent::GetType() const
{
    return std::type_index(typeid(HighScoreComponent));
}

void DigDug::HighScoreComponent::HighscoresRead()
{
    std::filesystem::path data_location = "./Data/";
    if (!std::filesystem::exists(data_location))
        data_location = "../Data/";

    const auto fullPath = data_location / "Highscores.txt";
    std::ifstream highscoreFile(fullPath.c_str());
    std::string highscoreStr;

    while (getline(highscoreFile, highscoreStr))
    {
        HighScore highscore{};
        highscore.FullString = highscoreStr;

        std::stringstream s(highscoreStr);
        std::getline(s, highscore.name, ' ');

        std::string scoreStr;
        std::getline(s, scoreStr);

        if (std::all_of(std::begin(scoreStr), std::end(scoreStr),
            [](unsigned char c) { return std::isdigit(c); }))
        {
            highscore.score = stoi(scoreStr);
        }

        m_highscores.emplace_back(highscore);
    }
}

void DigDug::HighScoreComponent::SetTextComponents()
{
    std::sort(m_highscores.begin(), m_highscores.end(),
    [](const HighScore& s1, const HighScore& s2) { return s1.score > s2.score; });

    size_t idx{ 0 };
    for (HighScore& highscore : m_highscores)
    {
        if (idx >= m_pHighscrTextComps.size())
        {
            m_highscores.erase(m_highscores.begin() + idx, m_highscores.end());
            break;
        }

        m_pHighscrTextComps[idx]->SetText(highscore.FullString);
        ++idx;
    }
}

void DigDug::HighScoreComponent::ConfirmsLetter() {
    if (m_curLetterIdx < m_pLetterTextComps.size() - 1 && m_curChar != '.')
    {
        m_NamePlayer += m_curChar;

        m_pLetterTextComps[m_curLetterIdx]->SetColor(SDL_Color{0, 0, 255, 255});
        ++m_curLetterIdx;
        m_pLetterTextComps[m_curLetterIdx]->SetColor(SDL_Color{128, 0, 128, 255});
        m_curChar = '.';

        std::string c{ m_curChar };
        m_pLetterTextComps[m_curLetterIdx]->SetText(c);

        glm::vec3 diff{ m_pLetterTextComps[m_curLetterIdx]->GetOwner()->GetTransform().GetWorldPosition()
            - m_pLetterTextComps[m_curLetterIdx - 1]->GetOwner()->GetTransform().GetWorldPosition() };
        for (auto arrow : m_pArrws)
            arrow->GetTransform().SetWorldPosition(arrow->GetTransform().GetWorldPosition() + diff);
    }
    else if (m_curLetterIdx != 0)
    {
        if (m_curChar != '.')
            m_NamePlayer += m_curChar;

        m_SavedHighScore = true;

        m_pLetterTextComps[m_curLetterIdx]->SetColor(SDL_Color{0, 0, 255, 255});
        for (auto arrow : m_pArrws)
            arrow->SetRenderObject(false);

        SetHighScore();
    }
}

void DigDug::HighScoreComponent::SetHighScore()
{
    std::string highscore = m_NamePlayer + " ";

    if (m_scoreP1 < 10000) highscore += "0";
    if (m_scoreP1 < 1000)  highscore += "0";
    if (m_scoreP1 < 100)   highscore += "0";
    if (m_scoreP1 < 10)    highscore += "0";
    highscore += std::to_string(m_scoreP1);

    m_highscores.emplace_back(HighScore{ .FullString = highscore, .name = m_NamePlayer, .score = m_scoreP1 });
    SetTextComponents();
    SaveHighScore();

    //dae::SceneManager::GetInstance().SetActiveScene(0);
}

void DigDug::HighScoreComponent::SaveHighScore()
{
    std::filesystem::path data_location = "./Data/";
    if (!std::filesystem::exists(data_location))
        data_location = "../Data/";

    const auto fullPath = data_location / "Highscores.txt";
    std::ofstream highscoreFile(fullPath.c_str());
    for (auto& hs : m_highscores)
        highscoreFile << hs.FullString << '\n';
}

void DigDug::HighScoreComponent::PassScore(size_t score)
{
    m_scoreP1 = score;

    std::string scoreStr{};
    if (m_scoreP1 < 10000) scoreStr += "0";
    if (m_scoreP1 < 1000)  scoreStr += "0";
    if (m_scoreP1 < 100)   scoreStr += "0";
    if (m_scoreP1 < 10)    scoreStr += "0";
    scoreStr += std::to_string(m_scoreP1);

    m_pScrTextComp->SetText(scoreStr);
}
