#include "messyEntity.hpp"
#include "messyComponent.hpp"

namespace MessyCode2D_Engine {
    MessyEntity::MessyEntity()
    {
        this->id = 0;
        this->name = "anonymous_messy_entity";
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
