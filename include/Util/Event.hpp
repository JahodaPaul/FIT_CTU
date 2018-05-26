#pragma once

namespace RG {
  namespace Util {
    //! \enum Event
    /*!
     *  \brief enumeration of game events used by Observer and Subject for comunication
     */
    enum Event {
        ENTITY_MOVE, /**< Model::Entity has moves, should be send by Model::Entity */
        ENTITY_DEAD, /**< Model::Entity has died, should be send by Model::Entity */
        ROOM_CHANGE, /**< room has changed, should be send by Model::Floor */
        WINDOW_RESIZE, /**< window has been resized */
        ENTITY_DAMAGED, /**< Model::Entity has been damadged, should be send by Model::Entity */
        ITEM_SOLD, /**< Item has been sold */
        FLOOR_UP, /**< Player used stairs to go up */
        FLOOR_DOWN /**< Player used stairs to go down */
    };
  }
}
