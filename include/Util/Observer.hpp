#pragma once

#include "Util/Subject.hpp"
#include "Util/Event.hpp"
#include "common.hpp"

namespace RG { namespace Util {
    /**
     * \class Observer
     * \brief Observer is getting notifications from Subjects.
     *
     * This class is used to register to Util::Subject as observer and then it can recieve notifications from Util::Subject;
     * To use it you have to override onNotify method.
     * 
     */
    class Observer {
        public:
            /**
             * Destructor
             */
            virtual ~Observer() {}

            /**
             * This method is called from Util::Subject and recieves notifications.
             * 
             * @param subject pointer to caller
             * @param event type of notification send ( see Util::Event )
             * 
             */
            virtual void onNotify(Subject * subject, Event event);
    };
} }
