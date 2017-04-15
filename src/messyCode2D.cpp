#include "headers/editor/messyCode2DEditor.hpp"
#include "headers/messyCode2DConfig.hpp"
#include "headers/scene.hpp"
#include "headers/messyCode2D.hpp"

namespace MessyCode2D_Engine {
    MessyCode2D::~MessyCode2D()
    {
        delete config;
        delete scene;
        delete elapseTimer;
        delete timer;
    }

    void MessyCode2D::Boot(MessyCodeConfig* config, Scene* scene)
    {
        this->config = config;
        this->scene = scene;
        this->elapseTimer = new QElapsedTimer();
        this->timer = new QTimer();
        this->connect(timer, SIGNAL(timeout()), this, SLOT(Loop()));

        scene->Build();
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
        elapseTimer->restart();
    }
}
