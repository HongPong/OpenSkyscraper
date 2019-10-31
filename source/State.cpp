#include <Rml/Debugger.h>
#include "State.h"
#include "Application.h"

using namespace OT;


State::State(std::string name) : gui(name, &App->gui)
{
	active = false;
}

void State::activate()
{
	active = true;
#ifdef BUILD_DEBUG
	Rml::Debugger::SetContext(gui.context);
#endif
}

void State::deactivate()
{
	active = false;
}
