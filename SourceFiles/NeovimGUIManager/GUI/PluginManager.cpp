#include "../../../HeaderFiles/NeovimGUIManager/GUI/PluginManager.hpp"
#include "../../../HeaderFiles/imgui/imgui.h"
#include "../../../HeaderFiles/imgui/misc/imgui_stdlib.h"

#include <filesystem>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

inline std::string PluginGitHubName;
inline std::vector<std::pair<std::string, bool>> plugins;
inline std::size_t SelectedPluginIndex = 0;
inline bool PluginNamesParsed = false;

const inline void ParsePluginNames(void) {
	if (!PluginNamesParsed) {
		for (const auto &i : std::filesystem::directory_iterator(
				 std::string(getenv("HOME")) +
				 "/.local/share/nvim/site/pack/*/start/")) {
			std::stringstream ss(i.path());

			std::string PluginName;

			while (std::getline(ss, PluginName, '/')) {
			}

			plugins.push_back(std::make_pair(PluginName, false));
		}
		PluginNamesParsed = true;
	}
}

const inline bool PluginExists(const std::string &PluginName) {
	std::stringstream ss(PluginName);

	std::string temp;

	while (std::getline(ss, temp, '/')) {
	}

	return std::filesystem::exists(std::string(getenv("HOME")) +
								   "/.local/share/nvim/site/pack/*/start/" +
								   temp);
}

const void NeovimGUIManager::GUI::PluginManager::show(void) {
	ParsePluginNames();
	/*
	if (ImGui::Begin("Plugin manager", NULL,
					 ImGuiWindowFlags_NoResize |
						 ImGuiWindowFlags_AlwaysAutoResize)) {
	*/
	if (ImGui::BeginListBox("Plguins")) {
		for (std::size_t i = 0; i < plugins.size(); i++) {
			if (ImGui::Selectable(plugins[i].first.c_str(),
								  [](const int &i) -> bool {
									  return SelectedPluginIndex == i;
								  }(i)))
				SelectedPluginIndex = i;

			if (SelectedPluginIndex == i)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}
	ImGui::InputText("GitHub URL", &PluginGitHubName);
	if (ImGui::Button("Add plugin")) {
		if (system(std::string("git ls-remote https://github.com/" +
							   PluginGitHubName + " > /dev/null 2>&1")
					   .c_str()) == 0)
			plugins.push_back(std::make_pair(PluginGitHubName, false));
	}
	ImGui::SameLine();
	if (ImGui::Button("Remove") &&
		!PluginExists(plugins[SelectedPluginIndex].first)) {
		plugins.erase(plugins.begin() + (SelectedPluginIndex + 1));
		SelectedPluginIndex = SelectedPluginIndex > 0 ? SelectedPluginIndex - 1
													  : SelectedPluginIndex;
	}
	ImGui::SameLine();
	if (ImGui::Button("Install")) {
		for (const auto &i : plugins) {
			system(std::string("git clone https://github.com/" + i.first +
								   " ~/.local/share/nvim/site/pack/*/start/" +
								   [&](void) -> std::string {
					   std::stringstream ss(i.first);

					   std::string RepoName;

					   while (std::getline(ss, RepoName, '/')) {
					   }

					   return RepoName;
				   }())
					   .c_str());
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Uninstall")) {
	}
	// }
	// ImGui::End();
}