#pragma once

#include "Defines.h"
#include "BoundingBox.h"

/*
	SpriteData class holds information regarding a sprite.
*/

class SpriteData {
private:
	string m_filename{ "" };
	vector<BYTE*> m_frames{ nullptr };
	BoundingBox m_boundingBox;
	float m_duration{ 0 };
	bool m_transparancy{ false };

public:
	SpriteData() = default;
	SpriteData(string filename, bool transparancy, int frames , float duration);
	~SpriteData();

	string GetName() const;
	int CurrentFrame(int counter, int framerate) const;
	bool AnimationEnd(int counter, int framerate) const;
	BYTE* GetFrameStart(int framerate, int& counter) const;
	int GetNumberOfFrames() const;
	BoundingBox GetBoundingBox() const;
	int GetWidth() const;
	int GetHeight() const;
	float GetDuration() const;
	bool GetTransparency() const;
};

