#ifndef SCENEHIERARCHY_HPP
#define SCENEHIERARCHY_HPP

#include <QApplication>
#include <QTreeWidget>

#include "filter.hpp"

namespace MessyCode2D_Engine {
    class SceneHierarchy
    {
    public:
        SceneHierarchy();
        ~SceneHierarchy();
        void Update(float deltaTime);
    private:
        QTreeWidget *treeWidget;
        ECS::Filter* gameEntityFilter;

        QTreeWidgetItem* BuildTree(ECS::Entity* entity, bool blockIfParented);
    };
}

#endif
