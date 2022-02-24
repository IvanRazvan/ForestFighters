#pragma once

#include "Defines.h"
#include "Vector2.h"

class SpriteLibrary;
class UIObject;

/*
	ProgressBar class implements the behaviour of a progress bar
*/

class ProgressBar
{
private:
	Vector2 m_position;
	Vector2 m_progressPosition;

	std::shared_ptr<UIObject> m_progress;
	std::shared_ptr<UIObject> m_border;

public:
	ProgressBar() = default;
	ProgressBar(string name, SpriteLibrary* spriteLibrary, Vector2 position);
	ProgressBar(string name, SpriteLibrary* spriteLibrary, Vector2 position, Vector2 progressPosition);

	UIObject* GetProgress() const;
	UIObject* GetBorder() const;

	void SetPosition(Vector2 position);
	Vector2 GetPosition() const;
	Vector2 GetProgressPosition() const;

	void UpdateProgress(float t);
};

