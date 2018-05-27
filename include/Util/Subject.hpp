#pragma once

#include <set>
#include <vector>

#include "Util/Event.hpp"

namespace RG { namespace Util {
    class Observer;
    /**
     * \class Subject
     * \brief Subject can be observed by Util::Observer
     *
     * This class is can send notifications to all registered observers.
     * 
     */
    class Subject {
        public:
            Subject();
            /**
             * \brief Register new Util::Observer
             *
             * @param observer pointer to Util::Observer to be registed
             * 
             */
            void AddObserver( Observer * observer );

            /**
             * \brief Remove one observer
             *
             * @param observer pointer to Util::Observer to be removed
             * 
             */
            void RemoveObserver( Observer * observer );
        protected:
            /**
             * \brief Send notification to all registered observers
             *
             * @param subject pointer to class calling this method
             * @param event type of notification ( see Util::Event )
             * 
             */
            void Notify( Subject * subject, Event event );
        private:
            std::set<Observer *> m_observers;
            bool m_lock;
            std::vector<Observer *> m_toDelete;
    };
} }
