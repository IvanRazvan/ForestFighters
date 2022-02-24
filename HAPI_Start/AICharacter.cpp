#include "AICharacter.h"
#include "Simulation.h"
#include "Projectile.h"
#include "ProgressBar.h"
#include "CharacterLibrary.h"

// This function returns true if the AI has no target
bool AICharacter::TargetFound()
{
	return m_target.isNull() == false;
}

// This function tries to find the closest target
Vector2 AICharacter::ComputeClosestTarget(vector<std::shared_ptr <GameObject>>& objects)
{
	Vector2 target;
	float distance = m_wanderRange;

	// It loops through all objects to look for the closest enemy in wander range
	for (std::shared_ptr<GameObject> object : objects)
	{
		if (object->IsActive() == false)
			continue;
		if (object->GetType() != E_ObjectType::CHARACTER)
			continue;
		if (object->GetTag() == GetTag())
			continue;
		
		float d = Distance(this, object.get());

		if (d < distance)
		{
			target = object->GetCenter();
			distance = d;
		}
		
	}

	return target;
}

// This function returns a random surrounding position based on range and world bounds
Vector2 AICharacter::GetRandomSurroundingPosition(int range)
{
	Vector2 position;

	do {
		position = GetPosition() + Vector2((rand() % 20 - 10) * range, (rand() % 20 - 10) * range);
	} while (m_simulation->IsInBoundaries(position) == false);

	return position;
}

// This function returns true if the AI should change its state
bool AICharacter::ChangeState()
{
	m_target = ComputeClosestTarget(m_simulation->GetGameObjects());

	// If it was attacking but the target died or got out of range
	if (m_state == E_AICharacterState::ATTACK && (m_target.isNull() || Distance(GetPosition(), m_target) > m_attackRange))
		return true;

	// If it was chasing but the target died or got out of range or got in range to attack
	if (m_state == E_AICharacterState::CHASE && (m_target.isNull() || Distance(GetPosition(), m_target) > m_wanderRange) || Distance(GetPosition(), m_target) < m_attackRange)
		return true;

	// If it was patroling but it found a target or reached destination
	if (m_state == E_AICharacterState::PATROL && (m_target.isNull() == false || Distance(GetPosition(), m_wander) < 25))
		return true;

	// If it was kiting an enemy but it died or reached destination
	if (m_state == E_AICharacterState::KITE && (m_target.isNull() || Distance(GetPosition(), m_wander) < 25))
		return true;

	return false;
}

// This function computes a new state
void AICharacter::ComputeState()
{
	if (m_state == E_AICharacterState::KITE)
	{
		// Go to patrol after kiting
		if (Distance(GetPosition(), m_wander) < 25)
		{
			m_wander = GetRandomSurroundingPosition(70);
			m_state = E_AICharacterState::PATROL;
		}
	}
	else
	{
		if (TargetFound())
		{
			// If it finds a target, attack or chase
			if (Distance(GetPosition(), m_target) < m_attackRange)
				m_state = E_AICharacterState::ATTACK;
			else
				m_state = E_AICharacterState::CHASE;
		}
		else
		{
			// Else patrol
			m_wander = GetRandomSurroundingPosition(80);
			m_state = E_AICharacterState::PATROL;
		}
	}
}

// This function handles behaviour based on current state
void AICharacter::BehaveOnState()
{
	// If attacking, fire a bullet then kite
	if (m_state == E_AICharacterState::ATTACK)
	{
		FireBullet(m_target);
		m_target = Vector2();

		m_wander = GetRandomSurroundingPosition(20);
		m_state = E_AICharacterState::KITE;
	}

	// If chasing, move towards target
	if (m_state == E_AICharacterState::CHASE)
	{
		Vector2 direction = m_target - GetPosition();
		direction.normalize();
		Move(direction * m_movementspeed);
	}

	// If patroling or kiting, move towards destination
	if (m_state == E_AICharacterState::PATROL || m_state == E_AICharacterState::KITE)
	{
		Vector2 direction = m_wander - GetPosition();
		direction.normalize();
		Move(direction * m_movementspeed);
	}
}

// This constructor sets the AI character
AICharacter::AICharacter(Simulation* simulation, string name, CharacterLibrary* characterLibrary, SpriteLibrary* spriteLibrary, Vector2 position)
	: Character(simulation, name, characterLibrary, spriteLibrary, position)
{
	m_attackRange = m_data->GetProjectileRange() - (rand() % (m_data->GetProjectileRange() / 5));
	m_wanderRange = m_data->GetProjectileRange() * 1.5f;
	m_movementspeed = m_data->GetCharacterMovementSpeed();
	m_wander = GetRandomSurroundingPosition(10);
}

// This function handles the AI behaviour
void AICharacter::Update()
{
	Heal(m_data->GetCharacterHealthRegen());

	m_healthBar->UpdateProgress(m_health / m_maxhealth);

	TakeStep();

	if (ChangeState())
		ComputeState();

	BehaveOnState();
}
