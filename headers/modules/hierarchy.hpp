#ifndef scene_hpp
#define scene_hpp

#include <vector>
#include <QObject>
#include "messyModule.hpp"

namespace MessyCode2D_Engine {
    class MessyEntity;
    
    class Hierarchy : public QObject, public MessyModule
    {
        Q_OBJECT

    public:
        void Boot();
        void Start();
        void Update(float deltaTime);
        void Refresh();
        void AddMessyEntity(MessyEntity* ge);
        void RemoveMessyEntity(MessyEntity* ge);
        void RemoveMessyEntity(int id);
        ~Hierarchy();

    private:
        std::vector<MessyEntity*> messyEntities;
        int lastEntityId;

    signals:
        void UpdateSignal();
    };
}
#endif