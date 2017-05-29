#include <messyCode2d.hpp>
#include <hierarchy.hpp>
#include "editorHierarchy.hpp"
#include "editorInspector.hpp"
#include "messyConsole.hpp"
#include <QApplication>
#include <QObject>

using namespace MessyCode2D_Engine;

int main(int argc, char * argv[]) {
    QApplication editor(argc, argv);

    // Create modules
    EditorHierarchy* editorHierarchy = new EditorHierarchy();
    EditorInspector* editorInspector = new EditorInspector();
    MessyConsole* editorConsole = new MessyConsole();

    // Create engine and add modules
    MessyCode2D* engine = new MessyCode2D();
    MessyCode2D::AddModule(editorHierarchy);
    MessyCode2D::AddModule(editorInspector);
    MessyCode2D::AddModule(editorConsole);

    engine->Boot();

    // link the editor
    Hierarchy* h = MessyCode2D::GetModule<Hierarchy>();
    QObject::connect(h, SIGNAL(UpdateSignal()), editorHierarchy, SLOT(Refresh()));
    QObject::connect(editorHierarchy->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), editorInspector, SLOT(Refresh(QTreeWidgetItem*,int)));

    engine->Start();

    int result = editor.exec();

    // Cleanup
    delete engine;
    engine = 0;

    return result;
}
