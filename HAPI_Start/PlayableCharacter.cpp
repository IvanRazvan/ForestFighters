#include "PlayableCharacter.h"
#include "Simulation.h"
#include "Application.h"
#include "Projectile.h"
#include "ProgressBar.h"
#include "CharacterLibrary.h"
#include "Graphics.h"

// This constructor sets the character
PlayableCharacter::PlayableCharacter(Simulation* simulation, string name, CharacterLibrary* characterLibrary, SpriteLibrary* spriteLibrary, Vector2 position)
	: Character(simulation, name, characterLibrary, spriteLibrary, position)
{

}

// This function handles player input
void PlayableCharacter::Update()
{
	Heal(m_data->GetCharacterHealthRegen());

	m_healthBar->UpdateProgress(m_health / m_maxhealth);

	TakeStep();

	Move(m_simulation->GetPlayerMovementInput() * m_data->GetCharacterMovementSpeed(), m_simulation->GetGameObjects());

	Vector2 bulletDirection = m_simulation->GetPlayerAimInput();
	if (bulletDirection.isNull() == false)
	{
		FireBullet(bulletDirection);
	}
}

// This function renders the character and locks the camera on it
void PlayableCharacter::Render(float t)
{
	m_simulation->GetGraphics()->FocusScreen(GetCenter(t));

	GetApplication()->GetGraphics()->Render(GetVisuals(), GetPosition(t));
	GetApplication()->GetGraphics()->Render(m_healthBar.get(), GetPosition(t) + m_healthBar->GetPosition());
}
