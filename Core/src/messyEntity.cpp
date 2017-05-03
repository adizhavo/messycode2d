#include "messyEntity.hpp"
#include "messyComponent.hpp"

namespace MessyCode2D_Engine {
    MessyEntity::MessyEntity()
    {
        // Is not added yet to the hierarchy
        this->id = -1;
    }

    MessyEntity::MessyEntity(std::string name)
    {
        this->id = 0;
        this->name = name;
    }

    void MessyEntity::Start()
    {
        for (MessyComponent* mc : GetComponents<MessyComponent>()) {
            mc->Start();
            mc->hasStarted = true;
        }
    }
    
    void MessyEntity::Update(float deltaTime)
    {
        for (MessyComponent* mc : GetComponents<MessyComponent>()) {
            if (!mc->hasStarted)
            {
                mc->Start();
                mc->hasStarted = true;
            }
                
            mc->Update(deltaTime);
        }
    }
}
