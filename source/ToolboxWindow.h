#pragma once
#include <Rml/Core/ElementDocument.h>
#include <Rml/Core/EventListener.h>
#include "GameObject.h"

namespace OT {
	
	class ToolboxWindow : public GameObject, private Rml::Core::EventListener
	{
	public:
		ToolboxWindow(Game * game) : GameObject(game) {
			window = NULL;
		}
		~ToolboxWindow() { close(); }
		
		void close();
		void reload();
		
		Rml::Core::ElementDocument * window;
		typedef std::set<Rml::Core::Element *> ElementSet;
		ElementSet buttons;
		
		void ProcessEvent(Rml::Core::Event & event);
		
		void updateSpeed();
		void updateTool();
	};
}
