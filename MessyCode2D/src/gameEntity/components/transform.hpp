#ifndef transform_hpp
#define transform_hpp

#include "gameComponent.hpp"

namespace MessyCode2D_Engine {
    class Transform : public GameComponent
    {
    public:
        float xPos, yPos, xAngle, yAngle, xScale, yScale;
        void Start();
        void Update(float elapseTime);
    };
    
    void Transform::Start() { }
    
    void Transform::Update(float elapseTime) { }
}

#endif
