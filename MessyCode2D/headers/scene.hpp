#ifndef scene_hpp
#define scene_hpp

#include <vector>

namespace MessyCode2D_Engine {
    class GameEntity;
    
    class Scene
    {
    public:
        static Scene* instance;
        
        void Build();
        void Start();
        void Update(float deltaTime);
        void AddGameEntity(GameEntity* ge);
        void RemoveGameEntity(GameEntity* ge);
    private:
        std::vector<GameEntity*> gameEntities;
    };
}
#endif
