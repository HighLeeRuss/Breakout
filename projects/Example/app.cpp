#include "app.h"

namespace App
{
	// External Globals. These are really implemented in app_main.cpp
	extern sf::RenderWindow g_window;
	extern sf::Clock g_clock;
	extern sf::Font g_font;
	extern bool g_running;
	extern kf::Xor128 g_rng;

	// Add your own variables here

	// Example of exposing a variable to other files.
	// This creates the memory for the variable.
	int exampleValue = 0;

	bool start()
	{
		// Add some physics colliders to the screen edges
		// Bottom
		kage::Physics::EdgeBuilder().start(0, 16.875).end(30, 16.875).friction(1).build(kage::Physics::getDefaultStatic());
		// Top
		kage::Physics::EdgeBuilder().start(0, 0).end(30, 0).friction(1).build(kage::Physics::getDefaultStatic());
		// Left
		kage::Physics::EdgeBuilder().start(0, 0).end(0, 16.875).friction(1).build(kage::Physics::getDefaultStatic());
		// Right
		kage::Physics::EdgeBuilder().start(30, 0).end(30, 16.875).friction(1).build(kage::Physics::getDefaultStatic());

		return true;
	}

	void update(float deltaT)
	{
		// Your main game logic goes here
	}

	void render()
	{
		// Draw a debug grid
		kage::World::debugGrid(g_window);

		// Render World
		kage::World::render(g_window);

		// The next line draws the physics debug info. This should be removed in a final release.
		kage::Physics::debugDraw(&g_window, 64);
	}

	void cleanup()
	{
		// Perform any clean up your project needs
	}
}
