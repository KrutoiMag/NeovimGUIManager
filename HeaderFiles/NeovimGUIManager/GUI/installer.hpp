#pragma once

#ifndef NEOVIMGUIMANAGER_GUI_INSTALLER_HPP
#define NEOVIMGUIMANAGER_GUI_INSTALLER_HPP

namespace NeovimGUIManager {
	namespace GUI {
		class installer {
		  public:
			static const void show(void), install(void), uninstall(void);

			const static bool installed(void);
		};
	} // namespace GUI
} // namespace NeovimGUIManager

#endif // NEOVIMGUIMANAGER_GUI_INSTALLER_HPP