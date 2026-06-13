//
// Created by omen on 29/04/2026.
//

#ifndef MINIGIN_SCORESYSTEM_H
#define MINIGIN_SCORESYSTEM_H
#include <unordered_map>
#include "IEventListener.h"

namespace dae
{
    class ScoreSystem final : public IEventListener
    {
    public:
        void OnEvent(const Event& e) override;
    private:
        std::unordered_map<int, int> m_scores;
    };
}




#endif //MINIGIN_SCORESYSTEM_H