#include "messyCode2D.hpp"
#include "scene.hpp"
#include "messyCode2DConfig.hpp"
#if MESSY_LOGS
#include <iostream>
#endif

namespace MessyCode2D_Engine {
    MessyCode2D*MessyCode2D::instance;

    MessyCode2D::MessyCode2D()
    {
        instance = this;
        this->timer = new QTimer();
        this->elapseTimer = new QElapsedTimer();
        AddService(new MessyCodeConfig());
    }

    void MessyCode2D::AddService(MessyModule *module)
    {
        this->modules.push_back(module);
#if MESSY_LOGS
        std::cout << "Module added : " << module->log ;
#endif
    }

    MessyCode2D::~MessyCode2D()
    {
        for (MessyModule* module : modules)
            delete module;
        modules.clear();

        delete timer;
        delete elapseTimer;
    }

    void MessyCode2D::Boot()
    {
        for (MessyModule* module : modules)
            module->Boot();
    }
    
    void MessyCode2D::Start()
    {
        for (MessyModule* module : modules)
            module->Start();

        this->connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
        timer->start((1.0 / GetModule<MessyCodeConfig>()->framePerSec));
        elapseTimer->start();
    }
    
    void MessyCode2D::Update()
    {
        for (MessyModule* module : modules)
            module->Update(elapseTimer->elapsed());
        elapseTimer->restart();
    }
}
