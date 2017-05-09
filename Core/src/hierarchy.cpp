#include "hierarchy.hpp"
#include "messyEntity.hpp"
#include <cstddef>

// Temp code
// #include "transform.hpp"

namespace MessyCode2D_Engine {
    Hierarchy::~Hierarchy()
    {
        for (MessyEntity* me : messyEntities)
            if (me != NULL)
                delete me;

        messyEntities.clear();
    }

    void Hierarchy::Boot()
    {
        this->lastEntityId = 0;
        // Temp code
        // Load sample entities to get the system started
        // MessyEntity* ent1 = new MessyEntity("ent 1");
        // MessyEntity* ent2 = new MessyEntity("ent 2");
        // MessyEntity* ent3 = new MessyEntity("ent 3");
        //
        // Transform* tr1 = new Transform();
        // Transform* tr2 = new Transform();
        // Transform* tr3 = new Transform();
        // ent1->AddComponent(tr1);
        // ent2->AddComponent(tr2);
        // ent3->AddComponent(tr3);
        //
        // tr3->SetParent(tr2);
        // tr2->SetParent(tr1);
        //
        // AddMessyEntity(ent1);
        // AddMessyEntity(ent2);
        // AddMessyEntity(ent3);
    }
    
    void Hierarchy::Start()
    {
        for (MessyEntity* me : messyEntities)
            me->Start();
    }

    void Hierarchy::Update(float deltaTime)
    {
        for (MessyEntity* me : messyEntities)
            me->Update(deltaTime);
    }

    void Hierarchy::AddMessyEntity(MessyEntity* me)
    {
        messyEntities.push_back(me);
        lastEntityId ++;
        me->id = lastEntityId;
        Refresh();
    }
    
    void Hierarchy::RemoveMessyEntity(MessyEntity* me)
    {
        messyEntities.erase(std::remove(messyEntities.begin(), messyEntities.end(), me), messyEntities.end());
        delete me;
        Refresh();
    }

    void Hierarchy::RemoveMessyEntity(int id)
    {
        for (MessyEntity* me : messyEntities)
            if (me->id == id)
            {
                RemoveMessyEntity(me);
                break;
            }
    }

    void Hierarchy::Refresh()
    {
        emit UpdateSignal();
    }
}
