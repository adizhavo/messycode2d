#include "headers/editor/messyCode2DEditor.hpp"
#include "headers/messyCode2DConfig.hpp"
#include "headers/scene.hpp"
#include "headers/messyCode2D.hpp"

namespace MessyCode2D_Engine {
    void MessyCode2D::Boot(MessyCodeConfig* config, Scene* scene, MessyCode2DEditor* editor)
    {
        this->config = config;
        this->scene = scene;
        this->editor = editor;
        this->elapseTimer = new QElapsedTimer();
        this->timer = new QTimer();
        this->connect(timer, SIGNAL(timeout()), this, SLOT(Loop()));

        timer->start((1.0 /config->framePerSec));
        elapseTimer->start();
    }
    
    void MessyCode2D::Start()
    {
        this->scene->Start();
    }
    
    void MessyCode2D::Loop()
    {
        this->scene->Update(elapseTimer->elapsed());
        this->editor->Update(elapseTimer->elapsed());
        elapseTimer->restart();
    }
}
