#include "ui.h"
#include "imgui/imgui.h"
#include "iw_string.h"

void UILocalVar::drawLocalVar()
{
	ImGui::Text("Type: %d", type);
	ImGui::Text("Name: %s", name);
}

void UILocalVarContext::drawLocalVarContext()
{
	for (auto i = 0; i < 256; i++)
	{
		auto& localVar = table[i];

		const auto text = String::Format("%3d", i);
		if (ImGui::TreeNode(text)) {
			localVar.drawLocalVar();

			ImGui::TreePop();
		}
	}
}

void UiContext::drawUiContext()
{
    ImGui::Begin("UiContext", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::TreeNode("Menu")) {

		if (ImGui::TreeNode("Menu vars")) {

			localVars.drawLocalVarContext();

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Menu stack")) {
			
			ImGui::Text("Menu Count %d", openMenuCount);

			for (auto i = 0; i < openMenuCount; i++) {
				auto menu = menuStack[i];

				const auto text = String::Format("[%s] %s", menu->items == nullptr ? " " : "X", menu->window.name);

				if (ImGui::TreeNode(text)) {
					menu->draw();
					ImGui::TreePop();
				}
			}

			ImGui::TreePop();
		}

        if (ImGui::TreeNode("Menus")) {

            ImGui::Text("Menu Count %d", menuCount);

            for (auto i = 0; i < menuCount; i++) {
                auto menu = menus[i];

	            const auto text = String::Format("[%s] %s", menu->items == nullptr ? " " : "X", menu->window.name);

                if (ImGui::TreeNode(text)) {
                    menu->draw();
                    ImGui::TreePop();
                }
            }

            ImGui::TreePop();
        }

        ImGui::TreePop();
    }

    ImGui::End();
}
