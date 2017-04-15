#ifndef gameComponent_hpp
#define gameComponent_hpp

#include "../gameEntity.hpp"

namespace MessyCode2D_Engine {
    CREATE_COMPONENT(GameComponent)
public:
    bool isEnabled;
    bool hasStarted;

    GameComponent() {
        isEnabled = true;
        hasStarted = true;
    }

    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual ~GameComponent() { }
    ENDCOMP
}

#endif
