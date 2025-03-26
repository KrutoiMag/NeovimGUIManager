#pragma once

#ifndef NEOVIMGUIMANAGER_DATA_HPP
#define NEOVIMGUIMANAGER_DATA_HPP

#include <cstdlib>
#include <string>

namespace NeovimGUIManager {
	namespace data {
		namespace pathes {
#if defined(unix) || defined(__unix) || defined(__unix__)
			const std::string NeovimExecutable =
				std::string(getenv("HOME")) + "/.local/bin";
			const std::string NeovimHome =
				std::string(getenv("HOME")) + "/.config/nvim";
		} // namespace pathes
		namespace commands {
			namespace InstallNeovim {
				const std::string deps = "sudo apt -y install fuse wget";
			}
			namespace UninstallNeovim {}
		} // namespace commands
#endif
	} // namespace data
} // namespace NeovimGUIManager

#endif // NEOVIMGUIMANAGER_DATA_HPP