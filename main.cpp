#include "headers/messyCode2D.hpp"
#include "headers/scene.hpp"
#include "headers/editor/messyCode2DEditor.hpp"
#include "headers/messyCode2DConfig.hpp"
#include <QApplication>
#include <QObject>

using namespace MessyCode2D_Engine;

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);

    MessyCodeConfig config;
    Scene scene;
    MessyCode2DEditor editor;
    MessyCode2D engine;

    QObject::connect(&scene, SIGNAL(UpdateScene()), &editor, SLOT(Update()));

    engine.Boot(&config, &scene);
    engine.Start();

    return a.exec();
}
