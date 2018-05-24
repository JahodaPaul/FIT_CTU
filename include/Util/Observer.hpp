#pragma once

#include "Util/Subject.hpp"
#include "Util/Event.hpp"
#include "common.hpp"

namespace RG { namespace Util {
    /**
     * \class Observer
     * \brief
     */
    class Observer {
        public:
            virtual ~Observer() {}
            virtual void onNotify(Subject * subject, Event event);
    };
} }
