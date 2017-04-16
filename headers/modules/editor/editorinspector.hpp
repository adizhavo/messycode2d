#ifndef EDITORINSPECTOR_H
#define EDITORINSPECTOR_H

#include <string>
#include <map>
#include <QTreeWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "messyModule.hpp"

#define EDITOR_SERIALIZABLE                     \
public:                                         \
    InspectorData inspectorData;                \
    InspectorData* GetInspectorData()           \
    {                                           \
        return &inspectorData;                  \
    }                                           \


#define SERIALIZE_BOOL(name, default)           \
public:                                         \
    bool name;                                  \
    void Serialize##name()                      \
    {                                           \
        name = default;                         \
        inspectorData.AddBool(&name, "name");   \
    }                                           \

#define SERIALIZE_FLOAT(name, default)          \
public:                                         \
    float name;                                 \
    void Serialize##name()                      \
    {                                           \
        name = default;                         \
        inspectorData.AddFloat(&name, "name");  \
    }                                           \

#define SERIALIZE_STRING(name, default)         \
public:                                         \
    std::string name;                           \
    void Serialize##name()                      \
    {                                           \
        name = default;                         \
        inspectorData.AddString(&name, "name"); \
    }                                           \

namespace MessyCode2D_Engine {
    using namespace std;

    class InspectorData
    {
        struct data {
            map<string, bool*> booleans;
            map<string, float*> floats;
            map<string, string*> strings;
        };

    public:
        data inspectorData;

        void AddBool(bool* value, string label)
        {
            inspectorData.booleans.insert(pair<string, bool*>(label, value));
        }

        void AddFloat(float* value, string label)
        {
            inspectorData.floats.insert(pair<string, float*>(label, value));
        }

        void AddString(string* value, string label)
        {
            inspectorData.strings.insert(pair<string, string*>(label, value));
        }
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
        QLabel* header;
        QHBoxLayout* layout;
    };
}

#endif
