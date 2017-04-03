#include "gameEntity.hpp"
#include "component.hpp"
#include "gameComponent.hpp"

using namespace ECS;

#include <iostream>

namespace MessyCode2D_Engine {
    void GameEntity::Start()
    {
        for (Component* cmp : this->GetComponents()) {
            GameComponent* gcmp = dynamic_cast<GameComponent*>(cmp);
            if (gcmp != NULL)
            {
                gcmp->Start();
                gcmp->hasStarted = true;
            }
        }
    }
    
    void GameEntity::Feed(float elapseTime)
    {
        for (Component* cmp : this->GetComponents()) {
            GameComponent* gcmp = dynamic_cast<GameComponent*>(cmp);
            if (gcmp != NULL)
            {
                if (!gcmp->hasStarted)
                {
                    gcmp->Start();
                    gcmp->hasStarted = true;
                }
                
                gcmp->Feed(elapseTime);
            }
        }
    }
}
