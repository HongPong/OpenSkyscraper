#pragma once
#include <Rml/Core/Decorator.h>
#include <Rml/Core/DecoratorInstancer.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace OT {
	
	class TimeWindowWatch : public Rml::Core::Decorator
	{
	public:
		virtual Rml::Core::DecoratorDataHandle GenerateElementData(Rml::Core::Element* element) { return 0; };
		virtual void ReleaseElementData(Rml::Core::DecoratorDataHandle element_data) {};
		virtual void RenderElement(Rml::Core::Element* element, Rml::Core::DecoratorDataHandle element_data);
	};
	
	class TimeWindowWatchInstancer : public Rml::Core::DecoratorInstancer
	{
	public:
		virtual Rml::Core::Decorator* InstanceDecorator(const Rml::Core::String& name, const Rml::Core::PropertyDictionary& properties) {
			return new TimeWindowWatch();
		}
		virtual void ReleaseDecorator(Rml::Core::Decorator* decorator) { delete decorator; }
		virtual void Release() { delete this; }
	};
}
