#ifndef transform_hpp
#define transform_hpp

#include "messyComponent.hpp"
#include <vector>

namespace MessyCode2D_Engine {
    class Transform : public MessyComponent
    {
    public:
        float xPos, yPos, xAngle, yAngle, xScale, yScale;

        Transform();
        ~Transform();

        void Start();
        void Update(float deltaTime);
        void SetParent(Transform* parent);
        Transform* GetParent();
        void AddChild(Transform* child);
        void RemoveChild(Transform* child);
        std::vector<Transform*> GetChildren();
        RETURN_ID(Transform)
    private:
        Transform* parent;
        std::vector<Transform*> childs;
    };
}

#endif
