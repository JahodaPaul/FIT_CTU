#include "Util/Observer.hpp"

namespace RG { namespace Util {
    //TODO(vojta) make it pure virtual again and unsubscribre all observers when room is changed ( probably need previous room )
    void Observer::onNotify(Subject * subject, Event event) {
        std::string msg = std::string("Call of virtual method in observer, remov, event: \'") + std::to_string( event ) + "\' removing observer.";
        mainLog.Error( msg );
        subject->RemoveObserver( this );
    }
} }
