#include "Util/Observer.hpp"

namespace RG { namespace Util {
    Observer::Observer() : m_lock{ false } {}

    Observer::~Observer() {
        m_lock = true;
        for ( auto it : m_Observing )
            it->RemoveObserver( this );
        m_lock = false;
    }

    void Observer::onNotify(Subject * subject, Event event) {
        std::string msg = std::string("Call of virtual method in observer, remov, event: \'") + std::to_string( event ) + "\' removing observer.";
        mainLog.Error( msg );
        subject->RemoveObserver( this );
    }

    void Observer::SubjectDead( Subject * subject ) {
        if ( !m_lock )
            m_Observing.erase( subject );
    }

    void Observer::SubscribeTo( Subject * subject ) {
        m_Observing.insert( subject );
        subject->AddObserver( this );
    }

} }
