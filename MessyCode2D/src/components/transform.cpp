#include "transform.hpp"

namespace MessyCode2D_Engine {
    void Transform::Start() { }

    void Transform::Update(float elapseTime) { }
    
    void Transform::Destroy()
    {
        if (this->parent != NULL)
        {
            this->parent->RemoveChild(this);
            this->parent = 0;
        }
        
        for (Transform* tr : this->childs)
        {
            tr->GetGameEntity()->Destroy();
            tr->Destroy();
        }
    }
    
    void Transform::SetParent(Transform* parent)
    {
        if (this->parent != NULL)
            this->parent->RemoveChild(this);
        
        this->parent = parent;
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
    }
    
    std::vector<Transform*> Transform::GetChildren()
    {
        return this->childs;
    }
}
