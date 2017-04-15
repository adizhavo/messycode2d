#include "headers/gameEntity.hpp"
#include "headers/components/gameComponent.hpp"

namespace MessyCode2D_Engine {
    GameEntity::GameEntity()
    {
        this->id = 0;
        this->name = "anonymous_game_entity";
    }

    GameEntity::GameEntity(std::string name)
    {
        this->id = 0;
        this->name = name;
    }

    void GameEntity::Start()
    {
        for (GameComponent* gcmp : GetComponents<GameComponent>()) {
            gcmp->Start();
            gcmp->hasStarted = true;
        }
    }
    
    void GameEntity::Update(float deltaTime)
    {
        for (GameComponent* gcmp : GetComponents<GameComponent>()) {
            if (!gcmp->hasStarted)
            {
                gcmp->Start();
                gcmp->hasStarted = true;
            }
                
            gcmp->Update(deltaTime);
        }
    }
    
    void GameEntity::Destroy()
    {
        for (GameComponent* gcmp : GetComponents<GameComponent>())
        {
            delete gcmp;
            gcmp = NULL;
        }
        
        RemoveAllComponents();
    }
}
