#include "headers/components/transform.hpp"

#include <iostream>

namespace MessyCode2D_Engine {
    void Transform::Start() { }

    void Transform::Update(float deltaTime) { }
    
    void Transform::Destroy()
    {
        if (this->parent != NULL)
        {
            this->parent->RemoveChild(this);
            this->parent = 0;
        }
        
        for (Transform* tr : this->childs)
        {
            tr->Destroy();
        }
        
        this->entity->RemoveComponent<Transform>();
    }
    
    void Transform::SetParent(Transform* parent)
    {
        if (this->parent != NULL)
            this->parent->RemoveChild(this);
        
        this->parent = parent;
        
        if (this->parent != NULL)
            this->parent->AddChild(this);
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
