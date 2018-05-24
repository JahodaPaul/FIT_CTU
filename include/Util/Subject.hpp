#pragma once

#include <set>
#include "Util/Event.hpp"

namespace RG { namespace Util {
    class Observer;
    /**
     * \class Subject
     * \brief
     */
    class Subject {
        public:
            void AddObserver( Observer * observer );
            void RemoveObserver( Observer * observer );
        private:
            std::set<Observer *> m_observers;
        protected:
            void Notify( Subject * subject, Event event );
    };
} }
