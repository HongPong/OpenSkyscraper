#include "TimeWindowWatch.h"
#include <Rml/Core/Geometry.h>
#include "OpenGL.h"
#include <cmath>

using namespace OT;
using namespace Rocket::Core;


void TimeWindowWatch::RenderElement(Rml::Core::Element* element, Rml::Core::DecoratorDataHandle element_data)
{
	/*Rml::Core::Geometry * geometry = new Rml::Core::Geometry;

	std::vector<Rml::Core::Vertex> & vertices = geometry->GetVertices();
	std::vector<int> & indices = geometry->GetIndices();

	Rml::Core::Vertex vertex;
	vertex.colour = Rml::Core::Colourb(0, 0, 0);

	vertex.position = Vector2f(0, 0);
	vertices.insert(vertex);
	vertex.position = Vector2f(0, 20);
	vertices.insert(vertex);
	vertex.position = Vector2f(12, 0);
	vertices.insert(vertex);

	indices.insert(0);
	indices.insert(1);

	geometry->render(Rml::Core::Vector2f());*/

	Vector2f offset = element->GetAbsoluteOffset();
	Vector2f size   = element->GetBox().GetSize() / 2;

	double radius_m = std::min<float>(size.x, size.y);
	double radius_h = 0.6 * radius_m;

	double time    = element->GetAttribute<float>("time", 0);
	double angle_h = 2 * M_PI * time/12;
	double angle_m = 2 * M_PI * time;

	glPushMatrix();
	glTranslatef(offset.x + size.x, offset.y + size.y, 0);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(radius_h * sin(angle_h), -radius_h * cos(angle_h));
	glVertex2f(0, 0);
	glVertex2f(radius_m * sin(angle_m), -radius_m * cos(angle_m));
	glEnd();
	glPopMatrix();
}
