#ifndef SCENEHIERARCHY_HPP
#define SCENEHIERARCHY_HPP

#include <QTreeWidget>
#include <string>
#include "filter.hpp"
#include <messyModule.hpp>
#include <messyEntity.hpp>

// Hierarchy GUI with a QTreeWidget

namespace MessyCode2D_Engine {
    class EditorHierarchy : public QObject, public MessyModule
    {
        Q_OBJECT

    public:
        void Boot();
        void Start();
        void Update(float deltaTime);
        ~EditorHierarchy();
        QTreeWidget *treeWidget;

    private:
        ECS::Filter* messyEntityFilter;

        QTreeWidgetItem* BuildTree(MessyEntity* messyEntity);

    public slots:
        void Refresh();
    };

    // Element in the hierarchy that holds a game entity
    // is used form the inspector to access the entity's components

    class HierarchyTreeWidget : public QTreeWidgetItem
    {
    public :
        MessyEntity* messyEntity;

        HierarchyTreeWidget(MessyEntity* me, const QString& string)
        {
            messyEntity = me;
            this->setText(0, string);
        }
    };
}

#endif
