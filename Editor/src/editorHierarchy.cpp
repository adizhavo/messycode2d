#include "editorHierarchy.hpp"
#include <transform.hpp>
#include <messyCode2D.hpp>
#include <hierarchy.hpp>
#include <cstddef>

namespace MessyCode2D_Engine {
    using namespace ECS;

    void EditorHierarchy::Boot()
    {
        // Create GUI elements and the entity filter
        treeWidget = new QTreeWidget();
        treeWidget->setHeaderLabel("Hierarchy");
        treeWidget->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

        messyEntityFilter = new Filter();
        messyEntityFilter->AnyOf(1, COMP_ID(Transform));
    }

    void EditorHierarchy::Start()
    {
        Refresh();
    }

    void EditorHierarchy::Update(float deltaTime) { }

    EditorHierarchy::~EditorHierarchy()
    {
        delete treeWidget;
        delete messyEntityFilter;

        treeWidget = NULL;
        messyEntityFilter = NULL;
    }

    void EditorHierarchy::Refresh()
    {
        treeWidget->clear();
        treeWidget->setColumnCount(1);

        QList<QTreeWidgetItem *> items;
        // Get all the entity by the filter
        std::vector<MessyEntity*> messyEntities = MessyCode2D::GetModule<Hierarchy>()->GetMessyEntities(*messyEntityFilter);

        for (MessyEntity* entity : messyEntities) {
            Transform* tr = entity->GetComponent<Transform>();
            // build hierarchy from the root entity
            if (tr->GetParent() == NULL) {
                QTreeWidgetItem* item = BuildTree(entity);
                items.append(item);
            }
        }

        treeWidget->insertTopLevelItems(0, items);
        treeWidget->show();
    }


    QTreeWidgetItem* EditorHierarchy::BuildTree(MessyEntity* messyEntity)
    {
        Transform* tr = messyEntity->GetComponent<Transform>();
        QString entityName = QString::fromStdString(messyEntity->name);
        HierarchyTreeWidget* item = new HierarchyTreeWidget(messyEntity, entityName);

        for (Transform* children : tr->GetChildren()) {
            QTreeWidgetItem* child = BuildTree(static_cast<MessyEntity*>(children->entity));
            if (child != NULL)
                item->addChild(child);
        }

        return item;
    }
}
