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

        void Boot()
        {
            framePerSec = 30;
            componentManifestPath = "./manifest.cpp";
        }

        void Start() { }
        void Update(float deltaTime) { }
        ~MessyCodeConfig() { }
    };
}

#endif
