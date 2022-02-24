#include "CharacterLibrary.h"

// This function adds a new entry in the map
void CharacterLibrary::AddEntry(string charactername)
{
	if (m_characters.find(charactername) == m_characters.end())
		m_characters.emplace(charactername, std::make_shared <CharacterData>(charactername));
}

// This function returns an entry from the map
CharacterData* CharacterLibrary::GetCharacterData(string charactername) const
{
	if (m_characters.find(charactername) == m_characters.end())
	{
		HAPI.UserMessage("No entry found: " + charactername, "Asset Library Error");
		HAPI.Close();
		return nullptr;
	}
	else
		return m_characters.at(charactername).get();
}
