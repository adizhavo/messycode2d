#ifndef transform_hpp
#define transform_hpp

#include "gameComponent.hpp"

namespace MessyCode2D_Engine {
    class Transform : public GameComponent
    {
    public:
        float xPos, yPos, xAngle, yAngle, xScale, yScale;
        void Start();
        void Feed(float elapseTime);
    };
    
    void Transform::Start() { }
    
    void Transform::Feed(float elapseTime) { }
}

#endif
