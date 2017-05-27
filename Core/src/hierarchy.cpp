#include "hierarchy.hpp"
#include "messyCode2D.hpp"
#include "hierarchyLoader.hpp"
#include "messyEntity.hpp"
#include <cstddef>

namespace MessyCode2D_Engine {
    Hierarchy::Hierarchy()
    {
        h_loader = new HierarchyLoader();
    }

    Hierarchy::~Hierarchy()
    {
        for (MessyEntity* me : messyEntities)
            if (me != NULL)
                delete me;

        messyEntities.clear();
        delete h_loader;
    }

    void Hierarchy::Boot()
    {
        this->lastEntityId = 0;
        h_loader->LoadHierarchy();
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
