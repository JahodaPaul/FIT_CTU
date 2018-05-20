#pragma once

#include "Util/Subject.hpp"
#include "Util/Event.hpp"

namespace RG { namespace Util {
    /**
     * \class Observer
     * \brief
     */
    class Observer {
        public:
            virtual ~Observer();
            virtual void onNotify(const Subject * subject, Event event) = 0;
    };
} }
