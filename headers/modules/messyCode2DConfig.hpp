#ifndef messyCode2DConfig_hpp
#define messyCode2DConfig_hpp

#include "messyModule.hpp"

namespace MessyCode2D_Engine {
    class MessyCodeConfig : public MessyModule
    {
    public:
        float framePerSec;

        void Boot()
        {
            framePerSec = 30;
        }

        void Start() { }
        void Update(float deltaTime) { }
        ~MessyCodeConfig() { }
    };
}

#endif
