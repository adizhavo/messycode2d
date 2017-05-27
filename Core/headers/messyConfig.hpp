#ifndef messyCode2DConfig_hpp
#define messyCode2DConfig_hpp

#include "messyModule.hpp"
#include <string>

namespace MessyCode2D_Engine {
    class MessyCodeConfig : public MessyModule
    {
    public:
        float framePerSec;
        std::string componentManifestPath;
        std::string hierarchyFilePath;

        void Boot()
        {
            framePerSec = 30;
            componentManifestPath = "./manifest.cpp";
            hierarchyFilePath = "../../../hierarchy.json";
        }

        void Start() { }
        void Update(float deltaTime) { }
        ~MessyCodeConfig() { }
    };
}

#endif
