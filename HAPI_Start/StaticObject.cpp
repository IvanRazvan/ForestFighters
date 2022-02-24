#include "StaticObject.h"
#include "Application.h"
#include "Graphics.h"

// This constructor sets the object
StaticObject::StaticObject(Simulation* simulation, string name, SpriteLibrary* spriteLibrary, Vector2 position)
	:	GameObject(simulation, position)
{
	SetVisuals(name, spriteLibrary);
}

// This function returns the OBSTACLE type
E_ObjectType StaticObject::GetType() const
{
	return E_ObjectType::OBSTACLE;
}

// This function implements no functionality
void StaticObject::Update()
{

}

// This function renders the object
void StaticObject::Render(float t)
{
	GetApplication()->GetGraphics()->Render(GetVisuals(), GetPosition());
}
