#include "headers/editor/scenehierarchy.hpp"
#include "headers/components/transform.hpp"
#include "entityMatcher.hpp"

using namespace ECS;

namespace MessyCode2D_Engine {
    SceneHierarchy::SceneHierarchy()
    {
        this->treeWidget = new QTreeWidget();
        gameEntityFilter = new Filter();
        gameEntityFilter->AnyOf(1, COMP_ID(Transform));
    }

    SceneHierarchy::~SceneHierarchy()
    {
        delete this->treeWidget;
        delete this->gameEntityFilter;

        this->treeWidget = NULL;
        this->gameEntityFilter = NULL;
    }

    void SceneHierarchy::Update(float deltaTime)
    {
        treeWidget->clear();
        treeWidget->setColumnCount(1);

        QList<QTreeWidgetItem *> items;
        std::vector<Entity*> gameEntities = EntityMatcher::FilterGroup(*gameEntityFilter);
        for (Entity* entity : gameEntities)
        {
            QTreeWidgetItem* item = BuildTree(entity, true);
            if (item != NULL)
                items.append(item);
        }

        treeWidget->insertTopLevelItems(0, items);
        treeWidget->show();
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
