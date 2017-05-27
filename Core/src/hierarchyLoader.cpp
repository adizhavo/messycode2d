#include "hierarchyLoader.hpp"
#include "messyCode2d.hpp"
#include "messyConfig.hpp"
#include <json.hpp>
#include <fstream>
#include <QString>
#include <QDebug>

namespace MessyCode2D_Engine {
    using namespace std;
    using namespace nlohmann;

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

                // Load entity data
                for (auto& entity : e_data) {
                    EntityData e;
                    e.id = entity.at("id").get<int>();
                    e.parentId = entity.at("parentId").get<int>();
                    e.name = entity.at("name").get<std::string>();
                    e.componentsId = entity.at("componentsId").get<vector<string>>();
                }
            }
            else
            qCritical() << "[HierarchyLoader] Could not load hierarchy, specified file is missing " << QString::fromStdString(config->hierarchyFilePath) ;
        }
    }
}
