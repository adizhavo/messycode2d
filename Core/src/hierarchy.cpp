#include "hierarchy.hpp"
#include "messyCode2d.hpp"
#include "messyEntity.hpp"
#include "componentLoader.hpp"
#include "entityMatcher.hpp"
#include <cstddef>
#include <iostream>
#include <fstream>
#include <json.hpp>
#include <transform.hpp>
#include <QDebug>

namespace MessyCode2D_Engine {
    using namespace std;
    using namespace nlohmann;
    using namespace ECS;

    Hierarchy::Hierarchy()
    {
        comp_loader = new ComponentLoader();
    }

    Hierarchy::~Hierarchy()
    {
        SaveHierarchy();

        qDebug() << "[Hierarchy] cleaning entities";

        for (MessyEntity* me : messyEntities)
            if (me != NULL)
                delete me;

        qDebug() << "[Hierarchy] cleaning component loader";

        delete comp_loader;
        comp_loader = NULL;

        qDebug() << "[Hierarchy] cleaning end";
    }

    void Hierarchy::Boot()
    {
        this->lastEntityId = 0;

        qDebug() << "[Hierarchy] finished boot";
        LoadHierarchy();
    }
    
    void Hierarchy::Start()
    {
        for (MessyEntity* me : messyEntities)
            if (me != NULL)
                me->Start();

        qDebug() << "[Hierarchy] finished start";
    }

    void Hierarchy::Update(float deltaTime)
    {
        for (MessyEntity* me : messyEntities)
            if (me != NULL)
                me->Update(deltaTime);
    }

    MessyEntity* Hierarchy::AddMessyEntity(string name)
    {
        lastEntityId ++;
        MessyEntity* entity = new MessyEntity(name);
        entity->id = lastEntityId;
        messyEntities.push_back(entity);
        Refresh();

        return entity;
    }
    
    void Hierarchy::RemoveMessyEntity(MessyEntity* me)
    {
        messyEntities.erase(remove(messyEntities.begin(), messyEntities.end(), me), messyEntities.end());
        delete me;
        Refresh();
    }

    MessyEntity* Hierarchy::GetMessyEntity(int id)
    {
        for (MessyEntity* me : messyEntities)
            if (me != NULL && me->id == id)
                return me;

        return NULL;
    }

    MessyEntity* Hierarchy::GetMessyEntity(const std::string name)
    {
        for (MessyEntity* me : messyEntities)
            if (me != NULL && me->name == name)
                return me;

        return NULL;
    }

    std::vector<MessyEntity*> Hierarchy::GetMessyEntities(const std::string name)
    {
        std::vector<MessyEntity*> result;
        for (MessyEntity* me : messyEntities)
            if (me != NULL && me->name == name)
                result.push_back(me);

        return result;
    }

    std::vector<MessyEntity*> Hierarchy::GetMessyEntities(Filter f)
    {
        std::vector<MessyEntity*> matched;

        for(MessyEntity* ent : messyEntities)
            if (ent != NULL && f.DoesMatch(static_cast<Entity*>(ent)))
                matched.push_back(ent);

        return matched;
    }

    std::vector<Entity*> Hierarchy::GetEntities(Filter f)
    {
        return EntityMatcher::FilterGroup(f);
    }

    void Hierarchy::RemoveMessyEntity(int id)
    {
        for (MessyEntity* me : messyEntities)
            if (me != NULL && me->id == id)
            {
                RemoveMessyEntity(me);
                break;
            }
    }

    void Hierarchy::Refresh()
    {
        emit UpdateSignal();
    }

    void Hierarchy::LoadHierarchy()
    {
        LoadPrefab(MessyCode2D::get_config().hierarchy());
    }

    void Hierarchy::LoadPrefab(string path)
    {
        ifstream reader;
        //prepare reader to throw if failbit gets set
        ios_base::iostate exceptionMask = reader.exceptions() | ios::failbit;
        reader.exceptions(exceptionMask);

        try
        {
            // open file
            reader.open(path);
            json hierarchy_data;
            reader >> hierarchy_data;

            // Get the hierarchy
            Hierarchy* hierarchy = MessyCode2D::GetModule<Hierarchy>();
            if (hierarchy == NULL)
            {
                qDebug() << "[HierarchyLoader] could not find hierarchy module, process will stop";
                return;
            }

            // Load entity data
            json entities_data = hierarchy_data["entities"];

            for (auto& entity_data : entities_data) {
                string name = entity_data.at("name").get<string>();
                MessyEntity* entity = hierarchy->AddMessyEntity(name);

                // Load components
                json comps_data = entity_data["components"];

                for (auto& comp_data : comps_data) {
                    string id = comp_data.at("id").get<string>();
                    ECS::Component* component = comp_loader->GetComponent(id);
                    if (component != NULL)
                        entity->AddComponent(component, false);

                    // Load component serialized data
                    json ser_data = comp_data["data"];

                    for (auto& s_data : ser_data) {
                        MessySerializer* ms = dynamic_cast<MessySerializer*>(component);
                        SerializerData* s_d = ms->GetSData(s_data.at("name").get<string>());

                        if (s_d != NULL) {
                            if (s_data["s"].size() != 0 ) *(s_d->s) = s_data.at("s").get<string>();
                            if (s_data["f"].size() != 0 ) *(s_d->f) = s_data.at("f").get<float>();
                            if (s_data["b"].size() != 0 ) *(s_d->b) = s_data.at("b").get<bool>();
                            if (s_data["i"].size() != 0 ) *(s_d->i) = s_data.at("i").get<int>();
                        }

                        qDebug() <<QString::fromStdString(s_data.at("name").get<string>());
                    }
                }
            }

            // Build parent hierarchy
            for (auto& entity_data : entities_data) {
                int parentId = entity_data.at("parentId").get<int>();
                if (parentId != -1) {
                    int id = entity_data.at("id").get<int>();
                    MessyEntity* child = hierarchy->GetMessyEntity(id);
                    MessyEntity* parent = hierarchy->GetMessyEntity(parentId);
                    child->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
                }
            }

            qDebug() << "[Hierarchy] loaded prefab:" << QString::fromStdString(path);
        }
        catch (ios_base::failure& e) {
            qCritical() << "[Hierarchy] could not load prefab" << QString::fromStdString(path) << QString::fromStdString(e.what());
        }
    }

    void Hierarchy::SaveHierarchy() {
        qDebug() << "[Hierarchy] starting saving of hierarchy";

        json hierarchy;
        json entities;

        qDebug() << "[Hierarchy] building entity json";

        for(MessyEntity* ent : messyEntities)
            if (ent != NULL) {
                json j_object;
                j_object["id"] = ent->id;
                Transform* tr = ent->GetComponent<Transform>();
                j_object["parentId"] =  tr->GetParent() != NULL ? tr->GetParent()->GetEntity()->id : -1;
                j_object["name"] = ent->name;

                // Load components id
                vector<string> componentsId;
                for (Component* comp : ent->GetComponents()) {
                    string id = comp_loader->GetJsonComponentId(comp->unique_id());
                    componentsId.push_back(id);
                }

                j_object["componentsId"] = componentsId;

                entities.push_back(j_object);
            }

        // Save also components
        // qDebug() << "[Hierarchy] building component json";
        // here

        hierarchy["entities"] = entities;

        string path = MessyCode2D::get_config().hierarchy();
        ofstream writer(path);
        //prepare reader to throw if failbit gets set
        ios_base::iostate exceptionMask = writer.exceptions() | ios::failbit;
        writer.exceptions(exceptionMask);

        try
        {
            //MessyCode2D::get_config().hierarchy()
            string j_output = hierarchy.dump();
            writer.write(j_output.c_str(), j_output.size());
            qDebug() << "[Hierarchy] saved successfully in" << QString::fromStdString(path);
        }
        catch (ios_base::failure& e) {
            qCritical() << "[HierarchyLoader] could not save" << QString::fromStdString(path) << QString::fromStdString(e.what());
        }
    }
}
