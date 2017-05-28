#ifndef HIERARCHYDATALOADER_H
#define HIERARCHYDATALOADER_H

#include <vector>
#include <string>

// loads and builds the hierarchy

namespace MessyCode2D_Engine {
    class ComponentLoader;

    class HierarchyLoader
    {
    public:
        HierarchyLoader();
        ~HierarchyLoader();
        void SaveHierarchy();
        void LoadHierarchy();
    private:
        ComponentLoader* componentLoader;
    };
}

#endif // HIERARCHYDATALOADER_H
