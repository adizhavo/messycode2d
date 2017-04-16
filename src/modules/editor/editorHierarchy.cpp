#include "editorHierarchy.hpp"
#include "transform.hpp"
#include "entityMatcher.hpp"

using namespace ECS;

namespace MessyCode2D_Engine {
    void EditorHierarchy::Boot()
    {
        this->treeWidget = new QTreeWidget();
        this->treeWidget->setHeaderLabel("Hierarchy");
        this->treeWidget->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint );

        this->messyEntityFilter = new Filter();
        this->messyEntityFilter->AnyOf(1, COMP_ID(Transform));
    }

    void EditorHierarchy::Start()
    {
        Refresh();
    }

    EditorHierarchy::~EditorHierarchy()
    {
        delete this->treeWidget;
        delete this->messyEntityFilter;

        this->treeWidget = NULL;
        this->messyEntityFilter = NULL;
    }

    void EditorHierarchy::Refresh()
    {
        this->treeWidget->clear();
        this->treeWidget->setColumnCount(1);

        QList<QTreeWidgetItem *> items;
        std::vector<Entity*> messyEntities = EntityMatcher::FilterGroup(*messyEntityFilter);
        for (Entity* entity : messyEntities)
        {
            QTreeWidgetItem* item = BuildTree(entity, true);
            if (item != NULL)
                items.append(item);
        }

        this->treeWidget->insertTopLevelItems(0, items);
        this->treeWidget->show();
    }

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
