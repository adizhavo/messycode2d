#include "messyCode2D.hpp"
#include "messyCode2DEditor.hpp"
#include "messyCode2DConfig.hpp"
#include "scene.hpp"
#include "timer.hpp"

namespace MessyCode2D_Engine {
    MessyCode2D::MessyCode2D(MessyCodeConfig* config, Scene* scene, MessyCode2DEditor* editor)
    {
        this->config = config;
        this->scene = scene;
        this->editor = editor;
        this->timer = new Timer();
    }
    
    void MessyCode2D::Start()
    {
        this->scene->Start();
    }
    
    void MessyCode2D::Loop()
    {
        this->timer->start();
        while(true)
        {
            if (ShoulFeed())
            {
                float elapseTime = this->timer->getTime();
                
                this->scene->Update(elapseTime);
                this->editor->Update(elapseTime);
                
                this->timer->reset();
            }
        }
    }
    
    bool MessyCode2D::ShoulFeed()
    {
        return this->timer->getTime() > (1.0 / this->config->framePerSec);
    }
}
