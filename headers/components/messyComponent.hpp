#ifndef gameComponent_hpp
#define gameComponent_hpp

#include "component.hpp"
#include "editorinspector.hpp"

namespace MessyCode2D_Engine {
    CREATE_ABSTRACT_COMPONENT(MessyComponent)
public:

    EDITOR_SERIALIZABLE
    SERIALIZE_BOOL(isEnabled, true)

    bool hasStarted;

    MessyComponent() {
        SerializeisEnabled();

        isEnabled = true;
        hasStarted = true;
    }

    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual ~MessyComponent() { }
    ENDCOMP
}

#endif
