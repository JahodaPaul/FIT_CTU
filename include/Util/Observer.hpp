#pragma once

#include <set>

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
             * \brief Constructor
             */
            Observer();

            /**
             * \brief Destructor
             *
             * This will unsubscribe from all subsribed Subjects whitch are still alive.
             */
            virtual ~Observer();

            /**
             * \brief This method is called from Util::Subject and recieves notifications.
             * 
             * @param subject pointer to caller
             * @param event type of notification send ( see Util::Event )
             * 
             */
            virtual void onNotify(Subject * subject, Event event);

            /**
             * \brief Notify Observer about end of live of subject, whitch we subscribed to.
             * 
             * @param subject subject
             */
            void SubjectDead( Subject * subject );

            /**
             * \brief Subscripe to subject for notifications.
             * 
             * @param subject subject to be subscribed to
             */
            void SubscribeTo( Subject * subject );
        private:
            std::set<Subject*> m_Observing;
            bool m_lock;
    };
} }
