#include "Util/Subject.hpp"
#include "Util/Observer.hpp"
#include <iostream>

namespace RG { namespace Util {
    void Subject::AddObserver( Observer * observer ) {
        m_observers.insert( observer );
    }
    void Subject::RemoveObserver( Observer * observer ) {
        m_observers.erase( observer );
    }
    void Subject::Notify( Subject * subject, Event event ) {
        for ( auto it : m_observers ) {
            it->onNotify( subject, event );
        }
    }
} }
