#include "scene.hpp"
#include <iostream>

#include "gameEntity.hpp"
#include "transform.hpp"

#include <iostream>

namespace MessyCode2D_Engine {
    void Scene::Build()
    {
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
        
        this->gameEntities.push_back(ent1);
        this->gameEntities.push_back(ent2);
        this->gameEntities.push_back(ent3);
    }
    
    void Scene::Start()
    {
        for (GameEntity* ge : this->gameEntities)
            ge->Start();
    }
    
    void Scene::Update(float elapseTime)
    {
        for (GameEntity* ge : this->gameEntities)
            ge->Update(elapseTime);
    }
}
