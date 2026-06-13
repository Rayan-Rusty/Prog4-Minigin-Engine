
#ifndef MINIGIN_EVENTBUS_H
#define MINIGIN_EVENTBUS_H
#include <vector>
#include "IEventListener.h"
#include "Event.h"

namespace dae
{
    class EventBus
    {
    public:
        void AddListener(IEventListener* listener);
        void QueueEvent(const Event& e);
        void Clear();
        void ProcessEvents();
    private:

        std::vector<IEventListener*> m_listeners;
        std::vector<Event> m_events;
    };
}



#endif //MINIGIN_EVENTBUS_H