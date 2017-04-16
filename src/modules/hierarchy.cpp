#include "hierarchy.hpp"

// Temp code
#include "transform.hpp"
#include "messyEntity.hpp"

namespace MessyCode2D_Engine {
    Hierarchy::~Hierarchy()
    {
        for (MessyEntity* me : this->messyEntities)
            delete me;

        this->messyEntities.clear();
    }

    void Hierarchy::Boot()
    {
        this->lastEntityId = 0;
        // Temp code
        // Load sample entities to get the system started
        MessyEntity* ent1 = new MessyEntity();
        MessyEntity* ent2 = new MessyEntity();
        MessyEntity* ent3 = new MessyEntity();

        Transform* tr1 = new Transform();
        Transform* tr2 = new Transform();
        Transform* tr3 = new Transform();
        ent1->AddComponent(tr1);
        ent2->AddComponent(tr2);
        ent3->AddComponent(tr3);

        tr3->SetParent(tr2);
        tr2->SetParent(tr1);

        AddMessyEntity(ent1);
        AddMessyEntity(ent2);
        AddMessyEntity(ent3);
    }
    
    void Hierarchy::Start()
    {
        for (MessyEntity* me : this->messyEntities)
            me->Start();
    }

    void Hierarchy::Update(float deltaTime)
    {
        for (MessyEntity* me : this->messyEntities)
            me->Update(deltaTime);
    }

    void Hierarchy::AddMessyEntity(MessyEntity* me)
    {
        this->messyEntities.push_back(me);
        this->lastEntityId ++;
        me->id = this->lastEntityId;
        Refresh();
    }
    
    void Hierarchy::RemoveMessyEntity(MessyEntity* me)
    {
        this->messyEntities.erase(std::remove(this->messyEntities.begin(), this->messyEntities.end(), me), this->messyEntities.end());
        delete me;
        Refresh();
    }

    void Hierarchy::Refresh()
    {
        emit UpdateSignal();
    }
}
