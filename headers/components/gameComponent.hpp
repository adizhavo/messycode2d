#ifndef gameComponent_hpp
#define gameComponent_hpp

#include "../gameEntity.hpp"

namespace MessyCode2D_Engine {
    CREATE_COMPONENT(GameComponent)
public:
    bool isEnabled = true;
    bool hasStarted = false;
    
    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Destroy() = 0;
    
    void Cleanup()
    {
        this->Destroy();
    }
    
    ~GameComponent()
    {
        this->Cleanup();
    }
    ENDCOMP
}

#endif
