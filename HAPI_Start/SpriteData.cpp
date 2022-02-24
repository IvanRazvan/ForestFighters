#include "SpriteData.h"

// This constructor sets the sprite data and reads the frames from a file
SpriteData::SpriteData(string filename, bool transparancy, int frames, float duration)
	: m_transparancy(transparancy), m_filename(filename), m_duration(duration)
{
	string format = ".png";
	string filepath = spriteMainFilePath + filename + "\\" + filename;

	m_frames.clear();
	for (int i = 0; i < frames; i++)
	{
		m_frames.push_back(nullptr);
		if (!HAPI.LoadTexture(filepath + to_string(i) + format, &m_frames.at(i), m_boundingBox.right, m_boundingBox.bottom))
		{
			HAPI.UserMessage("Missing file: " + filepath + to_string(i) + format, "Animation Error");
			HAPI.Close();
		}
	}

}

// This destructor clears the frames vector
SpriteData::~SpriteData()
{
	for (BYTE* frame : m_frames)
		delete frame;
	m_frames.clear();
}

// This function returns the name of the sprite
string SpriteData::GetName() const
{
	return m_filename;
}

// This function returns the current frame depending on framerate and animation counter
int SpriteData::CurrentFrame(int counter, int framerate) const
{
	return (counter * m_frames.size()) / (m_duration * framerate);
}

// This function returns true if the animation ended
bool SpriteData::AnimationEnd(int counter, int framerate) const
{
	return CurrentFrame(counter, framerate) >= m_frames.size();
}

// This function returns the proper frame depending on framerate and animation counter
BYTE* SpriteData::GetFrameStart(int framerate, int& counter) const
{
	if (m_frames.size() == 1 || counter < 0)
		return m_frames.at(0);

	counter++;

	if (AnimationEnd(counter, framerate))
	{
		counter = 0;
		return m_frames.at(counter);
	}
	else
		return m_frames.at(CurrentFrame(counter, framerate));
}

// This function returns the number of frames
int SpriteData::GetNumberOfFrames() const
{
	return m_frames.size();
}

// This function returns the bounding box of the sprite
BoundingBox SpriteData::GetBoundingBox() const
{
	return m_boundingBox;
}

// This function returns the width of the sprite
int SpriteData::GetWidth() const
{
	return m_boundingBox.GetWidth();
}

// This function returns the height of the sprite
int SpriteData::GetHeight() const
{
	return m_boundingBox.GetHeight();
}

// This function returns the duration of the animation
float SpriteData::GetDuration() const
{
	return m_duration;
}

// This function returns true if the sprite has transparancy
bool SpriteData::GetTransparency() const
{
	return m_transparancy;
}


