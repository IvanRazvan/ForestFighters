#include "SoundManager.h"

// This function loads a sound file
void SoundManager::Load(const std::string& filename)
{
	string format = ".wav";
	string filepath = soundMainFilePath + filename + "\\" + filename + format;

	if (!HAPI.LoadSound(filepath))
	{
		HAPI.UserMessage("Missing file: " + filepath, "Sound Error");
		HAPI.Close();
	}
}

// This function plays a sound file
void SoundManager::Play(const std::string& filename, bool largeSize)
{
	string format = ".wav";
	string filepath = soundMainFilePath + filename + "\\" + filename + format;
	
	HAPI_TSoundOptions options;
	options.loop = false;
	options.volume = 0.3f;

	if (largeSize)
	{
		if (!HAPI.PlayStreamedMedia(filepath))
		{
			HAPI.UserMessage("Not Loaded: " + filepath, "Sound Error");
			HAPI.Close();
		}
	}
	else
	{
		if (!HAPI.PlaySound(filepath, options))
		{
			HAPI.UserMessage("Not Loaded: " + filepath, "Sound Error");
			HAPI.Close();
		}
	}
}

// This function plays a looping sound by saving its ID in a map
void SoundManager::PlayLoop(const std::string& filename, bool largeSize)
{
	string format = ".wav";
	string filepath = soundMainFilePath + filename + "\\" + filename + format;

	if (m_soundID.find(filename) == m_soundID.end())
		m_soundID.emplace(filename, m_soundID.size());

	HAPI_TSoundOptions options;
	options.loop = true;
	options.volume = 0.3f;

	if (largeSize)
	{
		if (!HAPI.PlayStreamedMedia(filepath, options, m_soundID.find(filename)->second))
		{
			HAPI.UserMessage("Not Loaded: " + filepath, "Sound Error");
			HAPI.Close();
		}
	}
	else
	{
		if (!HAPI.PlaySound(filepath, options, m_soundID.find(filename)->second))
		{
			HAPI.UserMessage("Not Loaded: " + filepath, "Sound Error");
			HAPI.Close();
		}
	}
}
