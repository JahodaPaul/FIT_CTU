#include "Model/ContactListener.hpp"

namespace RG {
  namespace Model {
    ContactListener::ContactListener(std::shared_ptr<b2World> world)
    {
      world->SetContactListener(this);
      m_World = world;
    }
  
    ContactListener::~ContactListener(){
      m_World->SetContactListener(nullptr);
    }

    void ContactListener::BeginContact(b2Contact* contact)
    {
      Entity* typeA = static_cast<Entity*>(
          contact->GetFixtureA()->GetBody()->GetUserData());
      Entity* typeB = static_cast<Entity*>(
          contact->GetFixtureB()->GetBody()->GetUserData());

      typeA->RecvAttack(typeB->GetAttackLevel(), m_World);
      typeB->RecvAttack(typeA->GetAttackLevel(), m_World);
    }

    void ContactListener::EndContact(b2Contact* b2Contact) {}
  }
}
