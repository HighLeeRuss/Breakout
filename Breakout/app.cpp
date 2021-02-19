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
	int score = 0;
	int lives = 10;


	sf::Sprite* background;
	sf::Text scoreText;
	sf::Text livesText;

	bool start()
	{
		// Add some physics colliders to the screen edges
		// Bottom
		//kage::Physics::EdgeBuilder().start(0, 15).end(30, 16.875).friction(1).build(kage::Physics::getDefaultStatic());
		// Top
		kage::Physics::EdgeBuilder().start(0, 0).end(30, 0).friction(1).build(kage::Physics::getDefaultStatic());
		// Left
		kage::Physics::EdgeBuilder().start(0, 0).end(0, 16.875).friction(1).build(kage::Physics::getDefaultStatic());
		// Right
		kage::Physics::EdgeBuilder().start(30, 0).end(30, 16.875).friction(1).build(kage::Physics::getDefaultStatic());

		auto paddle = kage::World::build<Paddle>();
		paddle -> position(15, 14);

		auto ball = kage::World::build<Ball>();
		ball -> position(15, 8);
		ball -> velocity(5, 6);

		for (int y = 0; y < 5; ++y)
		{
			for (int x = 0; x < 10; ++x)
			{
				auto brick = kage::World::build<Brick>();
				brick->position(15 - (x - 4) * 2.3, 3 + y);
			}
		}

		background = kage::TextureManager::getSprite("data/sky.jpg");
		kage::scaleSprite(background, g_window.getSize());

		scoreText.setFont(g_font);
		scoreText.setCharacterSize(60);
		scoreText.setPosition(250, 50);
		scoreText.setString("Score:");
		scoreText.setFillColor(sf::Color::Black);

		livesText.setFont(g_font);
		livesText.setCharacterSize(60);
		livesText.setPosition(50, 50);
		livesText.setString("Lives:");
		livesText.setFillColor(sf::Color::Black);

		return true;
	}

	void update(float deltaT)
	{
		// Your main game logic goes here
		auto ball = kage::World::findByTag("Ball");
		if (ball == 0)
		{
			lives = lives - 1;
			auto ball = kage::World::build<Ball>();
			ball->position(15, 8);
			ball->velocity(5, 6);
		}

		//ImGui::Begin("Game Stats");
		//ImGui::Text("Score = %d", score);
		//ImGui::InputInt("Lives = %d", &lives);
		//ImGui::End();

		scoreText.setString("Score: " + std::to_string(score));
		scoreText.setString("Lives: " + std::to_string(lives));


	}

	void render()
	{
		g_window.draw(*background);
		
		// Draw a debug grid
		kage::World::debugGrid(g_window);

		// Render World
		kage::World::render(g_window);

		g_window.draw(scoreText);
		g_window.draw(livesText);

		// The next line draws the physics debug info. This should be removed in a final release.
		kage::Physics::debugDraw(&g_window, 64);
	}

	void cleanup()
	{
		// Perform any clean up your project needs
	}
}
