#include "HeaderFiles/imgui/imgui.h"
#include "HeaderFiles/imgui/misc/imgui_stdlib.h"

#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <ios>
#include <raylib.h>
#include <rlImGui.h>
#include <string>
#include <tuple>
#include <vector>

namespace ImGui {
class ListBoxEasy {
	std::string label;
	int CurrentIndex = 0;
	std::vector<std::pair<std::string, bool>> items;

  public:
	ListBoxEasy() = default;

	const void SetLabel(const std::string &label) { this->label = label; }

	const void SetCurrentIndex(const int &CurrentIndex) {
		this->CurrentIndex = CurrentIndex;
	}

	const void AddItem(const std::string &item) {
		items.push_back(std::make_pair(item, false));
	}

	// Counting begins from zero!
	const void RemoveItem(const int &index) {
		items.erase(items.begin() + index);
	}

	const void display(void) const {
		if (BeginListBox(label.c_str())) {
			for (auto &i : items) {
				if (ImGui::Selectable(i.first.c_str(), i.second)) {
				}
			}
			EndListBox();
		}
	}
};
} // namespace ImGui

bool NeovimStatus = false, ShowDemoWindow = true;

const inline bool DetermineWhetherNeovimIsInstalledOrNot(void) {
	return system("nvim -v") == 0;
}

const inline void InstallNeovim(void) {
	const std::string InstallCommands[] = {
		"sudo apt -y install fuse wget",
		"wget "
		"\"https://github.com/neovim/neovim/releases/latest/download/"
		"nvim-linux-x86_64.appimage\"",
		"chmod u+x nvim-linux-x86_64.appimage",
		"mv nvim-linux-x86_64.appimage nvim", "mv nvim ~/.local/bin"};

	{
		std::string command;

		for (const std::string &i : InstallCommands) {
			command += i + ';';
		}

		system(command.c_str());
	}
}

const inline void UninstallNeovim(void) {
	const std::string NeovimPathes[] = {
		"~/.local/bin/nvim",   "~/.config/nvim", "~/.local/share/nvim",
		"~/.local/state/nvim", "~/.cache/nvim",	 "/usr/bin/nvim",
		"/usr/local/bin/nvim"};

	for (const std::string &i : NeovimPathes) {
		if (std::filesystem::exists(i))
			system(std::string("sudo rm -rf " + i).c_str());
	}
}

ImGui::ListBoxEasy plugins;

const inline void init(void) {
	std::ios::sync_with_stdio(false);

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);

	InitWindow(800, 450, "raylib [core] example - basic window");

	SetTargetFPS(30);

	rlImGuiSetup(true);

	ImGui::GetIO().IniFilename = NULL;

	plugins.SetLabel("Plugins");
}

std::string PluginName;

const inline void MainLoop(void) {
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		rlImGuiBegin();
		ImGui::ShowDemoWindow(&ShowDemoWindow);
		if (ImGui::Begin("NeovimGUIManager", NULL,
						 ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::Text(
				"Status: %s.",
				std::string(NeovimStatus ? "Installed" : "Not installed")
					.c_str());
			if (ImGui::Button("Install Neovim")) {
				InstallNeovim();
				NeovimStatus = DetermineWhetherNeovimIsInstalledOrNot();
			}
			if (ImGui::Button("Uninstall Neovim.")) {
				UninstallNeovim();
				NeovimStatus = DetermineWhetherNeovimIsInstalledOrNot();
			}
			plugins.display();
			ImGui::InputText("Name", &PluginName);
			if (ImGui::Button("Add") &&
				system(std::string("git ls-remote https://github.com/" +
								   PluginName)
						   .c_str()) == 0) {
				plugins.AddItem(PluginName);
			}
			ImGui::SameLine();
			if (ImGui::Button("Install")) {
			}
			ImGui::SameLine();
			if (ImGui::Button("Update")) {
			}
			ImGui::SameLine();
			if (ImGui::Button("Uninstall")) {
			}
			ImGui::End();
		}
		rlImGuiEnd();
		EndDrawing();
	}
}

const inline void clean(void) {
	rlImGuiShutdown();

	CloseWindow();
}

int main(void) {
	init();

	MainLoop();

	clean();

	return EXIT_SUCCESS;
}