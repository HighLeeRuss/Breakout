////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#include "kage/input.h"
#include "imgui/imgui.h"
#include "sfml/graphics.hpp"
#include "kage/world.h"

namespace kage
{
	namespace
	{
		bool g_keyStates[sf::Keyboard::KeyCount] = { false };
		bool g_keyStatesPrevious[sf::Keyboard::KeyCount] = { false };
		bool g_mouseStates[sf::Mouse::ButtonCount] = { false };
		bool g_mouseStatesPrevious[sf::Mouse::ButtonCount] = { false };

		XINPUT_STATE g_xboxStates[4];
		XINPUT_STATE g_xboxStatesPrevious[4];

	}

	namespace Input
	{
		void poll()
		{
			for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
			{
				g_keyStatesPrevious[i] = g_keyStates[i];
			}
			for (int i = 0; i < sf::Mouse::ButtonCount; ++i)
			{
				g_mouseStatesPrevious[i] = g_mouseStates[i];
			}
			for (int i = 0; i < 4; ++i)
			{
				g_xboxStatesPrevious[i] = g_xboxStates[i];
				XInputGetState(i, &g_xboxStates[i]);
			}
		}

		void process(sf::Event& event)
		{
			if (event.type == sf::Event::EventType::KeyPressed && !ImGui::GetIO().WantCaptureKeyboard && event.key.code>=0)
			{
				g_keyStates[event.key.code] = true;
			}
			if (event.type == sf::Event::EventType::KeyReleased && !ImGui::GetIO().WantCaptureKeyboard && event.key.code >= 0)
			{
				g_keyStates[event.key.code] = false;
			}
			if (event.type == sf::Event::EventType::MouseButtonPressed && !ImGui::GetIO().WantCaptureMouse)
			{
				g_mouseStates[event.mouseButton.button] = true;
			}
			if (event.type == sf::Event::EventType::MouseButtonReleased && !ImGui::GetIO().WantCaptureMouse)
			{
				g_mouseStates[event.mouseButton.button] = false;
			}
		}

		bool isKeyPressed(sf::Keyboard::Key key)
		{
			if (key < sf::Keyboard::KeyCount)
				return g_keyStates[key] && !g_keyStatesPrevious[key];
			else
				return false;
		}

		bool isKeyReleased(sf::Keyboard::Key key)
		{
			if (key < sf::Keyboard::KeyCount)
				return !g_keyStates[key] && g_keyStatesPrevious[key];
			else
				return false;
		}

		bool isKeyDown(sf::Keyboard::Key key)
		{
			if (key < sf::Keyboard::KeyCount)
				return g_keyStates[key];
			else
				return false;
		}

		bool isMousePressed(sf::Mouse::Button button)
		{
			if (button < sf::Mouse::ButtonCount)
				return g_mouseStates[button] && !g_mouseStatesPrevious[button];
			else
				return false;
		}

		bool isMouseReleased(sf::Mouse::Button button)
		{
			if (button < sf::Mouse::ButtonCount)
				return !g_mouseStates[button] && g_mouseStatesPrevious[button];
			else
				return false;
		}

		bool isMouseDown(sf::Mouse::Button button)
		{
			if (button < sf::Mouse::ButtonCount)
				return g_mouseStates[button];
			else
				return false;
		}

		kf::Vec2 getMousePosition(sf::RenderWindow& win)
		{
			sf::Vector2i pos = sf::Mouse::getPosition(win);
			return kf::Vec2(win.mapPixelToCoords(pos, win.getView())) / kage::World::scale();
		}

		bool isXboxPressed(unsigned int controller, unsigned short button)
		{
			if (controller > 3)
				controller = 0;
			return (g_xboxStates[controller].Gamepad.wButtons & ~g_xboxStatesPrevious[controller].Gamepad.wButtons) & button;
		}

		bool isXboxReleased(unsigned int controller, unsigned short button)
		{
			if (controller > 3)
				controller = 0;
			return (~g_xboxStates[controller].Gamepad.wButtons & g_xboxStatesPrevious[controller].Gamepad.wButtons) & button;
		}

		bool isXboxDown(unsigned int controller, unsigned short button)
		{
			if (controller > 3)
				controller = 0;
			return g_xboxStates[controller].Gamepad.wButtons & button;
		}

		kf::Vec2 getXboxThumb(unsigned int controller, unsigned int thumb)
		{
			if (controller > 3)
				controller = 0;
			if(thumb==0)
				return kf::Vec2(kf::clamp(g_xboxStates[controller].Gamepad.sThumbLX / 32767.0, -1.0, 1.0), kf::clamp(g_xboxStates[controller].Gamepad.sThumbLY / -32767.0, -1.0, 1.0));
			else
				return kf::Vec2(kf::clamp(g_xboxStates[controller].Gamepad.sThumbRX / 32767.0, -1.0, 1.0), kf::clamp(g_xboxStates[controller].Gamepad.sThumbRY / -32767.0, -1.0, 1.0));
		}

		float getXboxTrigger(unsigned int controller, unsigned int thumb)
		{
			if (controller > 3)
				controller = 0;
			if (thumb == 0)
				return g_xboxStates[controller].Gamepad.bLeftTrigger / 255.0f;
			else
				return g_xboxStates[controller].Gamepad.bRightTrigger / 255.0f;
		}

		void setXboxVibrate(unsigned int controller, float left, float right)
		{
			if (controller > 3)
				controller = 0;
			XINPUT_VIBRATION vib;
			vib.wLeftMotorSpeed = kf::saturate(left) * 65535;
			vib.wRightMotorSpeed = kf::saturate(right) * 65535;
			XInputSetState(controller, &vib);
		}

	}
}