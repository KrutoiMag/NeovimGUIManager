#include "../../../HeaderFiles/NeovimGUIManager/GUI/installer.hpp"
#include "../../../HeaderFiles/imgui/imgui.h"

#include <cstdlib>
#include <filesystem>

inline bool DetectedInstalledOrNot = false, InstalledOrNot = false;

const bool NeovimGUIManager::GUI::installer::installed(void) {
	if (!DetectedInstalledOrNot) {
		DetectedInstalledOrNot = true;

		InstalledOrNot = std::system("nvim -v >/dev/null 2>&1") == 0;
	}
	return InstalledOrNot;
}

const void NeovimGUIManager::GUI::installer::install(void) {
	if (!installed()) {
		uninstall();

		const std::string cmds[] = {
			"sudo apt -y install fuse wget",
			"wget "
			"https://github.com/neovim/neovim/releases/"
			"latest/download/nvim-linux-x86_64.appimage",
			"chmod u+x nvim-linux-x86_64.appimage",
			"mv nvim-linux-x86_64.appimage nvim",
			"mv nvim " + std::string(getenv("HOME")) + "/.local/bin"};
		{
			std::string command = "(";

			for (const std::string &i : cmds) {
				command += i + ';';
			}

			command += ") >/dev/null 2>&1";

			if (system(command.c_str()) == 0) {
				InstalledOrNot = true;
			}

			if (!std::filesystem::exists(std::string(getenv("HOME")) +
										 "/.config/nvim")) {
				system("mkdir ~/.config/nvim");
			}

			if (!std::filesystem::exists(std::string(getenv("HOME")) +
										 "/.local/share/nvim/site/pack")) {
				system("mkdir -p ~/.local/share/nvim/site/pack/*/start");
			}
		}
	}
}

const void NeovimGUIManager::GUI::installer::uninstall(void) {
	if (installed()) {
		if (std::filesystem::exists(std::string(getenv("HOME")) +
									"/.local/bin/nvim")) {
			system(std::string("sudo rm -rf " + std::string(getenv("HOME")) +
							   "/.local/bin/nvim")
					   .c_str());
			InstalledOrNot = false;
		}
	}
}

const void NeovimGUIManager::GUI::installer::show(void) {
	/*
	if (ImGui::Begin("Installer", NULL,
					 ImGuiWindowFlags_NoResize |
						 ImGuiWindowFlags_AlwaysAutoResize)) {
	*/
	ImGui::Text("Status: %s", installed() ? "Installed" : "Not installed");
	if (!installed()) {
		if (ImGui::Button("Install Neovim")) {
			install();
		}
	} else {
		if (ImGui::Button("Uninstall Neovim")) {
			uninstall();
		}
	}
	// }
	// ImGui::End();
}