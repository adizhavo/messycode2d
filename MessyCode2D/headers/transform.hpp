#ifndef transform_hpp
#define transform_hpp

#include "gameComponent.hpp"
#include <iostream>

namespace MessyCode2D_Engine {
    class Transform : public GameComponent
    {
    public:
        float xPos, yPos, xAngle, yAngle, xScale, yScale;
        void Start() { }
        
        void Update(float elapseTime) {
            std::cout << "x: " << xPos << ", y: " << yPos << ", elapse time: " << elapseTime << "\n";
        }
        
        RETURN_ID(Transform)
    };
}

#endif
