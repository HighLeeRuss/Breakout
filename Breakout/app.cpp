#include "app.h"
#include "windows.h"

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
	int lives = 5;
	int highscore = 0;
	bool gameOver = false;
	bool started = false;
	bool running = false;
	bool gameWon = false;


	sf::Sprite* background;
	sf::Text scoreText;
	sf::Text livesText;
	sf::Text gameOverText;
	sf::Text highScoreText;
	sf::Text startGameText;
	sf::Text gameWonText;

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

		

		background = kage::TextureManager::getSprite("data/sky.jpg"); //get the sprite for the background
		kage::scaleSprite(background, g_window.getSize());

		startGameText.setFont(g_font);
		startGameText.setCharacterSize(240);
		startGameText.setPosition(550, 200);
		startGameText.setString("To Start\n Press S");
		startGameText.setFillColor(sf::Color::Black); //setting the text for the start screen
		
		

		

	
		
		
		return true;
	}

	void update(float deltaT)
	{
		// Your main game logic goes here
		if (kage::Input::isKeyPressed(sf::Keyboard::S)) //if player presses S calls the started bool
		{
			//kage::World::clear();
			started = true;
		}
		if (started == true) //if game has started then run alllllllll of this
		{
			auto paddle = kage::World::build<Paddle>();
			paddle->position(15, 14); //spawn the paddle



			auto ball = kage::World::build<Ball>();
			ball->position(15, 8);
			ball->velocity(5, 6); //spawn the ball

			for (int y = 0; y < 5; ++y)
			{
				for (int x = 0; x < 10; ++x)
				{
					auto brick = kage::World::build<Brick>();
					brick->position(15 - (x - 4.0) * 2.3, 3 + y);
				}
			}

			
			started = false;
			running = true;
		}
		
		if (running == true)
		{
			ShowCursor(false);
			kage::SoundManager::preload("data/NFF-soft-confirm.wav");

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

			highScoreText.setFont(g_font);
			highScoreText.setCharacterSize(60);
			highScoreText.setPosition(1550, 50);
			highScoreText.setString("Highscore:");
			highScoreText.setFillColor(sf::Color::Black);

			gameOverText.setFont(g_font);
			gameOverText.setCharacterSize(240);
			gameOverText.setPosition(450, 400);
			gameOverText.setString("GAME OVER\nPress Space");
			gameOverText.setFillColor(sf::Color::Red);

			gameWonText.setFont(g_font);
			gameWonText.setCharacterSize(240);
			gameWonText.setPosition(450, 200);
			gameWonText.setString("You Won\nPress Space to\n play again");
			gameWonText.setFillColor(sf::Color::Black);

			auto bricks = kage::World::findAllByTag("Brick");
			if (bricks.size() == 0)
			{
				gameWon = true;
			}

			auto ball = kage::World::findByTag("Ball");
			if (ball == 0 && (!gameWon && !gameOver))
			{
				lives = lives - 1;
				if (lives == 0)
				{
					gameOver = true;
				}
				else
				{
					auto ball = kage::World::build<Ball>();
					ball->position(15, 8);
					ball->velocity(5, 6);
				}
			
			}

			
			

			


			//ImGui::Begin("Game Stats");
			//ImGui::Text("Score = %d", score);
			//ImGui::InputInt("Lives = %d", &lives);
			//ImGui::End();

			scoreText.setString("Score: " + std::to_string(score));
			livesText.setString("Lives: " + std::to_string(lives));
			highScoreText.setString("Highscore: " + std::to_string(highscore));
			
		}

			if (score > highscore)
			{
				highscore = score;
			}

			if (gameOver && !gameWon)
			{
				if (kage::Input::isKeyPressed(sf::Keyboard::Space))
				{
					kage::World::clear();
					lives = 5;
					score = 0;
					gameOver = false;
					auto paddle = kage::World::build<Paddle>();
					paddle->position(15, 14);

					auto ball = kage::World::build<Ball>();
					ball->position(15, 8);
					ball->velocity(5, 6);

					for (int y = 0; y < 5; ++y)
					{
						for (int x = 0; x < 10; ++x)
						{
							auto brick = kage::World::build<Brick>();
							brick->position(15 - (x - 4.0) * 2.3, 3 + y);
						}
					}

				}
			}

			if (gameWon && !gameOver)
			{
				if (kage::Input::isKeyPressed(sf::Keyboard::Space))
				{
					kage::World::clear();
					lives = 5;
					score = 0;
					gameWon = false;
					auto paddle = kage::World::build<Paddle>();
					paddle->position(15, 14);

					auto ball = kage::World::build<Ball>();
					ball->position(15, 8);
					ball->velocity(5, 6);

					for (int y = 0; y < 5; ++y)
					{
						for (int x = 0; x < 10; ++x)
						{
							auto brick = kage::World::build<Brick>();
							brick->position(15 - (x - 4.0) * 2.3, 3 + y);
						}
					}

				}
			}

		
	}

	void render()
	{
		g_window.draw(*background);
		
		// Draw a debug grid
		kage::World::debugGrid(g_window);

		// Render World
		kage::World::render(g_window);

		if (started == false && running == false)
		{
			g_window.draw(startGameText);
		}
		g_window.draw(scoreText);
		g_window.draw(livesText);
		g_window.draw(highScoreText);

		if (gameOver && !gameWon)
		{
			g_window.draw(gameOverText);
		}

		if (gameWon)
		{
			g_window.draw(gameWonText);
		}

		// The next line draws the physics debug info. This should be removed in a final release.
		kage::Physics::debugDraw(&g_window, 64);
	}

	void cleanup()
	{
		// Perform any clean up your project needs
	}
}
