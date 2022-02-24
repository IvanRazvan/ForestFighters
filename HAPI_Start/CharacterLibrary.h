#pragma once

#include "CharacterData.h"

/*
	CharacterLibrary class uses an unordered map to store data of all characters.
*/

class CharacterLibrary
{
private:
	unordered_map<string, std::shared_ptr<CharacterData> > m_characters;

public:
	void AddEntry(string charactername);
	CharacterData* GetCharacterData(string charactername) const;
};

