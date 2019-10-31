#include <cassert>
#ifdef BUILD_DEBUG
#include <Rml/Debugger/Debugger.h>
#endif

#include "Application.h"
#include "GUI.h"
#include "GUIManager.h"
#include "OpenGL.h"

using namespace OT;


GUI::GUI(std::string name, GUIManager * manager)
{
	assert(manager && "GUI requires a GUIManager");

	this->manager = manager;
	unsigned width = manager->window->getView().getSize().x;
	unsigned height = manager->window->getView().getSize().y;
	context = Rml::Core::CreateContext(name.c_str(), Rml::Core::Vector2i(width, height));
	assert(context && "unable to initialize context");
}

GUI::~GUI()
{
	context->RemoveReference();
	context = NULL;
}

bool GUI::handleEvent(sf::Event & event)
{
	switch (event.type) {
		case sf::Event::Resized:
			this->context->SetDimensions(Rml::Core::Vector2i(
											manager->window->getView().getSize().x,
											manager->window->getView().getSize().y));
			return true;
		case sf::Event::MouseMoved:
			context->ProcessMouseMove(event.mouseMove.x, event.mouseMove.y, manager->getKeyModifiers());
			return true;
		case sf::Event::MouseButtonPressed:
			context->ProcessMouseButtonDown(event.mouseButton.button, manager->getKeyModifiers());
			return true;
		case sf::Event::MouseButtonReleased:
			context->ProcessMouseButtonUp(event.mouseButton.button, manager->getKeyModifiers());
			return true;
		case sf::Event::MouseWheelMoved:
			return context->ProcessMouseWheel(event.mouseWheel.delta, manager->getKeyModifiers());
		case sf::Event::TextEntered:
			return context->ProcessTextInput(event.text.unicode);
		case sf::Event::KeyPressed:
			return context->ProcessKeyDown(manager->translateKey(event.key.code), manager->getKeyModifiers());
		case sf::Event::KeyReleased:
			return context->ProcessKeyUp(manager->translateKey(event.key.code), manager->getKeyModifiers());
	}
	return false;
}

void GUI::draw()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	unsigned width = manager->window->getView().getSize().x;
	unsigned height = manager->window->getView().getSize().y;
	glOrtho(0.0, width, height, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	context->Update();
	context->Render();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

Rml::Core::ElementDocument * GUI::loadDocument(Path path)
{
	DataManager::Paths paths = App->data.paths(Path("gui").down(path));
	for (DataManager::Paths::iterator p = paths.begin(); p != paths.end(); p++) {
		Rml::Core::ElementDocument * document = context->LoadDocument((*p).c_str());
		if (document) {
			LOG(DEBUG, "loaded GUI document '%s'", path.c_str());
			return document;
		}
	}
	LOG(ERROR, "unable to load GUI document '%s'", path.c_str());
	return NULL;
}
