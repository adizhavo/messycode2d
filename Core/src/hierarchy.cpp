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

        for (MessyEntity* me : messyEntities)
            if (me != NULL)
                delete me;

        messyEntities.clear();
        delete   comp_loader;
        comp_loader = NULL;
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
            me->Start();

        qDebug() << "[Hierarchy] finished start";
    }

    void Hierarchy::Update(float deltaTime)
    {
        for (MessyEntity* me : messyEntities)
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
            if (me->id == id)
                return me;

        return NULL;
    }

    MessyEntity* Hierarchy::GetMessyEntity(const std::string name)
    {
        for (MessyEntity* me : messyEntities)
            if (me->name == name)
                return me;

        return NULL;
    }

    std::vector<MessyEntity*> Hierarchy::GetMessyEntities(const std::string name)
    {
        std::vector<MessyEntity*> result;
        for (MessyEntity* me : messyEntities)
            if (me->name == name)
                result.push_back(me);

        return result;
    }

    std::vector<MessyEntity*> Hierarchy::GetMessyEntities(Filter f)
    {
        std::vector<MessyEntity*> matched;

        for(MessyEntity* ent : messyEntities)
            if (f.DoesMatch(static_cast<Entity*>(ent)))
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
            if (me->id == id)
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
        ifstream reader(path);
        if (reader.good())
        {
            json hierarchy_data;
            reader >> hierarchy_data;
            json entities_data = hierarchy_data["entities"];

            // Get the hierarchy
            Hierarchy* hierarchy = MessyCode2D::GetModule<Hierarchy>();
            if (hierarchy == NULL)
            {
                qDebug() << "[HierarchyLoader] could not find hierarchy module, process will stop";
                return;
            }

            // Load entity data
            for (auto& entity_data : entities_data) {
                string name = entity_data.at("name").get<string>();
                MessyEntity* entity = hierarchy->AddMessyEntity(name);

                for (string componentId : entity_data.at("componentsId").get<vector<string>>()) {
                    ECS::Component* component = comp_loader->GetComponent(componentId);
                    if (component != NULL)
                        entity->AddComponent(component, false);
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

            qDebug() << "[HierarchyLoader] Loaded prefab:" << QString::fromStdString(path);
        }
        else
        qCritical() << "[HierarchyLoader] Could not load prefab, file is missing" << QString::fromStdString(path);
    }

    void Hierarchy::SaveHierarchy() {

    }
}





















