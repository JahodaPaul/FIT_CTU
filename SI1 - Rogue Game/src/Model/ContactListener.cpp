#include "Model/ContactListener.hpp"

namespace RG {
  namespace Model {
    ContactListener::ContactListener(std::shared_ptr<b2World> world)
    {
      world->SetContactListener(this);
      m_World = world;
    }

    ContactListener::~ContactListener() { m_World->SetContactListener(nullptr); }

    void ContactListener::BeginContact(b2Contact* contact)
    {
      Object* typeA = static_cast<Object*>(
          contact->GetFixtureA()->GetBody()->GetUserData());
      Object* typeB = static_cast<Object*>(
          contact->GetFixtureB()->GetBody()->GetUserData());

      typeA->Contact();
      typeB->Contact();

      if (typeA->GetType() & typeB->GetAttack())
        typeA->RecvAttack(typeB->GetAttackLevel());

      if (typeB->GetType() & typeA->GetAttack())
        typeB->RecvAttack(typeA->GetAttackLevel());
    }

    void ContactListener::EndContact(b2Contact* b2Contact) {}
  }
}
