#include "messyCode2D.hpp"
#include "messyConfig.hpp"

namespace MessyCode2D_Engine {
    std::vector<MessyModule*>MessyCode2D::modules;

    MessyCode2D::MessyCode2D()
    {
        elapseTimer = new QElapsedTimer();

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

        elapseTimer->start();
        Next();
    }
    
    void MessyCode2D::Update()
    {
        for (MessyModule* module : modules)
            module->Update(elapseTimer->elapsed());

        elapseTimer->restart();
        Next();
    }

    void MessyCode2D::Next()
    {
        QMetaObject::invokeMethod(this, "Update", Qt::QueuedConnection);
    }
}
