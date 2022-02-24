#include "GameObject.h"
#include "Simulation.h"
#include "Application.h"
#include "SpriteData.h"
#include "SpriteLibrary.h"

// This function sets the rectangle hitbox depending on the visuals and scale
void GameObject::SetHitBox(float scale)
{
	BoundingBox sprite = m_visuals->GetSpriteData()->GetBoundingBox();
	if (scale > 1 || scale < 0)
	{
		m_hitBox = sprite;
		return;
	}

	float margin = (1.0f - scale) / 2;
	m_hitBox.left = sprite.left + margin * sprite.GetWidth();
	m_hitBox.right = sprite.right - margin * sprite.GetWidth();
	m_hitBox.top = sprite.top + margin * sprite.GetHeight();
	m_hitBox.bottom = sprite.bottom - margin * sprite.GetHeight();
}

// This function sets the visuals and its hitbox
void GameObject::SetVisuals(SpriteData* spriteData, float scale)
{
	m_visuals->SetSpriteData(spriteData);
	SetHitBox(scale);
}

// This function sets the visuals and its hitbox
void GameObject::SetVisuals(string name, SpriteLibrary* spriteLibrary, float scale)
{
	SetVisuals(spriteLibrary->GetAnimationData(name), scale);
}

// This constructor sets the visuals pointer
GameObject::GameObject()
{
	m_visuals = std::make_shared<UIObject>();
}

// This constructor sets base and the visuals pointer
GameObject::GameObject(Simulation* scene, Vector2 position)
	: BaseObject(scene, position), m_simulation(scene)
{
	m_visuals = std::make_shared<UIObject>();
}

// This function returns the tag
string GameObject::GetTag() const
{
	return m_tag;
}

// This virtual function will be implemented in Character class, but it's used to detect unwanted collisions
void GameObject::TakeDamage(int amount)
{
	HAPI.UserMessage("TakeDamage() was called on non-Character object.", "Collision Error");
	HAPI.Close();
}

// This virtual function will be implemented in Character class to reset its state
void GameObject::Reset()
{

}

// This function returns the center of the hitbox considering interpolation between steps
Vector2 GameObject::GetCenter(float t) const
{
	return GetPosition(t) + m_hitBox.GetCenter();
}

// This function returns the hitbox
BoundingBox GameObject::GetHitBox() const
{
	return m_hitBox;
}

// This function returns a pointer to the visuals
UIObject* GameObject::GetVisuals() const
{
	return m_visuals.get();
}

// This function returns the distance between 2 GameObjects
float Distance(const GameObject* G1, const GameObject* G2)
{
	return Distance(G1->GetCenter(), G2->GetCenter());
}
