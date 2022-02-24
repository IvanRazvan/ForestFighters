#include "Simulation.h"
#include "Button.h"
#include "Application.h"
#include "Graphics.h"

// This constructor sets the position and visuals of the button.
Button::Button(Scene* scene, string name, SpriteLibrary* spriteLibrary, Vector2 position)
	:	BaseObject(scene, position)
{
	m_visuals = std::make_shared<UIObject>(name, spriteLibrary);
}

// This function returns true if the mouse is on top of the button
bool Button::isMouseHover(Vector2 mousePosition)  const
{
	return mousePosition.x >= GetPosition().x
		&& mousePosition.x <= GetPosition().x + m_visuals->GetWidth()
		&& mousePosition.y >= GetPosition().y
		&& mousePosition.y <= GetPosition().y + m_visuals->GetHeight();
}

// This function returns the position relative to the screen
Vector2 Button::GetScreenPosition() const
{
	return GetScene()->GetMousePosition() - GetApplication()->GetGraphics()->GetScreenPosition();
}

// This function handles the button click
void Button::Update()
{
	if (isMouseHover(GetScreenPosition()) && GetScene()->IsClicking())
		Action();
}

// This function handles the button rendering
void Button::Render(float t)
{
	GetApplication()->GetGraphics()->RenderStatic(m_visuals.get(), GetPosition());
}
