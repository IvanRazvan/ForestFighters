#include "Character.h"
#include "Simulation.h"
#include "Application.h"
#include "CharacterLibrary.h"
#include "ProgressBar.h"
#include "Projectile.h"
#include "SoundManager.h"
#include "Graphics.h"
#include "SpriteLibrary.h"

// This constructor sets the character
Character::Character(Simulation* simulation, string name, CharacterLibrary* characterLibrary, SpriteLibrary* spriteLibrary, Vector2 position)
	: DynamicObject(simulation, position)
{
	// It sets the character stats
	m_data = characterLibrary->GetCharacterData(name);
	SetVisuals(m_data->GetCharacterAnimationFileName(), spriteLibrary);
	m_tag = m_data->GetTag();

	m_maxhealth = m_data->GetCharacterHealth();
	m_health = m_maxhealth;

	m_healthBar = std::make_shared<ProgressBar>("Progress", spriteLibrary, Vector2());
	m_healthBar->SetPosition(Vector2((GetVisuals()->GetWidth() - m_healthBar->GetBorder()->GetWidth()) / 2, -m_healthBar->GetBorder()->GetHeight()));

	// It sets the bullet pool
	for (int i = 0; i < m_data->GetProjectileAmount(); i++)
	{
		m_projectiles.emplace_back(std::make_shared <Projectile>(simulation,
																m_data,
																spriteLibrary->GetAnimationData(m_data->GetProjectileAnimationFileName()),
																spriteLibrary->GetAnimationData(m_data->GetProjectileExplosionFileName()),
																Vector2()));
		m_simulation->GetGameObjects().emplace_back(m_projectiles.at(i));
	}
}

// This function returns the CHARACTER type
E_ObjectType Character::GetType() const
{
	return E_ObjectType::CHARACTER;
}

// This function heals the character by an amount
void Character::Heal(float amount)
{
	m_health += amount;

	if (m_health > m_maxhealth)
		m_health = m_maxhealth;
}

// This function damages the character by an amount
void Character::TakeDamage(int amount)
{
	m_health -= amount;

	// If it is close enough to the player, plays a sound
	if (Distance(GetPosition(), m_simulation->GetPlayerPosition()) < 800)
		GetApplication()->GetSound()->Play("hit");

	if (m_health <= 0)
	{
		SetActiveState(false);

		// If it is close enough to the player, plays a sound
		if (Distance(GetPosition(), m_simulation->GetPlayerPosition()) < 800)
			GetApplication()->GetSound()->Play("death");
	}
}

// This function resets the character and places it on a random position
void Character::Reset()
{
	SetActiveState(true);
	m_health = m_maxhealth;

	SetPosition(m_simulation->GetRandomPosition());

	SetFuturePosition(GetPosition());
}

// This function fires a bullet in the specified direction
void Character::FireBullet(Vector2 direction)
{
	direction = direction - (GetPosition() + Vector2(GetVisuals()->GetWidth() / 2, GetVisuals()->GetHeight() / 2));
	direction.normalize();
	
	// It loops through the bullet pool to find an available bullet to use
	for (shared_ptr<Projectile> projectile : m_projectiles)
	{
		if (projectile->IsActive() == false)
		{
			projectile->TurnActive(GetPosition() + Vector2(GetVisuals()->GetWidth() / 2, GetVisuals()->GetHeight() / 2), direction);

			// If it is close enough to the player, plays a sound
			if (Distance(GetPosition(), m_simulation->GetPlayerPosition()) < 800)
				GetApplication()->GetSound()->Play("shoot");

			break;
		}
	}
}

// This function handles the rendering
void Character::Render(float t)
{
	GetApplication()->GetGraphics()->Render(GetVisuals(), GetPosition(t));
	GetApplication()->GetGraphics()->Render(m_healthBar.get(), GetPosition(t) + m_healthBar->GetPosition());
}
