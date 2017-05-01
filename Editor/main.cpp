#include "messyCode2D.hpp"
#include "editorHierarchy.hpp"
#include "editorInspector.hpp"
#include "messyConsole.hpp"
#include <QApplication>
#include <QObject>

using namespace MessyCode2D_Engine;

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);

    EditorHierarchy* editorHierarchy = new EditorHierarchy();
    EditorInspector* editorInspector = new EditorInspector();
    MessyConsole* editorConsole = new MessyConsole();

    MessyCode2D* engine = new MessyCode2D();
    MessyCode2D::AddModule(editorHierarchy);
    MessyCode2D::AddModule(editorInspector);
    MessyCode2D::AddModule(editorConsole);

    engine->Boot();
    engine->Start();

    Hierarchy* h = MessyCode2D::GetModule<Hierarchy>();
    QObject::connect(h, SIGNAL(UpdateSignal()), editorHierarchy, SLOT(Refresh()));
    QObject::connect(editorHierarchy->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), editorInspector, SLOT(Refresh(QTreeWidgetItem*,int)));

    return a.exec();
}
