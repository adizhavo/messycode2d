#include "componentLoader.hpp"
#include "transform.hpp"
#include <QDebug>

namespace MessyCode2D_Engine {
    using namespace std;
    using namespace ECS;

    Component* ComponentLoader::GetComponent(const std::string componentId)
    {
        qDebug() << "[ComponentLoader] requested component:" << QString::fromStdString(componentId);

        Component* engineComponent = GetEngineComponent(componentId);
        if (engineComponent != NULL)
            return engineComponent;

        // TODO : try to load from external library

        qDebug() << "[ComponentLoader]" << QString::fromStdString(componentId) << "not found, will return null";
        return NULL;
    }

    Component* ComponentLoader::GetEngineComponent(const string componentId)
    {
        // Check if the component is default of engine
        if (componentId.compare("\"TRANSFORM\"")) {
            return new Transform();
        }
        // add other engine components here

        return NULL;
    }

    string ComponentLoader::GetJsonComponentId(unsigned long compId)
    {
        // Check if the component is default of engine
        if (compId == COMP_ID(Transform))
            return "TRANSFORM";
         // add other engine components here

        return "NOT_AVAILABLE"; // TODO : try to load from external library
    }
}
