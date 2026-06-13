//
// Created by omen on 29/04/2026.
//

#ifndef MINIGIN_SOUNDEVENTLISTENER_H
#define MINIGIN_SOUNDEVENTLISTENER_H
#include "IEventListener.h"


namespace dae
{
    class SoundEventListener final : public IEventListener
    {
    public:
        void OnEvent(const Event& e) override;
    private:
        bool m_isWalking{false};
    };
}

#endif //MINIGIN_SOUNDEVENTLISTENER_H