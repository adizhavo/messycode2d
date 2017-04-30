#include "messyCode2D.hpp"
#include "hierarchy.hpp"
#include "editorHierarchy.hpp"
#include "editorinspector.hpp"
#include "messyConsole.hpp"
#include <QApplication>
#include <QObject>

using namespace MessyCode2D_Engine;

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);

    Hierarchy* hierarchy = new Hierarchy();
    EditorHierarchy* editorHierarchy = new EditorHierarchy();
    EditorInspector* editorInspector = new EditorInspector();
    MessyConsole* editorConsole = new MessyConsole();

    MessyCode2D engine;
    MessyCode2D::AddModule(hierarchy);
    MessyCode2D::AddModule(editorHierarchy);
    MessyCode2D::AddModule(editorInspector);
    MessyCode2D::AddModule(editorConsole);

    engine.Boot();
    engine.Start();

    QObject::connect(hierarchy, SIGNAL(UpdateSignal()), editorHierarchy, SLOT(Refresh()));
    QObject::connect(editorHierarchy->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), editorInspector, SLOT(Refresh(QTreeWidgetItem*,int)));

    return a.exec();
}
