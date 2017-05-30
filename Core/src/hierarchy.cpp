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
            json hierarchy;
            reader >> hierarchy;

            // Load entity data
            json entities = hierarchy["entities"];

            for (auto& entity : entities) {
                string name = entity.at("name").get<string>();
                MessyEntity* new_entity = AddMessyEntity(name);

                // Load components
                json components = entity["components"];

                for (auto& component : components) {
                    string id = component.at("id").get<string>();
                    ECS::Component* new_component = comp_loader->GetComponent(id);
                    if (new_component != NULL) {
                        new_entity->AddComponent(new_component, false);
                        // Load variables
                        json variables = component["variables"];

                        for (auto& variable : variables) {
                            MessySerializer* ms = dynamic_cast<MessySerializer*>(new_component);
                            SerializedData* s_data = ms->GetSerializedData(variable.at("id").get<string>());

                            if (s_data != NULL) {
                                if (variable["s"].size() != 0 ) *(s_data->s) = variable.at("s").get<string>();
                                if (variable["f"].size() != 0 ) *(s_data->f) = variable.at("f").get<float>();
                                if (variable["b"].size() != 0 ) *(s_data->b) = variable.at("b").get<bool>();
                                if (variable["i"].size() != 0 ) *(s_data->i) = variable.at("i").get<int>();
                            }
                        }
                    }
                    else qDebug() << "[Hierarchy] could not loade component:" << QString::fromStdString(id);
                }
            }

            // Build parent hierarchy
            for (auto& entity : entities) {
                int parentId = entity.at("parentId").get<int>();
                if (parentId != -1) {
                    int id = entity.at("id").get<int>();
                    MessyEntity* child = GetMessyEntity(id);
                    MessyEntity* parent = GetMessyEntity(parentId);
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
                json entity;
                entity["id"] = ent->id;
                entity["name"] = ent->name;
                Transform* tr = ent->GetComponent<Transform>();
                entity["parentId"] =  tr->GetParent() != NULL ? tr->GetParent()->GetEntity()->id : -1;

                // Start save components
                json components;

                for (Component* comp : ent->GetComponents()) {
                    json component;
                    component["id"] = comp_loader->GetJsonComponentId(comp->unique_id());

                    // Save component data
                    MessySerializer* ms = dynamic_cast<MessySerializer*>(comp);
                    if (ms != NULL && ms->Size() > 0) {
                        json variables;
                        // Get the serialzer data and save each field
                        SerializedData** data = ms->GetSerializedData();
                        for (int i = 0; i < ms->Size(); i ++) {
                            json s_data;
                            s_data["name"] = data[i]->type;
                            s_data["id"] = data[i]->id;
                            if (data[i]->s != NULL) s_data["s"] = *(data[i]->s);
                            if (data[i]->f != NULL) s_data["f"] = *(data[i]->f);
                            if (data[i]->b != NULL) s_data["b"] = *(data[i]->b);
                            if (data[i]->i != NULL) s_data["i"] = *(data[i]->i);
                            variables.push_back(s_data);
                        }

                        qDebug() << QString::fromStdString(variables.dump());
                        component["data"] = variables;
                    }

                    components.push_back(component);
                }

                entity["components"] = components;
                entities.push_back(entity);
            }

        hierarchy["entities"] = entities;

        string path = MessyCode2D::get_config().hierarchy();
        ofstream writer(path);
        //prepare reader to throw if failbit gets set
        ios_base::iostate exceptionMask = writer.exceptions() | ios::failbit;
        writer.exceptions(exceptionMask);

        try
        {
            string j_output = hierarchy.dump();
            writer.write(j_output.c_str(), j_output.size());
            qDebug() << "[Hierarchy] saved successfully in" << QString::fromStdString(path);
        }
        catch (ios_base::failure& e) {
            qCritical() << "[HierarchyLoader] could not save" << QString::fromStdString(path) << QString::fromStdString(e.what());
        }
    }
}
