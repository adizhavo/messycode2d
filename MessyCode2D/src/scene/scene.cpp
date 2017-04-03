#include "scene.hpp"
#include <iostream>

namespace MessyCode2D_Engine {
    void Scene::Build()
    {
        // Load sample entities to get the system started
        Entity ent1;
        Entity ent2;
        Entity ent3;
        
        this->gameEntities.push_back(&ent1);
        this->gameEntities.push_back(&ent2);
        this->gameEntities.push_back(&ent3);
    }
    
    void Scene::Boot()
    {
        std::cout << "Scene booted\n";
    }
    
    void Scene::Feed()
    {
        std::cout << "Scene feeded\n";
    }
}
