////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KAGE_SHADERMANAGER_HEADER
#define KAGE_SHADERMANAGER_HEADER

#include <SFML/Graphics.hpp>


namespace kage
{
	namespace ShaderManager
	{
		sf::Shader*getShader(const std::string &filename);
		void preload(const std::string& filename);
	}
}

#endif