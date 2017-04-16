#include "transform.hpp"
#include "messyCode2D.hpp"
#include "hierarchy.hpp"

namespace MessyCode2D_Engine {
    Transform::Transform()
    {
        this->xPos = 0;
        this->yPos = 0;
        this->xAngle = 0;
        this->yAngle = 0;
        this->xScale = 0;
        this->yScale = 0;
    }

    Transform::~Transform()
    {
        if (this->parent != NULL)
        {
            this->parent->RemoveChild(this);
            this->parent = 0;
        }

        for (Transform* tr : this->childs)
        {
            delete tr;
        }

        this->childs.clear();
        this->entity->RemoveComponent(unique_id());

        MessyCode2D::instance->GetModule<Hierarchy>()->Refresh();
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

        MessyCode2D::instance->GetModule<Hierarchy>()->Refresh();
    }
    
    Transform* Transform::GetParent()
    {
        return this->parent;
    }
    
    void Transform::AddChild(Transform* child)
    {
        this->childs.push_back(child);
    }
    
    void Transform::RemoveChild(Transform* child)
    {
        this->childs.erase(std::remove(this->childs.begin(), this->childs.end(), child), this->childs.end());
        child->SetParent(NULL);
    }
    
    std::vector<Transform*> Transform::GetChildren()
    {
        return this->childs;
    }
}
