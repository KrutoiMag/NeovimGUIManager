#include "../../HeaderFiles/NeovimGUIManager/window.hpp"

#include <cstdlib>
#include <ios>

int main(void) {
	std::ios::sync_with_stdio(false);

	NeovimGUIManager::window::init();
	NeovimGUIManager::window::MainLoop();
	NeovimGUIManager::window::clean();

	return EXIT_SUCCESS;
}