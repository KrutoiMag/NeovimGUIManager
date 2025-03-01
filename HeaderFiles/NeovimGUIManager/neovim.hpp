#pragma once

#ifndef NEOVIMGUIMANAGER_NEOVIM_HPP
#define NEOVIMGUIMANAGER_NEOVIM_HPP

namespace NeovimGUIManager {
	class neovim {
	  public:
		const static bool installed(void);

		const static void install(void), uninstall(void);
	};
} // namespace NeovimGUIManager

#endif // NEOVIMGUIMANAGER_NEOVIM_HPP