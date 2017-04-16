#include "messyCode2D.hpp"
#include "hierarchy.hpp"
#include "editorHierarchy.hpp"
#include <QApplication>
#include <QObject>

using namespace MessyCode2D_Engine;

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);

    Hierarchy hierarchy;
    EditorHierarchy editorHierarchy;

    MessyCode2D engine;
    engine.AddModule(&hierarchy);
    engine.AddModule(&editorHierarchy);

    engine.Boot();
    engine.Start();

    QObject::connect(&hierarchy, SIGNAL(UpdateSignal()), &editorHierarchy, SLOT(Refresh()));

    return a.exec();
}
