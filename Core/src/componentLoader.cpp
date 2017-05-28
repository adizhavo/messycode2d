#include "componentLoader.hpp"
#include "transform.hpp"
#include <QDebug>

namespace MessyCode2D_Engine {
    using namespace std;
    using namespace ECS;

    Component* ComponentLoader::GetComponent(const std::string componentId)
    {
        qDebug() << "[ComponentLoader] requested component:" << QString::fromStdString(componentId);

        // Check if the component is a engine one
        if (componentId.compare("\"TRANSFORM\"")) {
            return new Transform();
        }
        // add other engine components here

        qDebug() << "[ComponentLoader]" << QString::fromStdString(componentId) << "not found, will return null";
        return NULL;
    }
}
