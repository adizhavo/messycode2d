#ifndef EDITORINSPECTOR_H
#define EDITORINSPECTOR_H

#include <string>
#include <QTreeWidget>
#include <QVBoxLayout>
#include "messyModule.hpp"

#define STARTSERIALIZE(s)                       \
    public :                                    \
        int size = s;                           \
        InspectorData* data[s] {                \

#define SERIALIZE(t, n)                         \
    new InspectorData( #t , #n, &n )            \

#define AND ,

#define ENDSERIALIZATION                        \
    };                                          \
    InspectorData** GetData() {                 \
        return data;                            \
    }                                           \
    int Size() { return size; }                 \

namespace MessyCode2D_Engine {
    using namespace std;

    struct InspectorData
    {
    public:
        string id;
        string name;
        string* s;
        int* i;
        float* f;
        bool* b;

        InspectorData(string id, string name, int* i){
            this->id = id;
            this->name = name;
            this->i = i;
        }

        InspectorData(string id, string name, bool* b){
            this->id = id;
            this->name = name;
            this->b = b;
        }

        InspectorData(string id, string name, float* f)
        {
            this->id = id;
            this->name = name;
            this->f = f;
        }

        InspectorData(string id, string name, string* s)
        {
            this->id = id;
            this->name = name;
            this->s = s;
        }
    };

    class InspectorSerializer
    {
    public:
        virtual InspectorData** GetData() = 0;
        virtual int Size() = 0;
    };

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

        QWidget* GetFieldWidget(InspectorData* data);
        void ClearWidgets();
    };
}

#endif
