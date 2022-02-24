#pragma once

#include "Defines.h"

/*
	SoundManager class handles loading and playing sounds.
*/

class SoundManager
{
private:
	unordered_map<string, int> m_soundID;

public:
	void Load(const std::string& filename);
	void Play(const std::string& filename, bool largeSize = false);
	void PlayLoop(const std::string& filename, bool largeSize = false);
};

