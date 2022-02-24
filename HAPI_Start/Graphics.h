#pragma once

#include "Defines.h"
#include "BoundingBox.h"

class SpriteData;
class GameObject;
class UIObject;
class ProgressBar;

/*
	Graphics class handles rendering on the screen.
*/

class Graphics
{
private:
	Vector2 m_screenPosition;
	BoundingBox m_screenSpace;
	
	int m_screenSize{ 0 };
	BYTE* m_start{ nullptr };

	BYTE* GetPixel(Vector2 position) const;
	bool IsOnScreen(Vector2 position) const;
	bool IsOnScreen(SpriteData* animation, Vector2 position) const;

	void Render(Vector2 position, BYTE* start, BoundingBox textureBoundingBox, BoundingBox textureRenderBox, bool transparency) const;

public:
	Graphics() = default;
	Graphics(int width, int height, string name);
	
	Vector2 GetScreenPosition() const;
	void FocusScreen(Vector2 position);
	void ResetScreen();

	void ClearScreen() const;
	void ClearScreen(const HAPI_TColour colour) const;

	void SortRenderingQueue(vector< std::shared_ptr <GameObject> >& gameObjects) const;

	void RenderStatic(UIObject* sprite, Vector2 position) const;
	void Render(UIObject* sprite, Vector2 position)  const;

	void RenderStatic(ProgressBar* progressBar, Vector2 position) const;
	void Render(ProgressBar* progressBar, Vector2 position) const;
};



