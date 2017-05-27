#include "hierarchyLoader.hpp"
#include "messyCode2d.hpp"
#include "messyConfig.hpp"
#include <json.hpp>
#include <cstddef>

#include <QDebug>
#include <QString>
#include <iostream>

namespace MessyCode2D_Engine {
    using namespace std;
    using namespace nlohmann;

    HierarchyLoader::~HierarchyLoader()
    {
        delete reader;
    }

    void HierarchyLoader::Boot()
    {
        reader = new ifstream();
    }

    void HierarchyLoader::Start() { }

    void HierarchyLoader::Update(float elapseTime) { }

    void HierarchyLoader::LoadHierarchy()
    {
        MessyCodeConfig* config = MessyCode2D::GetModule<MessyCodeConfig>();
        if (config != NULL)
        {
            reader->open(config->hierarchyFilePath);
            std::stringstream buffer;
            buffer << reader->rdbuf();
        }

        std::cout << "some guys";

        // this is for testing
//        json h_json = "{ \"entities\" : [ { \"id\" : 1, \"parentId\" : -1, \"name\" : \"test\", \"componentsId\" : [ \"TRANSFORM\" ] } ] }"_json;

//        json e_data = h_json["entities"];
        // log e_data.size()

//        std::cout << e_data.size();

//        for (auto& entity : e_data) {
//            EntityData e;
//            e.id = entity.at("id").get<int>();
//            e.parentId = entity.at("parentId").get<int>();
//            e.name = entity.at("name").get<std::string>();
//            e.componentsId = entity.at("componentsId").get<vector<string>>();


//        }
    }
}
