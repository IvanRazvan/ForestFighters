#pragma once

#include "Defines.h"

/*
	CharacterData class holds information regarding a character.
*/

class CharacterData
{
private:
	string m_tag{ "" };
	string m_characterName{ "" }, m_characterAnimationFile{ "" }, m_projectileAnimationFile{ "" }, m_projectileExplosionFile{ "" };
	int characterHealth{ 0 }, characterDamage{ 0 }, characterMovementSpeed{ 0 };
	float  characterHealthRegen{ 0 };
	int projectileAmount{ 0 }, projectileMovementSpeed{ 0 }, projectileRange{ 0 };
public:
	CharacterData() = default;
	CharacterData(string charactername);

	string GetTag() const;
	string GetName() const;
	string GetCharacterAnimationFileName() const;
	string GetProjectileAnimationFileName() const;
	string GetProjectileExplosionFileName() const;
	int GetCharacterHealth() const;
	float GetCharacterHealthRegen() const;
	int GetCharacterDamage() const;
	int GetCharacterMovementSpeed() const;
	int GetProjectileAmount() const;
	int GetProjectileMovementSpeed() const;
	int GetProjectileRange() const;
};

