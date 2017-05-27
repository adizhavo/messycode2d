#include "messyEntity.hpp"
#include "messyComponent.hpp"

namespace MessyCode2D_Engine {
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
