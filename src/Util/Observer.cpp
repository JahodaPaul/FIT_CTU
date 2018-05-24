#include "Util/Observer.hpp"

namespace RG { namespace Util {
    //TODO(vojta) make it pure virtual again and unsubscribre all observers when room is changed ( probably need previous room )
    void Observer::onNotify(Subject * subject, Event event) {
        std::string msg = std::string("!!!!!!!CALL OF VIRTUAL METHOD IN OBSERVER, EVENT: \'") + std::to_string( event ) + "\' !!!!!!!";
        mainLog.Error( msg );
    }
} }
