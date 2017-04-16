#include "editorinspector.hpp"
#include "editorHierarchy.hpp"
#include "messyCode2D.hpp"
#include <QHBoxLayout>
#include <QLabel>
#include <string>
#include <sstream>

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
        QLabel *label = new QLabel(inspector);
        QHBoxLayout *layout = new QHBoxLayout();
        label->setText("Selected entity, will show all entity properties");
        layout->addWidget(label);
        inspector->setLayout(layout);
    }
}
