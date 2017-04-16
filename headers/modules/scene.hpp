#ifndef scene_hpp
#define scene_hpp

#include <vector>
#include <QObject>
#include "messyModule.hpp"

namespace MessyCode2D_Engine {
    class GameEntity;
    
    class Scene : public QObject, public MessyModule
    {
        Q_OBJECT

    public:
        void Boot();
        void Start();
        void Update(float deltaTime);
        void Refresh();
        void AddGameEntity(GameEntity* ge);
        void RemoveGameEntity(GameEntity* ge);
        ~Scene();

    private:
        std::vector<GameEntity*> gameEntities;
        int lastEntityId;

    signals:
        void UpdateSignal();
    };
}
#endif
