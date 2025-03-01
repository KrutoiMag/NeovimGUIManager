#include "../../HeaderFiles/NeovimGUIManager/window.hpp"
#include "../../HeaderFiles/NeovimGUIManager/GUI.hpp"

#include <raylib.h>

const void NeovimGUIManager::window::init(void) {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(800, 450, "NeovimGUIManager");

	SetTargetFPS(30);

	GUI::init();
}

const void NeovimGUIManager::window::MainLoop(void) {
	while (!WindowShouldClose()) {
		BeginDrawing();
		{
			ClearBackground(RAYWHITE);
			GUI::show();
		}
		EndDrawing();
	}
}

const void NeovimGUIManager::window::clean(void) {
	GUI::clean();
	CloseWindow();
}