#ifndef COMPONENTLOADER_H
#define COMPONENTLOADER_H

#include <string>
#include "component.hpp"

namespace MessyCode2D_Engine {
    // Loads internal components or in an external library
    // Game components that comes from the final developer are loaded here
    using namespace ECS;

    class ComponentLoader
    {
    public:
        Component* GetComponent(const std::string componentId);
    };
}

#endif // COMPONENTLOADER_H
