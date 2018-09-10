#include "structure.h"
#include "iw_string.h"
#include <imgui/imgui.h>

void enumEntry::draw()
{
    ImGui::Text("Name: %s", name);
    ImGui::Text("Index: %d", index);
}

void definedEnum::draw()
{
    ImGui::Text("Number of entries: %d", entryCount);

    if (ImGui::TreeNode("Entries")) {

        for (auto i = 0; i < entryCount; i++) {
			auto& entry = entries[i];

			auto const text = String::Format("%d", i);

            if (ImGui::TreeNode(text)) {
				entry.draw();

                ImGui::TreePop();
            }
        }

        ImGui::TreePop();
    }
}

void structuredDataItem_t::draw()
{
	ImGui::Text("Type: %d", type);
	ImGui::Text("Index: %d", index);
	ImGui::Text("Offset: %d", offset);
}

void structureEntry::draw()
{
	ImGui::Text("Name: %s", name);

	if (ImGui::TreeNode("Item")) {
		item.draw();

		ImGui::TreePop();
	}
}

void definedStructure::draw()
{
	ImGui::Text("Number of entries: %d", entryCount);

	if (ImGui::TreeNode("Entries")) {

		for (auto i = 0; i < entryCount; i++) {
			auto& entry = entries[i];

			auto const text = String::Format("%d", i);

			if (ImGui::TreeNode(text)) {
				entry.draw();

				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}

	ImGui::Text("Size: %d", size);
}

void structuredDataIndexedArray_t::draw()
{
	ImGui::Text("Index: %d", numItems);

	if (ImGui::TreeNode("Item")) {
		item.draw();

		ImGui::TreePop();
	}
}

void structuredDataEnumArray_t::draw()
{
	ImGui::Text("Index: %d", enumIndex);

	if (ImGui::TreeNode("Item")) {
		item.draw();

		ImGui::TreePop();
	}
}

void StructuredData::draw()
{
	ImGui::Text("Version: %d", version);
	ImGui::Text("Hash: %d", hash);

	ImGui::Text("Number of enums: %d", enumCount);
	if (ImGui::TreeNode("Enums")) {

		for (auto i = 0; i < enumCount; i++) {
			auto& entry = enums[i];

			auto const text = String::Format("%d", i);

			if (ImGui::TreeNode(text)) {
				entry.draw();

				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}

	ImGui::Text("Number of structures: %d", structureCount);
	if (ImGui::TreeNode("Structures")) {

		for (auto i = 0; i < structureCount; i++) {
			auto& entry = structures[i];

			auto const text = String::Format("%d", i);

			if (ImGui::TreeNode(text)) {
				entry.draw();

				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}

	ImGui::Text("Number of indexed arrays: %d", indexedArrayCount);
	if (ImGui::TreeNode("Indexed arrays")) {

		for (auto i = 0; i < indexedArrayCount; i++) {
			auto& entry = indexedArrays[i];

			auto const text = String::Format("%d", i);

			if (ImGui::TreeNode(text)) {
				entry.draw();

				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}

	ImGui::Text("Number of enum arrays: %d", enumArrayCount);
	if (ImGui::TreeNode("Enum arrays")) {

		for (auto i = 0; i < enumArrayCount; i++) {
			auto& entry = enumArrays[i];

			auto const text = String::Format("%d", i);

			if (ImGui::TreeNode(text)) {
				entry.draw();

				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Root item")) {
		rootItem.draw();

		ImGui::TreePop();
	}

}
