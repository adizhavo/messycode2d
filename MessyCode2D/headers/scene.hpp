#ifndef scene_hpp
#define scene_hpp

#include <vector>

namespace MessyCode2D_Engine {
    class GameEntity;
    
    class Scene
    {
    public:
        void Build();
        void Start();
        void Update(float elapseTime);
    private:
        std::vector<GameEntity*> gameEntities;
    };
}
#endif
