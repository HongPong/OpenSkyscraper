#include <cassert>
#include <Rml/Core/Element.h>
#include "Game.h"
#include "ToolboxWindow.h"

using namespace OT;


void ToolboxWindow::close()
{
	buttons.clear();
	
	if (window) {
		window->RemoveReference();
		window->Close();
	}
	window = NULL;
}

void ToolboxWindow::reload()
{
	close();
	
	window = game->gui.loadDocument("toolbox.rml");
	assert(window);
	window->Show();
	
	Rml::Core::ElementList tmp;
	window->GetElementsByTagName(tmp, "button");
	for (int i = 0; i < tmp.size(); i++) {
		tmp[i]->AddEventListener("click", this);
		if (tmp[i]->IsClassSet("tool")) buttons.insert(tmp[i]);
	}
	
	//Add the item buttons.
	for (int i = 0; i < game->itemFactory.prototypes.size(); i++) {
		Item::AbstractPrototype * prototype = game->itemFactory.prototypes[i];
		
		char id[128];
		snprintf(id, 128, "item-%s", prototype->id.c_str());
		
		char style[512];
		snprintf(style, 512, "button#%s { background-image-s: %ipx %ipx; }", id, prototype->icon*32, prototype->icon*32+32);
		LOG(DEBUG, "style for %s: %s", prototype->name.c_str(), style);
		
		Rml::Core::StyleSheet * sheet = Rml::Core::Factory::InstanceStyleSheetString(style);
		assert(sheet && "unable to instantiate stylesheet");
		window->SetStyleSheet(window->GetStyleSheet()->CombineStyleSheet(sheet));
		sheet->RemoveReference();
		
		Rml::Core::XMLAttributes attributes;
		attributes.Set("class", "item");
		attributes.Set("id", id);
		
		Rml::Core::Element * button = Rml::Core::Factory::InstanceElement(NULL, "button", "button", attributes);
		assert(button && "unable to instantiate button");
		
		button->AddEventListener("click", this);
		window->AppendChild(button);
		buttons.insert(button);
		
		button->RemoveReference();
	}
	
	updateSpeed();
	updateTool();
}

void ToolboxWindow::ProcessEvent(Rml::Core::Event & event)
{
	LOG(DEBUG, "%s received", event.GetType().CString());
	Rml::Core::Element * element = event.GetCurrentElement();
	if (buttons.count(element)) {
		game->selectTool(element->GetId().CString());
		event.StopPropagation();
	} else if (element->IsClassSet("speed")) {
		int speed;
		sscanf(element->GetId().CString(), "speed%i", &speed);
		game->setSpeedMode(speed);
		event.StopPropagation();
	}
}

void ToolboxWindow::updateSpeed()
{
	for (int i = 0; i < 4; i++) {
		char c[32];
		snprintf(c, 32, "speed%i", i);
		Rml::Core::Element * button = window->GetElementById(c);
		assert(button);
		button->SetClass("selected", game->speedMode == i);
	}
}

void ToolboxWindow::updateTool()
{
	for (ElementSet::iterator b = buttons.begin(); b != buttons.end(); b++) {
		(*b)->SetClass("selected", (*b)->GetId() == game->selectedTool.c_str());
	}
}
