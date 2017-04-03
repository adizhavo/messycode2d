#include "messyCode2D.hpp"

namespace MessyCode2D_Engine {
    MessyCode2D::MessyCode2D(Scene* scene, MessyCode2DEditor* editor)
    {
        this->scene = scene;
        this->editor = editor;
    }
    
    void MessyCode2D::Boot()
    {
        this->scene->Boot();
    }
    
    void MessyCode2D::Loop()
    {
        this->scene->Feed();
    }
}
