#ifndef EDITORINSPECTOR_H
#define EDITORINSPECTOR_H

#include <QTreeWidget>
#include <QVBoxLayout>
#include <messyModule.hpp>
#include "messySerializer.hpp"

namespace MessyCode2D_Engine {
    // Editor inspector GUI

    class EditorInspector : public QObject, public MessyModule
    {
        Q_OBJECT

    public:
        void Boot();
        void Start();
        void Update(float deltaTime);

        EditorInspector();
        ~EditorInspector();

    public slots:
        void Refresh(QTreeWidgetItem *item, int column);

    private:
        QWidget* inspector;
        QVBoxLayout *inspectorLayout;
        vector<QWidget*> widgets;

        QWidget* GetFieldWidget(SerializerData* data);
        void ClearWidgets();
    };
}

#endif
