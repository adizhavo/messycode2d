#ifndef SCENEHIERARCHY_HPP
#define SCENEHIERARCHY_HPP

#include <QApplication>
#include <QTreeWidget>
#include "filter.hpp"
#include "messyModule.hpp"

namespace MessyCode2D_Engine {
    class EditorHierarchy : public QObject, public MessyModule
    {
        Q_OBJECT

    public:
        void Boot();
        void Start();
        void Update(float deltaTime) { }
        ~EditorHierarchy();
    private:
        QTreeWidget *treeWidget;
        ECS::Filter* messyEntityFilter;

        QTreeWidgetItem* BuildTree(ECS::Entity* entity, bool blockIfParented);

    public slots:
        void Refresh();
    };
}

#endif
