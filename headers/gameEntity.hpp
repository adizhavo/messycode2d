#ifndef gameEntity_hpp
#define gameEntity_hpp

#include "libs/ecs/entity.hpp"
#include <string>

namespace MessyCode2D_Engine {
    class GameEntity : public ECS::Entity {
    public:
        int id;
        std::string name = "anonymous_game_entity";

        GameEntity();
        GameEntity(std::string name);

        void Start();
        void Update(float deltaTime);
        void Destroy();
    };
}

#endif
