#include "dvar.h"
#include "iw_string.h"
#include <cstring>
#include <imgui/imgui.h>
#include <iostream>

int DvarLimitsEnumeration::findIndexForString(const char* input)
{
    if (input == nullptr) {
        return 0;
    }

    for (auto i = 0; i < stringCount; i++) {
        if (std::strcmp(strings[i], input) == 0) {
            return i;
        }
    }

    return 0;
}

void DvarLimitsEnumeration::draw()
{
    ImGui::Text("Number of strings: %d", stringCount);

    if (strings != nullptr && ImGui::TreeNode("Strings")) {
        for (auto i = 0; i < stringCount; i++) {
            const auto string = strings[i];

            ImGui::Text(string);
        }

        ImGui::TreePop();
    }
}

void DvarLimitsInteger::draw()
{
    ImGui::Text("Min: %d", min);
    ImGui::Text("Max: %d", max);
}

void DvarLimitsValue::draw()
{
    ImGui::Text("Min: %g", min);
    ImGui::Text("Max: %g", max);
}

void DvarLimits::draw()
{
    if (ImGui::TreeNode("Enumeration")) {
        enumeration.draw();

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Integer")) {
        integer.draw();

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Value")) {
        value.draw();

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Vector")) {
        vector.draw();

        ImGui::TreePop();
    }
}

void DvarValueStringBuf::draw()
{
    ImGui::Text("String: %s", string);
}

void DvarValue::draw(DvarType_t type, dvar_s* dvar, DvarLimitsEnumeration* enumeration = nullptr)
{
    switch (type) {
    case DVAR_TYPE_BOOL:
        ImGui::Checkbox("Enabled", &enabled);
        break;

    case DVAR_TYPE_FLOAT:
        ImGui::InputFloat("Float", &value);
        break;

    case DVAR_TYPE_FLOAT_2:
        ImGui::InputFloat2("Float 2", vec2);
        break;

    case DVAR_TYPE_FLOAT_3:
        ImGui::InputFloat3("Float 3", vec3);
        break;

    case DVAR_TYPE_FLOAT_4:
        ImGui::InputFloat4("Float 4", vec4);
        break;

    case DVAR_TYPE_INT:
        ImGui::InputInt("Integer", &integer);
        break;

    case DVAR_TYPE_ENUM:
        ImGui::ListBox("Enum", &integer, enumeration->strings, enumeration->stringCount);
        break;

    case DVAR_TYPE_STRING:
        ImGui::Text("String: %s", string);
        static char buffer[256];
        if (ImGui::InputText("New string", buffer, IM_ARRAYSIZE(buffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
            Dvar::SetString(dvar, buffer);
            strcpy_s(buffer, "");
        };
        break;

    case DVAR_TYPE_FLOAT_3_COLOR:
        ImGui::ColorPicker3("Color", vec3);
        break;

    case DVAR_TYPE_COUNT:
        break;

    default:;
    }
}

void dvar_s::draw()
{
    ImGui::Text("Name: %s", name);
    ImGui::Text("Flags: %d", flags);
    ImGui::Text("Type: %d", type);
    ImGui::Text("Modified: %d", modified);
    ImGui::Text("Hash next: %d", hashNext);

    const auto text = String::Format("Current @ %p", offsetof(dvar_s, current));

    DvarLimitsEnumeration* enumeration = nullptr;

    if (type == DVAR_TYPE_ENUM) {
        enumeration = &domain.enumeration;
    }

    if (ImGui::TreeNode(text)) {
        current.draw(type, this, enumeration);
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Latched")) {
        latched.draw(type, this, enumeration);

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Reset")) {
        reset.draw(type, this, enumeration);

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Domain")) {
        domain.draw();

        ImGui::TreePop();
    }

    if (next != nullptr && ImGui::TreeNode("Next")) {
        next->draw();

        ImGui::TreePop();
    }
}

void Dvar::QueryDvars(const char* text)
{
    g_numMatchedDvars = 0;

    for (auto i = 0; i < *g_numDvars; i++) {
        const auto dvar = g_dvars[i];

        if (text == nullptr || strstr(dvar->name, text)) {
            g_matchedDvars[g_numMatchedDvars++] = dvar;
        }
    }
}

void Dvar::Draw()
{
    ImGui::Begin("Dvars", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Number of dvars: %d", *g_numDvars);

    static char dvarBuffer[128] = "";
    ImGui::InputText("Search", dvarBuffer, IM_ARRAYSIZE(dvarBuffer), ImGuiInputTextFlags_CallbackAlways, [](ImGuiTextEditCallbackData* data) {
        QueryDvars(data->Buf);
        return 0;
    });

    if (ImGui::TreeNode("Dvars")) {
        for (auto i = 0; i < g_numMatchedDvars; i++) {
            auto dvar = g_matchedDvars[i];

            if (dvar != nullptr && ImGui::TreeNode(dvar->name)) {
                dvar->draw();

                ImGui::TreePop();
            }
        }

        ImGui::TreePop();
    }

    ImGui::End();
}
