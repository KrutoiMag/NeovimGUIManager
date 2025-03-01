#include "../../HeaderFiles/NeovimGUIManager/GUI.hpp"
#include "../../HeaderFiles/NeovimGUIManager/neovim.hpp"
#include "../../HeaderFiles/imgui/imgui.h"
#include "../../HeaderFiles/rlImGui/rlImGui.h"

const void NeovimGUIManager::GUI::init(void) {
	rlImGuiSetup(true);

	ImGui::GetIO().IniFilename = NULL;
}

const void NeovimGUIManager::GUI::show(void) {
	rlImGuiBegin();
	{
		if (ImGui::Begin("NeovimGUIManager", NULL,
						 ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::Text("Status: %s",
						neovim::installed() ? "Installed" : "Not installed");
			if (!neovim::installed()) {
				if (ImGui::Button("Install Neovim")) {
					neovim::install();
				}
			} else {
				if (ImGui::Button("Uninstall Neovim")) {
					neovim::uninstall();
				}
			}
			ImGui::End();
		}
	}
	rlImGuiEnd();
}

const void NeovimGUIManager::GUI::clean(void) { rlImGuiShutdown(); }