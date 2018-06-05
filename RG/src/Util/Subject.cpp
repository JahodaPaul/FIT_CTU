#include "Util/Subject.hpp"
#include "Util/Observer.hpp"
#include <iostream>

namespace RG { namespace Util {
    Subject::Subject() 
        :m_lock{ false } { }

    Subject::~Subject() {
        for ( auto & it : m_observers ) {
            it.first->SubjectDead( this );
        }
    }

    void Subject::AddObserver( Observer * observer ) {
        m_observers[ observer ] = true;
    }

    void Subject::RemoveObserver( Observer * observer ) {
        if ( !m_lock ) {
            m_observers.erase( observer );
        }
        else {
            m_observers[ observer ] = false;
        }
    }

    void Subject::Notify( Subject * subject, Event event ) {
        m_lock = true;
        for ( auto & it : m_observers )
            if ( it.second )
                it.first->onNotify( subject, event );
        m_lock = false;

        for ( auto it = m_observers.begin(); it != m_observers.end(); ) {
            if ( ! it->second )
                it = m_observers.erase( it );
            else ++it;
        }
    }
} }
