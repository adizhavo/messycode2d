#include "transform.hpp"
#include "messyCode2d.hpp"
#include "hierarchy.hpp"
#include "entity.hpp"
#include <cstddef>

namespace MessyCode2D_Engine {
    Transform::Transform() :
        xPos(0), yPos(0), xAngle(0), yAngle(0), xScale(0), yScale(0), parent(NULL) { }

    Transform::~Transform()
    {
        if (parent != NULL)
        {
            parent->RemoveChild(this);
            parent = 0;
        }

        for (Transform* tr : childs)
        {
            delete tr;
        }

        childs.clear();
        entity->RemoveComponent(unique_id());

        MessyCode2D::GetModule<Hierarchy>()->Refresh();
    }

    void Transform::Start() { }

    void Transform::Update(float deltaTime) { }
    
    void Transform::SetParent(Transform* parent)
    {
        if (this->parent != NULL)
            this->parent->RemoveChild(this);
        
        this->parent = parent;
        
        if (this->parent != NULL)
            this->parent->AddChild(this);

        MessyCode2D::GetModule<Hierarchy>()->Refresh();
    }
    
    Transform* Transform::GetParent()
    {
        return parent;
    }

    MessyEntity* Transform::GetEntity()
    {
        return static_cast<MessyEntity*>(entity);
    }
    
    void Transform::AddChild(Transform* child)
    {
        childs.push_back(child);
    }
    
    void Transform::RemoveChild(Transform* child)
    {
        childs.erase(std::remove(childs.begin(), childs.end(), child), childs.end());
        child->SetParent(NULL);
    }
    
    std::vector<Transform*> Transform::GetChildren()
    {
        return childs;
    }
}
