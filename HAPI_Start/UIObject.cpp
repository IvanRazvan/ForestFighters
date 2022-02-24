#include "UIObject.h"
#include "Scene.h"
#include "SpriteLibrary.h"

// This constructor sets the sprite
UIObject::UIObject(string name, SpriteLibrary* spriteLibrary)
{
	SetSpriteData(name, spriteLibrary);
}

// This constructor sets the sprite
UIObject::UIObject(SpriteData* spriteData)
{
	SetSpriteData(spriteData);
}

// This function returns the sprite
SpriteData* UIObject::GetSpriteData() const
{
	return m_sprite;
}

// This function sets the sprite
void UIObject::SetSpriteData(string name, SpriteLibrary* spriteLibrary)
{
	m_sprite = spriteLibrary->GetAnimationData(name);
	m_renderedArea = m_sprite->GetBoundingBox();
}

// This function sets the sprite
void UIObject::SetSpriteData(SpriteData* spriteData)
{
	m_sprite = spriteData;
	m_renderedArea = m_sprite->GetBoundingBox();
}

// This function returns the sprite's rendered area
BoundingBox UIObject::GetRenderedArea() const
{
	return m_renderedArea;
}

// This function returns the sprite's width
int UIObject::GetWidth() const
{
	return m_sprite->GetWidth();
}

// This function sets the sprite's width
void UIObject::SetWidth(float t)
{
	if (t < 0 || t > 1)
		return;

	m_renderedArea.right = m_renderedArea.left + t * m_sprite->GetWidth();
}

// This function returns the sprite's height
int UIObject::GetHeight() const
{
	return m_sprite->GetHeight();
}

// This function sets the sprite's height
void UIObject::SetHeight(float t)
{
	if (t < 0 || t > 1)
		return;

	m_renderedArea.bottom = m_renderedArea.top + t * m_sprite->GetHeight();
}

// This function toggles the sprite animation
void UIObject::ToggleAnimation(bool state)
{
	if (state == true && m_counter == -1)
		m_counter = 0;
	else if (state == false)
		m_counter = -1;
}

// This function returns the sprite's animation counter
int& UIObject::GetCounter()
{
	return  m_counter;
}

// This function returns true if the animation will end
bool UIObject::WillFinishAnimating() const
{
	return m_sprite->AnimationEnd(m_counter + 1, targetFPS);
}

// This function updates the sprite
void UIObject::Update()
{

}
