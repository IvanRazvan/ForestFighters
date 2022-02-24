#include "CharacterData.h"

// This constructor reads the information from the specified file
CharacterData::CharacterData(string charactername)
	:	m_characterName(charactername)
{
	string filepath = characterStatsMainFilePath + charactername + ".txt";
	ifstream in(filepath);

	if (!in.is_open())
	{
		HAPI.UserMessage("No stats found: " + filepath, "Character Stats Error");
		HAPI.Close();
	}
	else
	{
		string text;

		in >> text >> m_tag
		   >> text >> m_characterAnimationFile
		   >> text >> characterHealth
		   >> text >> characterHealthRegen
		   >> text >> characterDamage
		   >> text >> characterMovementSpeed
		   >> text >> m_projectileAnimationFile
		   >> text >> m_projectileExplosionFile
		   >> text >> projectileAmount
		   >> text >> projectileMovementSpeed
		   >> text >> projectileRange;
	}

	in.close();
}

// This function returns the tag
string CharacterData::GetTag() const
{
	return m_tag;
}

// This function returns the name
string CharacterData::GetName() const
{
	return m_characterName;
}

// This function returns the character animation file name
string CharacterData::GetCharacterAnimationFileName() const
{
	return m_characterAnimationFile;
}

// This function returns the projectile animation file name
string CharacterData::GetProjectileAnimationFileName() const
{
	return  m_projectileAnimationFile;
}

// This function returns the projectile explosion file name
string CharacterData::GetProjectileExplosionFileName() const
{
	return m_projectileExplosionFile;
}

// This function returns the character max health
int CharacterData::GetCharacterHealth() const
{
	return characterHealth;
}

// This function returns the character health regen
float CharacterData::GetCharacterHealthRegen() const
{
	return characterHealthRegen;
}

// This function returns the character damage
int CharacterData::GetCharacterDamage() const
{
	return characterDamage;
}

// This function returns the character movement speed
int CharacterData::GetCharacterMovementSpeed() const
{
	return characterMovementSpeed;
}

// This function returns the projectile pool size
int CharacterData::GetProjectileAmount() const
{
	return projectileAmount;
}

// This function returns the projectile movement speed
int CharacterData::GetProjectileMovementSpeed() const
{
	return projectileMovementSpeed;
}

// This function returns the projectile range
int CharacterData::GetProjectileRange() const
{
	return projectileRange;
}
