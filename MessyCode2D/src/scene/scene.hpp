#ifndef scene_hpp
#define scene_hpp

#include <vector>

namespace MessyCode2D_Engine {
    class GameEntity;
    
    class Scene
    {
    public:
        void Build();
        void Boot();
        void Feed(float elapseTime);
    private:
        std::vector<GameEntity*> gameEntities;
    };
}
#endif
