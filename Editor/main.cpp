#include <messyCode2d.hpp>
#include <hierarchy.hpp>
#include "editorHierarchy.hpp"
#include "editorInspector.hpp"
#include "messyConsole.hpp"
#include <QApplication>
#include <QObject>

// TEMP CODE
#include <transform.hpp>

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

    // TEMP CODE
    // Add some entity in scene
    MessyEntity* ent1 = new MessyEntity("ent 1");
    MessyEntity* ent2 = new MessyEntity("ent 2");
    MessyEntity* ent3 = new MessyEntity("ent 3");

    Transform* tr1 = new Transform();
    Transform* tr2 = new Transform();
    Transform* tr3 = new Transform();
    ent1->AddComponent(tr1);
    ent2->AddComponent(tr2);
    ent3->AddComponent(tr3);

    tr3->SetParent(tr2);
    tr2->SetParent(tr1);

    h->AddMessyEntity(ent1);
    h->AddMessyEntity(ent2);
    h->AddMessyEntity(ent3);
    // END TEMP CODE

    return a.exec();
}
