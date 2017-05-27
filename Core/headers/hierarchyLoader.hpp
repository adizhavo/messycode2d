#ifndef HIERARCHYDATALOADER_H
#define HIERARCHYDATALOADER_H

#include <vector>
#include <string>

namespace MessyCode2D_Engine {
    // loads and builds the hierarchy

    class HierarchyLoader
    {
    public:
        void LoadHierarchy();
    };

    class EntityData
    {
    // data to recreate an entity
    public:
        int id;
        int parentId;
        std::string name;
        std::vector<std::string> componentsId;
    };
}

#endif // HIERARCHYDATALOADER_H
