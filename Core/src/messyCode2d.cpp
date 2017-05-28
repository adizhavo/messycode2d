#include "messyCode2d.hpp"
#include "hierarchy.hpp"
#include "QDebug"

namespace MessyCode2D_Engine {
    std::vector<MessyModule*>MessyCode2D::modules;

    MessyCode2D::MessyCode2D()
    {
        elapseTimer = new QElapsedTimer();
        config = new MessyCodeConfig();

        AddModule(config);
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
        qDebug() << "[MessyCode2D] invoking boot";

        for (MessyModule* module : modules)
            module->Boot();

        qDebug() << "[MessyCode2D] finished boot";
    }
    
    void MessyCode2D::Start()
    {
        qDebug() << "[MessyCode2D] invoking start";

        for (MessyModule* module : modules)
            module->Start();

        elapseTimer->start();
        Next();

        qDebug() << "[MessyCode2D] finished start, target framerate:" << config->framePerSec;
    }
    
    void MessyCode2D::Update()
    {
        if (elapseTimer->elapsed() > 1 / config->framePerSec)
        {
            for (MessyModule* module : modules)
                module->Update(elapseTimer->elapsed());

            elapseTimer->restart();
        }

        Next();
    }

    void MessyCode2D::Next()
    {
        QMetaObject::invokeMethod(this, "Update", Qt::QueuedConnection);
    }
}
