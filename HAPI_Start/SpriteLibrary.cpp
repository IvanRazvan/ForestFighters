#include "SpriteLibrary.h"

// This function adds a new entry in the map
void SpriteLibrary::AddEntry(string filename, bool transparancy, int frames, float duration)
{
	if (frames <= 0)
	{
		HAPI.UserMessage("Negative frames: " + filename, "Asset Library Error");
		HAPI.Close();
	}
	if (duration <= 0)
	{
		HAPI.UserMessage("Negative duration: " + filename, "Asset Library Error");
		HAPI.Close();
	}

	if (m_sprites.find(filename) == m_sprites.end())
		m_sprites.emplace(filename, std::make_shared <SpriteData>(filename, transparancy, frames, duration));
}

// This function returns an entry from the map
SpriteData* SpriteLibrary::GetAnimationData(string filename) const
{
	if (m_sprites.find(filename) == m_sprites.end())
	{
		HAPI.UserMessage("No entry found: " + filename, "Asset Library Error");
		HAPI.Close();
		return nullptr;
	}
	else
		return m_sprites.at(filename).get();
}


