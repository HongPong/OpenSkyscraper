#include <cassert>
#include <Rml/Controls.h>
#include <Rml/Debugger.h>

#include "Application.h"
#include "GUIManager.h"

using namespace OT;

GUIManager::GUIManager()
{
	window = NULL;
}

GUIManager::~GUIManager()
{
	//TODO: do cleanup here.
}

bool GUIManager::init(sf::RenderWindow * window)
{
	assert(window != NULL && "window must not be NULL");

	this->window = window;
	renderer.SetWindow(window);

	Rml::Core::SetRenderInterface(&renderer);
	Rml::Core::SetSystemInterface(&system);

	if (!Rml::Core::Initialise()) {
		LOG(ERROR, "unable to initialize Rml::Core");
		return false;
	}
	Rml::Controls::Initialise();

	return true;
}

Rml::Core::Input::KeyIdentifier GUIManager::translateKey(sf::Keyboard::Key key)
{
	return system.TranslateKey(key);
}

int GUIManager::getKeyModifiers()
{
	return system.GetKeyModifiers(window);
}
