#include "messyCode2D.hpp"
#include "messyConfig.hpp"

namespace MessyCode2D_Engine {
    std::vector<MessyModule*>MessyCode2D::modules;

    MessyCode2D::MessyCode2D()
    {
        this->timer = new QTimer();
        this->elapseTimer = new QElapsedTimer();

        AddModule(new MessyCodeConfig());
        AddModule(new Hierarchy());
    }

    void MessyCode2D::AddModule(MessyModule *module)
    {
        modules.push_back(module);
    }

    MessyCode2D::~MessyCode2D()
    {
        for (MessyModule* module : modules)
            if (module != NULL)
                delete module;
        modules.clear();

        delete timer;
        delete elapseTimer;
        delete hierarchy;
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
