#include "scenehierarchy.hpp"
#include "transform.hpp"
#include "entityMatcher.hpp"

using namespace ECS;

namespace MessyCode2D_Engine {
    void SceneHierarchy::Boot()
    {
        this->treeWidget = new QTreeWidget();
        this->gameEntityFilter = new Filter();
        this->gameEntityFilter->AnyOf(1, COMP_ID(Transform));
    }

    void SceneHierarchy::Start()
    {
        Refresh();
    }

    SceneHierarchy::~SceneHierarchy()
    {
        delete this->treeWidget;
        delete this->gameEntityFilter;

        this->treeWidget = NULL;
        this->gameEntityFilter = NULL;
    }

    void SceneHierarchy::Refresh()
    {
        this->treeWidget->clear();
        this->treeWidget->setColumnCount(1);

        QList<QTreeWidgetItem *> items;
        std::vector<Entity*> gameEntities = EntityMatcher::FilterGroup(*gameEntityFilter);
        for (Entity* entity : gameEntities)
        {
            QTreeWidgetItem* item = BuildTree(entity, true);
            if (item != NULL)
                items.append(item);
        }

        this->treeWidget->insertTopLevelItems(0, items);
        this->treeWidget->show();
    }

    QTreeWidgetItem* SceneHierarchy::BuildTree(Entity* entity, bool blockIfParented)
    {
        Transform* tr = entity->GetComponent<Transform>();

        if (blockIfParented && tr->GetParent() != NULL)
            return NULL;

        QTreeWidgetItem* item = new QTreeWidgetItem(   (QTreeWidget*)0,      QStringList(QString("entity"))     );

        for (Transform* children : tr->GetChildren())
        {
            QTreeWidgetItem* child = BuildTree(children->entity, false);
            if (child != NULL)
                item->addChild(child);
        }

        return item;
    }
}
