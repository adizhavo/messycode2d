#ifndef hierarchy_hpp
#define hierarchy_hpp

#include <vector>
#include <QObject>
#include "messyModule.hpp"
#include "componentLoader.hpp"
#include <filter.hpp>
#include <string>

// Holds all the entity with hierarchies in the scene
// Can be considered as the world of the engine

namespace MessyCode2D_Engine {
    using namespace ECS;

    class HierarchyLoader;
    class MessyEntity;

    class Hierarchy : public QObject, public MessyModule
    {
        Q_OBJECT

    public:
        void Boot();
        void Start();
        void Update(float deltaTime);
        Hierarchy();
        ~Hierarchy();

        void Refresh();

        // Use only this method to add entities in the engine
        // ECS is a shared library and holds a static variable used for the entity matching
        // the matching system will be moved in the engine later
        MessyEntity* AddMessyEntity(std::string name = "messyEntity");

        void RemoveMessyEntity(MessyEntity* ge);
        void RemoveMessyEntity(int id);
        MessyEntity* GetMessyEntity(int id);
        MessyEntity* GetMessyEntity(const std::string name);
        std::vector<MessyEntity*> GetMessyEntities(const std::string name);
        std::vector<MessyEntity*> GetMessyEntities(Filter f);
        std::vector<Entity*> GetEntities(Filter f);

        void LoadPrefab(const std::string path);

    private:
        std::vector<MessyEntity*> messyEntities;
        int lastEntityId;
        ComponentLoader* comp_loader;

        void SaveHierarchy();
        void LoadHierarchy();

    signals:
        void UpdateSignal();
    };
}
#endif
