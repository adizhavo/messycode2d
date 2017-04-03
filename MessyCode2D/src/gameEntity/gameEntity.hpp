#ifndef gameEntity_hpp
#define gameEntity_hpp

#include "entity.hpp"

namespace MessyCode2D_Engine {
    class GameEntity : public ECS::Entity {
    public:
        void Start();
        void Feed(float elapseTime);
    };
}

#endif
