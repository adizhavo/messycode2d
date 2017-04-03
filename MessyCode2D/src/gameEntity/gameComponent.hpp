#ifndef gameComponent_hpp
#define gameComponent_hpp

#include "component.hpp"

namespace MessyCode2D_Engine {
    CREATE_COMPONENT(GameComponent)
    public:
        bool hasStarted = false;
    
        virtual void Start() = 0;
        virtual void Feed(float elapseTime) = 0;
    ENDCOMP
}

#endif
