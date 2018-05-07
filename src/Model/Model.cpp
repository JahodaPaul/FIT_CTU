#include "Model/Model.hpp"

namespace RG {
  namespace Model {
    Model::Model():m_GameWorld(GameWorld("Novy Svet")){
    }

    Model::~Model(){}

    void Move(){}

    const RG::Model::Room& Model::GetCurrentRoom ( void ) const {
      return RG::Model::Room(0,0); // FIXME (vanda)
    }

    std::pair<float, float> Model::GetPlayerPosition ( void ) const {
      return {0,0}; // FIXME (vanda)
    }

    float Model::GetPlayerRotation ( void ) const {
      return 0; // FIXME (vanda)
    }

    float Model::GetPlayerRadius ( void ) const {
      return 0; // FIXME (vanda)
    }

      int Model::GetRoomId (void) const{
          return 0; //TODO (vanda)
      }

      int Model::GetFloorLevel ( void ) const{
          return 0; //TODO (vanda)
      }

      std::vector<bool> Model::GetRoomDoors (int floorID) const{//TODO FIXME (vanda)
          //dummy return
          std::vector<bool> dummy;
          for(int i = 0;i<4;i++){
              dummy.push_back(true);
          }
          return dummy;
      }
  }
}
