#pragma once

#include "Events.h"

#include <functional>
#include <vector>

namespace CitrusEngine {

    //EventConsumer wraps a function consumer
    class EventConsumer {
    public:
        EventConsumer(std::function<void(Event&)> consumer) : consumer(consumer) {}

        void Consume(Event& event) {
            consumer(event);
        }

        bool operator==(EventConsumer rhs){
            return (this == &rhs);
        }
    private:
        std::function<void(Event&)> consumer;
    };
}