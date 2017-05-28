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

        for (MessyEntity* entity : messyEntities)
        {
            QTreeWidgetItem* item = BuildTree(entity, true);
            if (item != NULL)
                items.append(item);
        }

        treeWidget->insertTopLevelItems(0, items);
        treeWidget->show();
    }

    // The additional boolean is to stop the recursion for the first entity without a parent
    QTreeWidgetItem* EditorHierarchy::BuildTree(MessyEntity* messyEntity, bool blockIfParented)
    {
        Transform* tr = messyEntity->GetComponent<Transform>();

        if (blockIfParented && tr->GetParent() != NULL)
            return NULL;

        QString entityName = QString::fromStdString(messyEntity->name);
        HierarchyTreeWidget* item = new HierarchyTreeWidget(messyEntity, entityName);

        for (Transform* children : tr->GetChildren())
        {
            QTreeWidgetItem* child = BuildTree(static_cast<MessyEntity*>(children->entity), false);
            if (child != NULL)
                item->addChild(child);
        }

        return item;
    }
}
