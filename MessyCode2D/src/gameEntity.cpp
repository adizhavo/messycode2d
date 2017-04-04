#include "gameEntity.hpp"
#include "component.hpp"
#include "gameComponent.hpp"

using namespace ECS;

#include <iostream>

namespace MessyCode2D_Engine {
    void GameEntity::Start()
    {
        for (GameComponent* gcmp : GetComponents<GameComponent>()) {
            gcmp->Start();
            gcmp->hasStarted = true;
        }
    }
    
    void GameEntity::Update(float elapseTime)
    {
        for (GameComponent* gcmp : GetComponents<GameComponent>()) {
            if (!gcmp->hasStarted)
            {
                gcmp->Start();
                gcmp->hasStarted = true;
            }
                
            gcmp->Update(elapseTime);
        }
    }
}
