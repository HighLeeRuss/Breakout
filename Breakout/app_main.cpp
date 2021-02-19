#include "app.h"

namespace App
{
	sf::RenderWindow g_window;
	sf::Clock g_clock;
	sf::Font g_font;
	bool g_running = false;
	bool g_showInspector = false;
	kf::Xor128 g_rng;
	
	bool init()
	{
		g_rng.seed((kf::u32)time(0));
		
		// This sets the working directory to where the executable is.
		kage::initDirectory();

		// Start the KF log system, tell it to log to the console and a file.
		kf::LogSystem::getDefault().addCout();
		kf::LogSystem::getDefault().addFile("kage2d.log");
		kf_log("Started");

		g_window.create(sf::VideoMode(1920, 1080, 32), "Kage2D");
		g_window.setFramerateLimit(60);

		if (!getFont().loadFromFile("data/fonts/bluehigh.ttf"))
		{
			return false;
		}
		ImGui::CreateContext();
		ImGui::SFML::Init(g_window);

		// Initialise the physics system. Set the default gravity to 9.8m/s^2 down.
		kage::Physics::init(b2Vec2(0, 9.8f));

		return true;
	}

	void run()
	{
		g_running = true;

		if (!init())
		{
			return;
		}

		if (!start())
		{
			return;
		}

		while (g_window.isOpen() && g_running)
		{
			kage::Input::poll();

			// Events are things such as keys being pressed, the window closing, etc.
			// There could be several events waiting for us, so use a loop to process them all.
			sf::Event event;
			while (g_window.pollEvent(event))
			{
				ImGui::SFML::ProcessEvent(event);
				kage::Input::process(event);
				if (event.type == sf::Event::Closed)
				{
					g_window.close();
					break;
				}
				if (event.type == sf::Event::Resized)
				{
					//sf::View view = g_window.getDefaultView();
					//view.reset(sf::FloatRect(0, 0, event.size.width, event.size.height));
					//g_window.setView(view);
					kage::World::setViewFitAll(g_window, kf::Vector2(0, 0), 1920.0 / 64.0, 1080.0 / 64.0, false);
				}
			}
			if (kage::Input::isKeyPressed(sf::Keyboard::Pause))
			{
				kage::World::pause(!kage::World::pause());
			}
			if (kage::Input::isKeyPressed(sf::Keyboard::F12))
			{
				g_showInspector = !g_showInspector;
			}
			if (kage::Input::isKeyPressed(sf::Keyboard::Escape))
			{
				quit();
			}

			sf::Time deltaT_sfml = g_clock.restart();
			//float deltaT = deltaT_sfml.asSeconds();
			ImGui::SFML::Update(g_window, deltaT_sfml);

			kage::World::update(1.0f / 60.0f);

			update(1.0f / 60.0f);
			if (g_showInspector)
			{
				kage::World::inspector();
			}

			// Clear the window.
			g_window.clear();

			render();

			ImGui::SFML::Render(g_window);

			// Calling display will make the contents of the window appear on screen (before this, it was kept hidden in the back buffer).
			g_window.display();
		}

		cleanup();
	}

	sf::RenderWindow& getWindow()
	{
		return g_window;
	}

	sf::Clock& getClock()
	{
		return g_clock;
	}

	sf::Font& getFont()
	{
		return g_font;
	}
	
	kf::Xor128& getRNG()
	{
		return g_rng;
	}

	bool isRunning()
	{
		return g_running;
	}

	void quit()
	{
		g_running = false;
	}
}
	int main()
	{
		App::run();

		return 0;
	}
