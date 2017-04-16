#include "messyCode2D.hpp"
#include "scene.hpp"
#include "scenehierarchy.hpp"
#include <QApplication>
#include <QObject>

using namespace MessyCode2D_Engine;

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);

    Scene scene;
    SceneHierarchy hierarchy;

    MessyCode2D engine;
    engine.AddService(&scene);
    engine.AddService(&hierarchy);

    engine.Boot();
    engine.Start();

    QObject::connect(&scene, SIGNAL(UpdateSignal()), &hierarchy, SLOT(Refresh()));

    return a.exec();
}
