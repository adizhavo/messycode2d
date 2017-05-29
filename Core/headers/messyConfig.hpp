#ifndef messyCode2DConfig_hpp
#define messyCode2DConfig_hpp

#include <string>

namespace MessyCode2D_Engine {
    class MessyCodeConfig
    {
    private:
        float framePerSec;
        std::string componentManifestPath;
        std::string hierarchyFilePath;

    public:
        MessyCodeConfig()
        {
            framePerSec = 30;
            componentManifestPath = "./manifest.cpp";
            hierarchyFilePath = "../../../hierarchy.json";
        }

        float fps() { return framePerSec; }
        std::string manifest() { return componentManifestPath; }
        std::string hierarchy() { return hierarchyFilePath; }
    };
}

#endif
