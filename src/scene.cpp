#include "headers/scene.hpp"

// Temp code
#include "headers/components/transform.hpp"
#include "headers/gameEntity.hpp"

namespace MessyCode2D_Engine {
    Scene*Scene::instance;
    
    void Scene::Build()
    {
        Scene::instance = this;
        
        // Temp code
        // Load sample entities to get the system started
        GameEntity* ent1 = new GameEntity();
        GameEntity* ent2 = new GameEntity();
        GameEntity* ent3 = new GameEntity();
        
        Transform* tr = new Transform();
        Transform* tr2 = new Transform();
        Transform* tr3 = new Transform();
        ent1->AddComponent(tr);
        ent2->AddComponent(tr2);
        ent3->AddComponent(tr3);
        
        AddGameEntity(ent1);
        AddGameEntity(ent2);
        AddGameEntity(ent3);
    }
    
    void Scene::Start()
    {
        for (GameEntity* ge : this->gameEntities)
            ge->Start();
    }
    
    void Scene::Update(float deltaTime)
    {
        for (GameEntity* ge : this->gameEntities)
            ge->Update(deltaTime);
    }
    
    void Scene::AddGameEntity(GameEntity* ge)
    {
        this->gameEntities.push_back(ge);
        this->lastEntityId ++;
        ge->id = this->lastEntityId;
    }
    
    void Scene::RemoveGameEntity(GameEntity* ge)
    {
        this->gameEntities.erase(std::remove(this->gameEntities.begin(), this->gameEntities.end(), ge), this->gameEntities.end());
        ge->Destroy();
        delete ge;
        ge = NULL;
    }
}