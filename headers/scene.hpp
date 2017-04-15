#ifndef scene_hpp
#define scene_hpp

#include <vector>
#include <QObject>

namespace MessyCode2D_Engine {
    class GameEntity;
    
    class Scene : public QObject
    {
        Q_OBJECT

    public:
        static Scene* instance;
        
        void Build();
        void Start();
        void Refresh();
        void Update(float deltaTime);
        void AddGameEntity(GameEntity* ge);
        void RemoveGameEntity(GameEntity* ge);
        Scene();
        ~Scene();

    private:
        std::vector<GameEntity*> gameEntities;
        int lastEntityId;

    signals:
        void UpdateScene();
    };
}
#endif
