#pragma once

#include <Rml/Core.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

#include "Path.h"

namespace OT
{
	class GUIManager;
	
	class GUI
	{
	public:
		GUIManager * manager;
		Rml::Core::Context * context;
		
		GUI(std::string name, GUIManager * manager);
		~GUI();
		
		bool handleEvent(sf::Event & event);
		void draw();
		
		Rml::Core::ElementDocument * loadDocument(Path path);
	};
}