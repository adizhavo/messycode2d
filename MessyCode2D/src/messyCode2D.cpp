#include "messyCode2D.hpp"

namespace MessyCode2D_Engine {
    MessyCode2D::MessyCode2D(MessyCodeConfig* config, Scene* scene, MessyCode2DEditor* editor)
    {
        this->config = config;
        this->scene = scene;
        this->editor = editor;
        this->timer = new Timer();
    }
    
    void MessyCode2D::Boot()
    {
        this->scene->Boot();
    }
    
    void MessyCode2D::Loop()
    {
        this->timer->start();
        while(true)
        {
            if (ShoulFeed())
            {
                float elapseTime = this->timer->getTime();
                
                this->scene->Feed(elapseTime);
                this->editor->Feed(elapseTime);
                
                this->timer->reset();
            }
        }
    }
    
    bool MessyCode2D::ShoulFeed()
    {
        return this->timer->getTime() > (1.0 / this->config->framePerSec);
    }
}
