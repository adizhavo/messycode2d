#ifndef gameEntity_hpp
#define gameEntity_hpp

#include "entity.hpp"
#include <string>

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
