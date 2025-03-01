#include "../../HeaderFiles/NeovimGUIManager/neovim.hpp"

#include <cstdlib>
#include <filesystem>
#include <string>

inline bool DetectedInstalledOrNot = false, InstalledOrNot = false;

const bool NeovimGUIManager::neovim::installed(void) {
	if (!DetectedInstalledOrNot) {
		DetectedInstalledOrNot = true;

		InstalledOrNot = std::system("nvim -v >/dev/null 2>&1") == 0;
	}
	return InstalledOrNot;
}

const void NeovimGUIManager::neovim::install(void) {
	if (!installed()) {
		const std::string cmds[] = {
			"sudo apt -y install fuse wget",
			"wget "
			"https://github.com/neovim/neovim/releases/"
			"latest/download/nvim-linux-x86_64.appimage",
			"chmod u+x nvim-linux-x86_64.appimage",
			"mv nvim-linux-x86_64.appimage nvim", "mv nvim ~/.local/bin"};
		{
			std::string command = "(";

			for (const std::string &i : cmds) {
				command += i + ';';
			}

			command += ") >/dev/null 2>&1";

			if (system(command.c_str()) == 0) {
				InstalledOrNot = true;
			}
		}
	}
}

const void NeovimGUIManager::neovim::uninstall(void) {
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