#include "menu.h"
#include "imgui/imgui.h"
#include "iw_string.h"

void ExpressionString::draw()
{
    ImGui::Text("String: %s", string);
}

void OperandInternalDataUnion::draw()
{
    ImGui::Text("Int value: %d", intVal);
    ImGui::Text("Float value: %g", floatVal);

    if (stringVal != nullptr && ImGui::TreeNode("String value")) {
        stringVal->draw();

        ImGui::TreePop();
    }

    if (function != nullptr && ImGui::TreeNode("Function")) {
        function->draw();

        ImGui::TreePop();
    }
}

void Operand::draw()
{
    ImGui::Text("Data type: %d", dataType);

    if (ImGui::TreeNode("Internals")) {
        internals.draw();

        ImGui::TreePop();
    }
}

void EntryInternalData::draw()
{
    ImGui::Text("Operation: %d", op);

    if (ImGui::TreeNode("Operand")) {
        operand.draw();

        ImGui::TreePop();
    }
}

void SetLocalVarData::draw()
{
    ImGui::Text("Local variable: %s", localVarName);

    if (expression != nullptr && ImGui::TreeNode("Expression")) {
        expression->draw();

        ImGui::TreePop();
    }
}

void ConditionalScript::draw()
{
    if (eventHandlerSet != nullptr && ImGui::TreeNode("Event handler set")) {
        eventHandlerSet->draw();

        ImGui::TreePop();
    }

    if (eventExpression != nullptr && ImGui::TreeNode("Event expression")) {
        eventExpression->draw();

        ImGui::TreePop();
    }
}

void ExpressionEntry::draw()
{
    ImGui::Text("Type: %d", type);

    if (ImGui::TreeNode("Data")) {
        data.draw();

        ImGui::TreePop();
    }
}

void Statement::draw()
{
    ImGui::Text("Number of entries: %d", numEntries);

    if (entries != nullptr && ImGui::TreeNode("Entries")) {
        for (auto i = 0; i < numEntries; i++) {
            auto entry = entries[i];

            auto const text = String::Format("%3d", i);

            if (ImGui::TreeNode(text)) {
                entry.draw();

                ImGui::TreePop();
            }
        }

        ImGui::TreePop();
    }

    if (supportingData != nullptr && ImGui::TreeNode("Supporting data")) {
        supportingData->draw();

        ImGui::TreePop();
    }
}

void ItemFloatExpression::draw()
{
    ImGui::Text("Target: %d", target);

    if (expression != nullptr && ImGui::TreeNode("Expression")) {
        expression->draw();

        ImGui::TreePop();
    }
}

void EventData::draw()
{
    ImGui::Text("Unconditional script: %s", unconditionalScript);

    if (conditionalScript != nullptr && ImGui::TreeNode("Conditional script")) {
        conditionalScript->draw();

        ImGui::TreePop();
    }

    if (elseScript != nullptr && ImGui::TreeNode("Else script")) {
        elseScript->draw();

        ImGui::TreePop();
    }

    if (setLocalVarData != nullptr && ImGui::TreeNode("Set local variable data")) {
        setLocalVarData->draw();

        ImGui::TreePop();
    }
}

void MenuEventHandler::draw()
{
    ImGui::Text("Type: %d", eventType);

    if (ImGui::TreeNode("Data")) {
        eventData.draw();

        ImGui::TreePop();
    }
}

void MenuEventHandlerSet::draw()
{
    ImGui::Text("Number of event handlers: %d", eventHandlerCount);

    if (eventHandlers != nullptr && ImGui::TreeNode("Event handlers")) {
        for (auto i = 0; i < eventHandlerCount; i++) {
            auto handler = eventHandlers[i];

            auto const text = String::Format("%3d", i);

            if (handler != nullptr && ImGui::TreeNode(text)) {
                handler->draw();

                ImGui::TreePop();
            }
        }

        ImGui::TreePop();
    }
}

void ItemKeyHandler::draw()
{
    ImGui::Text("Key: %d", key);

    if (action != nullptr && ImGui::TreeNode("Action")) {
        action->draw();

        ImGui::TreePop();
    }

    if (next != nullptr && ImGui::TreeNode("Next")) {
        next->draw();

        ImGui::TreePop();
    }
}

void NewsTicker::draw()
{
    ImGui::Text("Id: %d", feedId);
    ImGui::Text("Speed: %d", speed);
    ImGui::Text("Spacing: %d", spacing);
}

void ColumnInfo::draw()
{
    ImGui::Text("Position: %d", pos);
    ImGui::Text("Width: %d", width);
    ImGui::Text("Max characters: %d", maxChars);
    ImGui::Text("Alignment: %d", alignment);
}

void ListBox::draw()
{
    ImGui::Text("Width: %g", elementWidth);
    ImGui::Text("Height: %g", elementHeight);
    ImGui::Text("Style: %d", elementStyle);
    ImGui::Text("Columns: %d", numColumns);

    if (ImGui::TreeNode("Column info")) {
        for (auto i = 0; i < MAX_LB_COLUMNS; i++) {
            auto& info = columnInfo[i];

            auto const text = String::Format("%3d", i);

            if (ImGui::TreeNode(text)) {
                info.draw();

                ImGui::TreePop();
            }
        }

        ImGui::TreePop();
    }

    if (doubleClick != nullptr && ImGui::TreeNode("Double click")) {
        doubleClick->draw();

        ImGui::TreePop();
    }

    ImGui::Text("Not selectable: %d", notselectable);
    ImGui::Text("No scrollbars: %d", noscrollbars);
    ImGui::Text("Use paging: %d", usepaging);
}

void EditField::draw()
{
    ImGui::Text("Minimum: %g", minVal);
    ImGui::Text("Maximum: %g", maxVal);
    ImGui::Text("Default: %g", defVal);
    ImGui::Text("Range: %g", range);
    ImGui::Text("Max characters: %d", maxChars);
    ImGui::Text("Max go to next: %d", maxCharsGotoNext);
    ImGui::Text("Max paint: %d", maxPaintChars);
    ImGui::Text("Paint offset: %d", paintOffset);
}

void MultiDef::draw()
{
    if (ImGui::TreeNode("Dvar list")) {
        for (auto& dvar : dvarList) {
            ImGui::Text(dvar);
        }

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Dvar strings")) {
        for (auto& dvar : dvarStr) {
            ImGui::Text(dvar);
        }

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Dvar values")) {
        for (auto& value : dvarValue) {
            ImGui::Text("%g", value);
        }

        ImGui::TreePop();
    }

    ImGui::Text("Count: %d", count);
    ImGui::Text("String def: %d", strDef);
}

void TextScroll::draw()
{
    ImGui::Text("Start time: %d", startTime);
}

void ItemData::draw()
{
    ImGui::Text("Enum dvar name: %s", enumDvarName);

    if (listBox != nullptr && ImGui::TreeNode("List box")) {
        listBox->draw();

        ImGui::TreePop();
    }

    if (editField != nullptr && ImGui::TreeNode("Edit field")) {
        editField->draw();

        ImGui::TreePop();
    }

    if (multi != nullptr && ImGui::TreeNode("Multi")) {
        multi->draw();

        ImGui::TreePop();
    }

    if (newsTicker != nullptr && ImGui::TreeNode("News ticker")) {
        newsTicker->draw();

        ImGui::TreePop();
    }

    if (textScroll != nullptr && ImGui::TreeNode("Action")) {
        textScroll->draw();

        ImGui::TreePop();
    }
}

void Rect::draw()
{
    ImGui::Text("X position: %g", x);
    ImGui::Text("Y position: %g", y);
    ImGui::Text("Width: %g", w);
    ImGui::Text("Height: %g", h);
    ImGui::Text("Horizontal align: %d", horzAlign);
    ImGui::Text("Vertical align: %d", vertAlign);
}

void Window::draw()
{
    ImGui::Text("Name: %s", name);

    if (ImGui::TreeNode("Rectangle")) {
        rect.draw();

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Rectangle client")) {
        rectClient.draw();

        ImGui::TreePop();
    }

    ImGui::Text("Group: %s", group);

    ImGui::Text("Style: %d", style);
    ImGui::Text("Border: %d", border);
    ImGui::Text("Owner draw: %d", ownerDraw);
    ImGui::Text("Owner draw flags: %d", ownerDrawFlags);
    ImGui::Text("Border size: %g", borderSize);
    ImGui::Text("Static flags: %d", staticFlags);
    ImGui::Text("Dynamic flags: %d", dynamicFlags);
    ImGui::Text("Next time: %d", nextTime);
}

void Item::draw()
{
    if (ImGui::TreeNode("Window")) {
        window.draw();

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Text rectangle")) {
        textRect.draw();

        ImGui::TreePop();
    }

    ImGui::Text("Type: %d", type);
    ImGui::Text("Data type: %d", dataType);
    ImGui::Text("Align: %d", align);
    ImGui::Text("Font enum: %d", fontEnum);
    ImGui::Text("Text align mode: %d", textAlignMode);
    ImGui::Text("Text align X: %g", textAlignX);
    ImGui::Text("Text align Y: %g", textAlignY);
    ImGui::Text("Text scale: %g", textScale);
    ImGui::Text("Text style: %d", type);
    ImGui::Text("Game message window index: %d", gameMsgWindowIndex);
    ImGui::Text("Game message window mode: %d", gameMsgWindowMode);
    ImGui::Text("Text: %s", text);
    ImGui::Text("Save game info: %d", textSaveGameInfo);

    if (parent != nullptr && ImGui::TreeNode("Multi")) {
        parent->draw();

        ImGui::TreePop();
    }

    if (mouseEnterText != nullptr && ImGui::TreeNode("Mouse enter text")) {
        mouseEnterText->draw();

        ImGui::TreePop();
    }

    if (mouseExitText != nullptr && ImGui::TreeNode("Mouse exit text")) {
        mouseExitText->draw();

        ImGui::TreePop();
    }

    if (mouseEnter != nullptr && ImGui::TreeNode("Mouse enter")) {
        mouseEnter->draw();

        ImGui::TreePop();
    }

    if (mouseExit != nullptr && ImGui::TreeNode("Mouse exit")) {
        mouseExit->draw();

        ImGui::TreePop();
    }

    if (action != nullptr && ImGui::TreeNode("Action")) {
        action->draw();

        ImGui::TreePop();
    }

    if (accept != nullptr && ImGui::TreeNode("Accept")) {
        accept->draw();

        ImGui::TreePop();
    }

    if (onFocus != nullptr && ImGui::TreeNode("Enter focus")) {
        onFocus->draw();

        ImGui::TreePop();
    }

    if (leaveFocus != nullptr && ImGui::TreeNode("Leave focus")) {
        leaveFocus->draw();

        ImGui::TreePop();
    }

    if (onKey != nullptr && ImGui::TreeNode("On key")) {
        onKey->draw();

        ImGui::TreePop();
    }

    ImGui::Text("Dvar: %s", dvar);
    ImGui::Text("Dvar test: %s", dvarTest);
    ImGui::Text("Dvar enable: %s", enableDvar);
    ImGui::Text("Dvar flags: %d", dvarFlags);
    ImGui::Text("Special: %g", special);
    ImGui::Text("Cursor position: %d", cursorPos);

    if (ImGui::TreeNode("Type data")) {
        typeData.draw();

        ImGui::TreePop();
    }

    ImGui::Text("Image track: %d", imageTrack);
    ImGui::Text("Float expression count: %d", floatExpressionCount);

    if (floatExpressions != nullptr && ImGui::TreeNode("Float expression")) {
        floatExpressions->draw();

        ImGui::TreePop();
    }

    if (visibleExp != nullptr && ImGui::TreeNode("Visible expression")) {
        visibleExp->draw();

        ImGui::TreePop();
    }

    if (disabledExp != nullptr && ImGui::TreeNode("Disabled expression")) {
        disabledExp->draw();

        ImGui::TreePop();
    }

    if (textExp != nullptr && ImGui::TreeNode("Text expression")) {
        textExp->draw();

        ImGui::TreePop();
    }

    if (materialExp != nullptr && ImGui::TreeNode("Material Expression")) {
        materialExp->draw();

        ImGui::TreePop();
    }
}

void StaticDvar::draw()
{
    ImGui::Text("Dvar name: %s", dvarName);

    if (dvar != nullptr && ImGui::TreeNode("Dvar")) {
        dvar->draw();

        ImGui::TreePop();
    }
}

void StaticDvarList::draw()
{
    ImGui::Text("Number of static dvars: %d", numStaticDvars);

    if (staticDvars != nullptr && ImGui::TreeNode("Static dvars")) {
        for (auto i = 0; i < numStaticDvars; i++) {
            auto dvar = staticDvars[i];

            auto const text = String::Format("%3d", i);

            if (dvar != nullptr && ImGui::TreeNode(text)) {
                dvar->draw();

                ImGui::TreePop();
            }
        }

        ImGui::TreePop();
    }
}

void FunctionList::draw()
{
    ImGui::Text("Number of functions: %d", totalFunctions);

    if (functions != nullptr && ImGui::TreeNode("Functions")) {
        for (auto i = 0; i < totalFunctions; i++) {
            auto function = functions[i];

            auto const text = String::Format("%3d", i);

            if (function != nullptr && ImGui::TreeNode(text)) {
                function->draw();

                ImGui::TreePop();
            }
        }

        ImGui::TreePop();
    }
}

void StringList::draw()
{
    ImGui::Text("Number of strings: %d", totalStrings);

    if (strings != nullptr && ImGui::TreeNode("Functions")) {
        for (auto i = 0; i < totalStrings; i++) {
            auto string = strings[i];

            ImGui::Text(string);
        }

        ImGui::TreePop();
    }
}

void ExpressionSupportingData::draw()
{
    if (ImGui::TreeNode("UI functions")) {
        uifunctions.draw();

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Static dvars")) {
        staticDvarList.draw();

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("UI strings")) {
        uiStrings.draw();

        ImGui::TreePop();
    }
}

void MenuTransition::draw()
{
    ImGui::Text("Transition type: %d", transitionType);
    ImGui::Text("Start time: %d", startTime);
    ImGui::Text("Start value: %g", startVal);
    ImGui::Text("End value: %g", endVal);
    ImGui::Text("Time: %g", time);
    ImGui::Text("End trigger type: %d", endTriggerType);
}

void MenuDefinition::draw()
{
	if (ImGui::Button("Open"))
	{
		Menu::OpenMenu(0, window.name);
	}

    if (ImGui::TreeNode("Window")) {
        window.draw();

        ImGui::TreePop();
    }

    ImGui::Text("Font: %s", font);
    ImGui::Text("Fullscreen: %d", fullscreen);
    ImGui::Text("Item count: %d", itemCount);
    ImGui::Text("Font index: %d", fontIndex);
    ImGui::Text("Cursor items: %d", cursorItems);
    ImGui::Text("Fade cycle: %d", fadeCycle);

    ImGui::Text("Fade clamp: %g", fadeClamp);
    ImGui::Text("Fade amount: %g", fadeAmount);
    ImGui::Text("Fade in amount: %g", fadeInAmount);
    ImGui::Text("Blur radius: %g", blurRadius);

    if (onOpen != nullptr && ImGui::TreeNode("On open")) {
        onOpen->draw();

        ImGui::TreePop();
    }

    if (onRequestClose != nullptr && ImGui::TreeNode("On request close")) {
        onRequestClose->draw();

        ImGui::TreePop();
    }

    if (onClose != nullptr && ImGui::TreeNode("On close")) {
        onClose->draw();

        ImGui::TreePop();
    }

    if (onEsc != nullptr && ImGui::TreeNode("On escape")) {
        onEsc->draw();

        ImGui::TreePop();
    }

    if (execKeys != nullptr && ImGui::TreeNode("Exec keys")) {
        execKeys->draw();

        ImGui::TreePop();
    }

    if (visibleExp != nullptr && ImGui::TreeNode("Visible expression")) {
        visibleExp->draw();

        ImGui::TreePop();
    }

    ImGui::Text("Allowed binding: %s", allowedBinding);
    ImGui::Text("Sound name: %s", soundName);
    ImGui::Text("Image track: %d", imageTrack);

    if (rectXExp != nullptr && ImGui::TreeNode("Rectangle X expression")) {
        rectXExp->draw();

        ImGui::TreePop();
    }

    if (rectYExp != nullptr && ImGui::TreeNode("Rectangle Y expression")) {
        rectYExp->draw();

        ImGui::TreePop();
    }

    if (rectHExp != nullptr && ImGui::TreeNode("Rectangle H expression")) {
        rectHExp->draw();

        ImGui::TreePop();
    }

    if (rectWExp != nullptr && ImGui::TreeNode("Rectangle W expression")) {
        rectWExp->draw();

        ImGui::TreePop();
    }

    if (openSoundExp != nullptr && ImGui::TreeNode("Open sound expression")) {
        openSoundExp->draw();

        ImGui::TreePop();
    }

    if (closeSoundExp != nullptr && ImGui::TreeNode("Close sound expression")) {
        closeSoundExp->draw();

        ImGui::TreePop();
    }

    if (expressionData != nullptr && ImGui::TreeNode("Expression supporting data")) {
        expressionData->draw();

        ImGui::TreePop();
    }

	if (ImGui::TreeNode("Items")) {
		for (auto i = 0; i < itemCount; i++) {
			auto& item = items[i];

			auto const text = String::Format("%3d - %s", i, item->window.name);

			if (item != nullptr && ImGui::TreeNode(text)) {
				item->draw();

				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}
}

void MenuList::draw()
{
	ImGui::Text("Name: %s", name);
	ImGui::Text("Number of menus: %d", menuCount);

	if (menus != nullptr && ImGui::TreeNode("Menus")) {
		for (auto i = 0; i < menuCount; i++) {
			auto menu = menus[i];

			auto const text = String::Format("%3d", i);

			if (menu != nullptr && ImGui::TreeNode(text)) {
				menu->draw();

				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}
}
