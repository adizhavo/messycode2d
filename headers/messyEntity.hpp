#ifndef gameEntity_hpp
#define gameEntity_hpp

#include "entity.hpp"
#include <string>

// Game entity, is the base entity of the engine
// For the entity to be in the loop, the entity should be added to the hierarchy (is a Module)

namespace MessyCode2D_Engine {
    class MessyEntity : public ECS::Entity {
    public:
        int id;
        std::string name = "anonymous_game_entity";

        MessyEntity();
        MessyEntity(std::string name);

        void Start();
        void Update(float deltaTime);
    };
}

#endif
