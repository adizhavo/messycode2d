#ifndef gameComponent_hpp
#define gameComponent_hpp

#include "component.hpp"
#include "gameEntity.hpp"

namespace MessyCode2D_Engine {
    CREATE_COMPONENT(GameComponent)
    public:
        bool hasStarted = false;
    
        virtual void Start() = 0;
        virtual void Update(float elapseTime) = 0;
        virtual void Destroy() = 0;
    
        GameEntity* GetGameEntity()
        {
            return static_cast<GameEntity*>(entity);
        }
    ENDCOMP
}

#endif
