#include "Projectile.h"
#include "Simulation.h"
#include "Application.h"
#include "CharacterData.h"
#include "Graphics.h"

// This constructor sets the projectile
Projectile::Projectile(Simulation* simulation, CharacterData* characterData, SpriteData* spriteData, SpriteData* explosionData, Vector2 position)
	: DynamicObject(simulation, position), m_damage(characterData->GetCharacterDamage()), m_movementSpeed(characterData->GetProjectileMovementSpeed()), m_range(characterData->GetProjectileRange())
{
	// It sets the bullet inactive for the object pooling
	SetActiveState(false);
	m_ignoreBoundings = true;
	m_tag = characterData->GetTag();

	SetVisuals(spriteData);
	m_explosion = make_shared<UIObject>(explosionData);
}

// This function returns the PROJECTILE type
E_ObjectType Projectile::GetType() const
{
	return E_ObjectType::PROJECTILE;
}

// This function turns the bullet active and fires it in the specified direction
void Projectile::TurnActive(Vector2 position, Vector2 direction)
{
	SetActiveState(true);
	m_isAlive = true;
	m_direction = direction;
	SetPosition(position - Vector2(GetVisuals()->GetWidth() / 2, GetVisuals()->GetHeight() / 2));
	SetFuturePosition(GetPosition());
	m_firedPosition = GetPosition();
}

// This function handles the projectile movement
void Projectile::Update()
{
	// If the bullet is not alive, it stops
	if (m_isAlive == false)
		return;

	// Moves the bullet and if it reaches max range, it gets disabled
	TakeStep();

	Move(m_direction * m_movementSpeed, m_simulation->GetGameObjects());

	if (Distance(m_firedPosition, GetPosition()) > m_range)
		SetActiveState(false);
}

// This function handles the collision event
void Projectile::OnCollision(std::shared_ptr <GameObject> other)
{
	// If the other object is a character from another team, it takes damage from the bullet
	if (other->GetType() == E_ObjectType::CHARACTER && other->GetTag() != GetTag())
	{
		m_isAlive = false;
		other->TakeDamage(m_damage);
	}
}

// This function handles the rendering
void Projectile::Render(float t)
{
	// If the bullet is alive, it gets rendered
	if (m_isAlive)
		GetApplication()->GetGraphics()->Render(GetVisuals(), GetPosition(t));
	else
	{
		// If not, it renders one instance of the exploding animation
		bool finished = m_explosion->WillFinishAnimating();
		
		GetApplication()->GetGraphics()->Render(m_explosion.get(), GetPosition());

		if (finished)
			SetActiveState(false);
	}
}
