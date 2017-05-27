#ifndef HIERARCHYDATALOADER_H
#define HIERARCHYDATALOADER_H

#include "messyModule.hpp"
#include <fstream>
#include <vector>

#include <string>
#include "messySerializer.hpp"

namespace MessyCode2D_Engine {

    // loads and builds the hierarchy

    class EntityData
    {
        // data to recreate an entity

    public:
        int id;
        int parentId;
        std::string name;
        std::vector<std::string> componentsId;
    };

    class HierarchyLoader : public MessyModule
    {
    public:
        void Boot();
        void Start();
        void Update(float elapseTime);
        void LoadHierarchy();
        ~HierarchyLoader();

    private:
        std::ifstream* reader;
    };
}

#endif // HIERARCHYDATALOADER_H
