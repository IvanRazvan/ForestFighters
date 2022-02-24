#pragma once

#include "SpriteData.h"

/*
	SpriteLibrary class uses an unordered map to store data of all sprites.
*/

class SpriteLibrary
{
private:
	unordered_map<string, std::shared_ptr <SpriteData>> m_sprites;

public:
	void AddEntry(string filename, bool transparancy, int frames = 1 , float duration = 1.0f);
	SpriteData* GetAnimationData(string filename) const;
};

