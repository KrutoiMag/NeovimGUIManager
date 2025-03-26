#include "../../HeaderFiles/NeovimGUIManager/GUI.hpp"
#include "../../HeaderFiles/NeovimGUIManager/GUI/PluginManager.hpp"
#include "../../HeaderFiles/NeovimGUIManager/GUI/installer.hpp"
#include "../../HeaderFiles/imgui/imgui.h"
#include "../../HeaderFiles/rlImGui/rlImGui.h"
#include <cstddef>

const void NeovimGUIManager::GUI::init(void) {
	rlImGuiSetup(true);

	ImGui::GetIO().IniFilename = NULL;
}

const void NeovimGUIManager::GUI::show(void) {
	rlImGuiBegin();
	{
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(
			ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
		if (ImGui::Begin("##NeovimGUIManager", NULL,
						 ImGuiWindowFlags_NoResize |
							 ImGuiWindowFlags_NoTitleBar |
							 ImGuiWindowFlags_NoCollapse)) {
			if (ImGui::BeginTabBar("Tabs")) {
				if (ImGui::BeginTabItem("Installer")) {
					GUI::installer::show();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Plugin manager")) {
					GUI::PluginManager::show();
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
			ImGui::End();
		}
	}
	rlImGuiEnd();
}

const void NeovimGUIManager::GUI::clean(void) { rlImGuiShutdown(); }