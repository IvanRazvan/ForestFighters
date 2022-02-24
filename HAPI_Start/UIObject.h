#pragma once

#include "Defines.h"
#include "BoundingBox.h"

class Scene;
class Application;
class SpriteLibrary;
class SpriteData;

/*
	UIObject class implements the behaviour of UI.
*/

class UIObject
{
protected:
	bool m_isActive{ true };

	SpriteData* m_sprite;
	BoundingBox m_renderedArea;
	int m_counter{ 0 };

public:
	UIObject() = default;
	UIObject(string name, SpriteLibrary* spriteLibrary);
	UIObject(SpriteData* spriteData);

	SpriteData* GetSpriteData() const;
	void SetSpriteData(string name, SpriteLibrary* spriteLibrary);
	void SetSpriteData(SpriteData* spriteData);

	int GetWidth() const;
	void SetWidth(float t);

	int GetHeight() const;
	void SetHeight(float t);

	BoundingBox GetRenderedArea() const;

	void ToggleAnimation(bool state);
	int& GetCounter();
	bool WillFinishAnimating() const;

	virtual void Update();
};

