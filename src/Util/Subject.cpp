#include "Util/Subject.hpp"
#include "Util/Observer.hpp"
#include <iostream>

namespace RG { namespace Util {
    Subject::Subject() 
        :m_lock{ false } { }

    void Subject::AddObserver( Observer * observer ) {
            m_observers.insert( observer );
        }
    void Subject::RemoveObserver( Observer * observer ) {
        if ( !m_lock )
            m_observers.erase( observer );
        else
            m_toDelete.push_back( observer );
    }
    void Subject::Notify( Subject * subject, Event event ) {
        m_lock = true;
        for ( auto it : m_observers )
            it->onNotify( subject, event );
        m_lock = false;

        for ( auto it : m_toDelete )
            m_observers.erase( &(*it) );
        m_toDelete.clear();
    }
} }
