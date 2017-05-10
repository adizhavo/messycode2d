#include "editorHierarchy.hpp"
#include <transform.hpp>
#include <entityMatcher.hpp>
#include <cstddef>

using namespace ECS;

namespace MessyCode2D_Engine {
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
        std::vector<Entity*> messyEntities = EntityMatcher::FilterGroup(*messyEntityFilter);
        for (Entity* entity : messyEntities)
        {
            QTreeWidgetItem* item = BuildTree(entity, true);
            if (item != NULL)
                items.append(item);
        }

        treeWidget->insertTopLevelItems(0, items);
        treeWidget->show();
    }

    // The additional boolean is to stop the recursion for the first entity without a parent
    QTreeWidgetItem* EditorHierarchy::BuildTree(Entity* entity, bool blockIfParented)
    {
        Transform* tr = entity->GetComponent<Transform>();

        if (blockIfParented && tr->GetParent() != NULL)
            return NULL;

        MessyEntity* messyEntity = static_cast<MessyEntity*>(entity);
        QString entityName = QString::fromStdString(messyEntity->name);
        HierarchyTreeWidget* item = new HierarchyTreeWidget(messyEntity, entityName);

        for (Transform* children : tr->GetChildren())
        {
            QTreeWidgetItem* child = BuildTree(children->entity, false);
            if (child != NULL)
                item->addChild(child);
        }

        return item;
    }
}
