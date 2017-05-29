#include "hierarchyLoader.hpp"
#include "componentLoader.hpp"
#include "transform.hpp"
#include "messyEntity.hpp"
#include "messyCode2d.hpp"
#include "messyConfig.hpp"
#include "hierarchy.hpp"

#include <json.hpp>
#include <fstream>
#include <QString>
#include <QDebug>

namespace MessyCode2D_Engine {
    using namespace std;
    using namespace nlohmann;

    HierarchyLoader::HierarchyLoader() {
        componentLoader = new ComponentLoader();
    }

    HierarchyLoader::~HierarchyLoader() {
        delete   componentLoader;
        componentLoader = NULL;
    }

    void HierarchyLoader::SaveHierarchy() { }

    void HierarchyLoader::LoadHierarchy()
    {
        MessyCodeConfig* config = MessyCode2D::GetModule<MessyCodeConfig>();
        if (config != NULL)
        {
            ifstream reader(config->hierarchyFilePath);
            if (reader.good())
            {
                qDebug() << "[HierarchyLoader] Loaded hierarchy data file";
                json h_data;
                reader >> h_data;
                json e_data = h_data["entities"];

                // Get the hierarchy
                Hierarchy* hierarchy = MessyCode2D::GetModule<Hierarchy>();
                if (hierarchy == NULL)
                {
                    qDebug() << "[HierarchyLoader] could not find hierarchy module, process will stop";
                    return;
                }

                // Load entity data
                for (auto& entity : e_data) {
                    string name = entity.at("name").get<string>();
                    MessyEntity* newEnt = new MessyEntity(name);

                    for (string componentId : entity.at("componentsId").get<vector<string>>())
                    {
                        ECS::Component* component = componentLoader->GetComponent(componentId);
                        if (component != NULL)
                            newEnt->AddComponent(component, false);
                    }

                    hierarchy->AddMessyEntity(newEnt);
                }

                // Build parent hierarchy
                for (auto& entity : e_data) {
                    int parentId = entity.at("parentId").get<int>();
                    if (parentId != -1) {
                        int id = entity.at("id").get<int>();
                        MessyEntity* child = hierarchy->GetMessyEntity(id);
                        MessyEntity* parent = hierarchy->GetMessyEntity(parentId);
                        child->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
                    }
                }
            }
            else
            qCritical() << "[HierarchyLoader] Could not load hierarchy, specified file is missing " << QString::fromStdString(config->hierarchyFilePath) ;
        }
    }
}
