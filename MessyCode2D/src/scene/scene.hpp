#ifndef scene_hpp
#define scene_hpp

#include <vector>
#include "entity.hpp"

using namespace ECS;

namespace MessyCode2D_Engine {
    class Scene
    {
    public:
        void Build();
        void Boot();
        void Feed(float elapseTime);
    private:
        std::vector<Entity*> gameEntities;
    };
}
#endif
