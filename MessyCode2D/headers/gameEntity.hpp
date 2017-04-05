#ifndef gameEntity_hpp
#define gameEntity_hpp

#include "entity.hpp"
#include <string>

namespace MessyCode2D_Engine {
    class GameEntity : public ECS::Entity {
    public:
        std::string name = "anonymous_game_entity";
        void Start();
        void Update(float elapseTime);
        void Destroy();
    };
}

#endif
