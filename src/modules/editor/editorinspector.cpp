#include "editorinspector.hpp"
#include "editorHierarchy.hpp"
#include "messyCode2D.hpp"
#include <string>
#include <sstream>

namespace MessyCode2D_Engine {
    EditorInspector::EditorInspector()
    {
        inspector = new QWidget();
        header = new QLabel(inspector);
        layout = new QHBoxLayout();
        layout->addWidget(header);
        inspector->setLayout(layout);
    }

    EditorInspector::~EditorInspector()
    {
        delete inspector;
        delete header;
        delete layout;

        inspector = NULL;
        header = NULL;
        layout = NULL;
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
        HierarchyTreeWidget* hierarchyWidget = static_cast<HierarchyTreeWidget*>(item);
        QString headerText = QString::fromStdString(hierarchyWidget->messyEntity->name);
        header->setText(headerText);
    }
}
