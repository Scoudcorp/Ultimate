#include "entity.h"
#include "game.h"
#include "iw_string.h"
#include "script.h"
#include "server.h"
#include <imgui/imgui.h>


gentity_s* Entity::Spawn(const char* modelName, const float* origin, const float* angles)
{
    const auto entity = Game::Spawn();

    entity->classname = Script::g_scriptStringConstants->script_model;
    entity->script_linkname = Script::g_scriptStringConstants->script_model;
    entity->targetname = Script::g_scriptStringConstants->script_model;
    entity->spawnFlags = 1;

    entity->shared.currentOrigin[0] = origin[0];
    entity->shared.currentOrigin[1] = origin[1];
    entity->shared.currentOrigin[2] = origin[2];

    entity->shared.currentAngles[0] = angles[0];
    entity->shared.currentAngles[1] = angles[1];
    entity->shared.currentAngles[2] = angles[2];

    Game::SetModel(entity, modelName);
    if (!entity->model) {
        std::printf("Entity -> Invalid model %s\n", modelName);
        Game::FreeEntity(entity);
    }

    if (!Game::CallSpawnEntity(entity)) {
        std::printf("Entity -> Failed to spawn entity %d (%s)\n", entity->state.number, modelName);
        Game::FreeEntity(entity);
        return nullptr;
    }

    return entity;
}

gentity_s* Entity::SpawnCarePackage(const float* origin, const float* angles)
{
    auto package = Spawn("com_plasticcase_friendly", origin, angles);
    package->cloneBrushModelToScriptModel(g_airdropCollisionBrush);
    return package;
}

void Entity::DrawEntityList()
{
    ImGui::Begin("Entities", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    for (auto i = 0; i < g_entities.size(); i++) {
        const auto entity = &g_entities[i];

        const auto text = String::Format("%4d", i);
        if (entity != nullptr && ImGui::TreeNode(text)) {
            entity->draw();

            ImGui::TreePop();
        }
    }

    ImGui::End();
}

void gentity_s::cloneBrushModelToScriptModel(gentity_s* brushEntity)
{
    if (classname != Script::g_scriptStringConstants->script_model) {
        std::printf("Script model entity is not a script_model\n");
        return;
    }

    if (state.eType != 6) {
        std::printf("Script model entity is not a type 6 (%d)\n", state.eType);
        return;
    }

    if (!brushEntity->state.index.brushmodel) {
        std::printf("Brush model entity has no collision model\n");
        return;
    }

    Server::UnlinkEntity(this);

    const auto contents = shared.contents;
    state.index.brushmodel = brushEntity->state.index.brushmodel;
    shared.bmodel = 4;

    Server::SomeBrushSetup(this);

    shared.contents |= contents;

    Server::LinkEntity(this);
}

void gentity_s::draw()
{
    ImGui::Text("Model: %s", String::ConvertToString(model));
    ImGui::Text("Class: %s (%d)", String::ConvertToString(classname), classname);
    ImGui::Text("Code class: %s (%d)", String::ConvertToString(code_classname), code_classname);
    ImGui::Text("Script link: %s", String::ConvertToString(script_linkname));
    ImGui::Text("Target: %s", String::ConvertToString(target));
    ImGui::Text("Target name: %s", String::ConvertToString(targetname));
    ImGui::Text("Brush model: %d", state.index.brushmodel);
}
