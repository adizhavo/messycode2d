#include "editorinspector.hpp"

namespace MessyCode2D_Engine {
    EditorInspector::EditorInspector()
    {
        inspector = new QWidget();
    }

    EditorInspector::~EditorInspector()
    {
        delete inspector;
        inspector = NULL;
    }

    void EditorInspector::Boot()
    {
        inspector->setWindowTitle(QString("Inspector"));
        inspector->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint );
    }

    void EditorInspector::Start()
    {
        inspector->show();
    }

    void EditorInspector::Update(float deltaTime) { }

    void EditorInspector::Refresh(QTreeWidgetItem *item, int column)
    {

    }
}
