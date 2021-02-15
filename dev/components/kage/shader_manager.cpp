////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#include "kage/shader_manager.h"
#include <map>
#include <string>
#include "kage/system.h"

namespace
{
	long long g_maxId=0;
}

namespace kage
{
	namespace ShaderManager
	{
		std::map<std::string, sf::Shader*>& getShaders()
		{
			static std::map<std::string, sf::Shader*> s_shaders;
			return s_shaders;
		}

		sf::Shader*getShader(const std::string &filename)
		{
			std::map<std::string, sf::Shader*>::iterator it = getShaders().find(filename);
			if (it == getShaders().end())
			{
				sf::Shader *s = new sf::Shader;
				kage::initDirectory();
				if (!s->loadFromFile(filename,sf::Shader::Fragment))
				{
					// TODO: add default shaders literally.
				}
				getShaders()[filename] = s;
				return s;
			}
			return it->second;
		}

		void preload(const std::string& filename)
		{
			getShader(filename);
		}
	}
}
