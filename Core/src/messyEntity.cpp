#include "messyEntity.hpp"
#include "messyComponent.hpp"

namespace MessyCode2D_Engine {
    MessyEntity::MessyEntity() : Entity(), id(0) { }

    MessyEntity::MessyEntity(std::string name) : Entity(), id(0), name(name) { }

    void MessyEntity::Start()
    {
        for (MessyComponent* comp : GetComponents<MessyComponent>())
            if (comp != NULL) {
                comp->Start();
                comp->hasStarted = true;
        }
    }
    
    void MessyEntity::Update(float deltaTime)
    {
        for (MessyComponent* comp : GetComponents<MessyComponent>())
            if (comp != NULL) {
                if (!comp->hasStarted) {
                    comp->Start();
                    comp->hasStarted = true;
                    return;
                }

                comp->Update(deltaTime);
        }
    }
}
