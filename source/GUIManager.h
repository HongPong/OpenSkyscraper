#pragma once

#include <Rml/Core.h>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Rml/Renderer.h"
#include "Rml/SystemInterface.h"

namespace OT
{
	class GUI;
	
	class GUIManager
	{
		friend class GUI;
		
	public:
		GUIManager();
		~GUIManager();
		
		bool init(sf::RenderWindow * window);
		
		Rml::Core::Input::KeyIdentifier translateKey(sf::Keyboard::Key key);
		int getKeyModifiers();
		
	protected:
		sf::RenderWindow * window;
		
	private:
		RmlRenderer renderer;
		RmlSystemInterface system;
	};
}
