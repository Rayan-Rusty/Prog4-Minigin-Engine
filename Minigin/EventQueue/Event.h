//
// Created by omen on 29/04/2026.
//

#ifndef MINIGIN_EVENT_H
#define MINIGIN_EVENT_H
#include <cstdint>

namespace dae
{


    struct EventArg
    {
        int intValue;
    };

    using EventId = unsigned int;

    struct Event
    {
        const EventId id;

        static const uint8_t MAX_ARGS = 8;
        uint8_t nbArgs{0};
        EventArg args[MAX_ARGS]{};

        explicit Event(EventId _id)
            : id{_id}
        {}
    };
}
#endif //MINIGIN_EVENT_H