#ifndef transform_hpp
#define transform_hpp

#include "messyComponent.hpp"
#include "messySerializer.hpp"
#include <vector>

// Transform component of the engine
// Used to locate an entity in space

namespace MessyCode2D_Engine {
    class Transform : public MessyComponent, public MessySerializer
    {
    public:
        float xPos, yPos, xAngle, yAngle, xScale, yScale;

        START_SERIALIZER(3)
        SERIALIZE(bool, isEnabled) AND
        SERIALIZE(float, xPos) AND
        SERIALIZE(float, yPos)
        END_SERIALIZER

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
