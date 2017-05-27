#ifndef gameComponent_hpp
#define gameComponent_hpp

#include <component.hpp>

// Base component of the engine

namespace MessyCode2D_Engine {
    CREATE_ABSTRACT_COMPONENT(MessyComponent)
public:
    bool isEnabled;
    bool hasStarted;

    MessyComponent() {
        isEnabled = true;
        hasStarted = true;
    }

    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual ~MessyComponent() { }
    ENDCOMP
}

#endif
