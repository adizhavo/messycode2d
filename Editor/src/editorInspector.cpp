#include "editorInspector.hpp"
#include "editorHierarchy.hpp"
#include "messySerializer.hpp"
#include <QString>
#include <QLabel>

namespace MessyCode2D_Engine {
    EditorInspector::EditorInspector()
    {
        inspector = new QWidget();
        inspector->resize(300, 300);
        inspectorLayout = new QVBoxLayout(inspector);
        inspectorLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    }

    EditorInspector::~EditorInspector()
    {
        ClearWidgets();

        delete inspector;
        inspector = NULL;
    }

    void EditorInspector::Boot()
    {
        inspector->setWindowTitle(QString("Inspector"));
        inspector->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    }

    void EditorInspector::Start()
    {
        inspector->show();
    }

    void EditorInspector::Update(float deltaTime) { }

    void EditorInspector::Refresh(QTreeWidgetItem *item, int column)
    {
        ClearWidgets();

        // Get all the serializable components from the entity
        HierarchyTreeWidget* hierarchyTree = static_cast<HierarchyTreeWidget*>(item);
        vector<MessySerializer*> serializable = hierarchyTree->messyEntity->GetComponents<MessySerializer>();

        for (MessySerializer* is : serializable)
        {
            SerializerData** data = is->GetData();
            for (int i = 0; i < is->Size(); i ++)
            {
                // Get the widget displaying the data
                QWidget* widget = GetFieldWidget(data[i]);
                widgets.push_back(widget);
                inspectorLayout->addWidget(widget);
                widget->show();
            }
        }
    }

    // Get a widget for each serialized field
    QWidget* EditorInspector::GetFieldWidget(SerializerData* data)
    {
        QString s;
        QLabel* label = new QLabel();

        if (data->id == "float")
            s.sprintf("%s: %f", data->name.c_str(), *(data->f));
        else if (data->id == "string")
            s.sprintf("%s: %f", data->name.c_str(), *(data->f));
        else if (data->id == "bool")
            s.sprintf("%s: %s", data->name.c_str(), data->b ? "true" : "false");
        else if (data->id == "int")
            s.sprintf("%s: %d", data->name.c_str(), *(data->i));
        else
            s.sprintf("%s, could not display property, unknown type", data->name.c_str());

        label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        label->setText(s);
        label->show();
        return label;
    }

    void EditorInspector::ClearWidgets()
    {
        for (QWidget* widget : widgets)
        {
            inspectorLayout->removeWidget(widget);
            delete widget;
        }

        widgets.clear();
    }
}
