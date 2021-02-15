////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KAGE_INPUT_HEADER
#define KAGE_INPUT_HEADER
#include "kf/kf_vector.h"
#include "sfml/window.hpp"
#include "sfml/graphics.hpp"
#include <windows.h>
#include "xinput.h"

namespace kage
{
	namespace Input
	{
		// Update the state of the input system. Perform this once per frame.
		// Poll should be called either before the event loop (where process is called)
		// or at the very end of the main update.
		void poll();

		// Process keyboard and mouse events from SFML. This tracks key/mouse up and down events.
		void process(sf::Event& event);

// Keyboard

		// Return true if the specified key was pressed during the last update.
		bool isKeyPressed(sf::Keyboard::Key key);

		// Return true if the specified key was released during the last update.
		bool isKeyReleased(sf::Keyboard::Key key);

		// Return true if the specified key was down during the last update. (continuous)
		bool isKeyDown(sf::Keyboard::Key key);

// Mouse

		// Return true if the specified button was pressed during the last update.
		bool isMousePressed(sf::Mouse::Button button);

		// Return true if the specified button was released during the last update.
		bool isMouseReleased(sf::Mouse::Button button);

		// Return true if the specified button was down during the last update. (continuous)
		bool isMouseDown(sf::Mouse::Button button);

		// Return position in world coordinates of the mouse within the specified window.
		kf::Vec2 getMousePosition(sf::RenderWindow &win);

// Xbox
		bool isXboxPressed(unsigned int controller, unsigned short button);
		bool isXboxReleased(unsigned int controller, unsigned short button);
		bool isXboxDown(unsigned int controller, unsigned short button);
		kf::Vec2 getXboxThumb(unsigned int controller, unsigned int thumb);
		float getXboxTrigger(unsigned int controller, unsigned int thumb);
		void setXboxVibrate(unsigned int controller, float left, float right);
	}
}
#endif
