#include "scene.hpp"
#include <iostream>

#include "gameEntity.hpp"
#include "transform.hpp"

namespace MessyCode2D_Engine {
    void Scene::Build()
    {
        // Load sample entities to get the system started
        GameEntity ent1;
        GameEntity ent2;
        GameEntity ent3;
        
        Transform tr;
        ent1.AddComponent(&tr);
        ent2.AddComponent(&tr);
        ent3.AddComponent(&tr);
        
        this->gameEntities.push_back(&ent1);
        this->gameEntities.push_back(&ent2);
        this->gameEntities.push_back(&ent3);
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
        
        std::cout << "Scene feeded, elapse time: " << elapseTime << "\n";
    }
}
