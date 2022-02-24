#include "Graphics.h"
#include "SpriteData.h"
#include "GameObject.h"
#include "ProgressBar.h"

// This function returns the BYTE corresponding to a screen position
BYTE* Graphics::GetPixel(Vector2 screenPosition) const
{
	return m_start + ((size_t)screenPosition.y * m_screenSpace.GetWidth() + (size_t)screenPosition.x) * 4;
}

// This function returns true if a position is on screen
bool Graphics::IsOnScreen(Vector2 screenPosition) const
{
	return m_screenSpace.HoldsPosition(screenPosition);
}

// This function returns true if a sprite is on screen
bool Graphics::IsOnScreen(SpriteData* animation, Vector2 screenPosition) const
{
	return Clip(m_screenSpace, animation->GetBoundingBox()).IsValid();
}

// This function uses bounding boxes to clip and render sprites on screen
void Graphics::Render(Vector2 position, BYTE* start, BoundingBox textureBoundingBox, BoundingBox textureRenderBox, bool transparency) const
{
	BoundingBox renderedBox = Clip(m_screenSpace + m_screenPosition, Clip(textureBoundingBox, textureRenderBox) + position);
	
	if (renderedBox.IsValid() == false)
		return;
	
	BYTE* screenPtr{ GetPixel(renderedBox.GetPosition() - m_screenPosition) };
	
	renderedBox = renderedBox - position;
	BYTE* texturePtr{ start + ((size_t)textureBoundingBox.GetWidth() * renderedBox.top + renderedBox.left) * 4 };
	
	if (transparency)
	{
		int screenEndOfLineOffset{ (m_screenSpace.GetWidth() - renderedBox.GetWidth()) * 4 };
		int textureEndOfLineOffset{ (textureBoundingBox.GetWidth() - renderedBox.GetWidth()) * 4 };
		for (int i = 0; i < renderedBox.GetHeight(); i++)
		{
			for (int j = 0; j < renderedBox.GetWidth(); j++)
			{
				if (texturePtr[3] == 255)
				{
					memcpy(screenPtr, texturePtr, 4);
				}
				else if (texturePtr[3] != 0)
				{
					screenPtr[0] = texturePtr[0] * texturePtr[3] / 255 + screenPtr[0] * (255 - texturePtr[3]) / 255;
					screenPtr[1] = texturePtr[1] * texturePtr[3] / 255 + screenPtr[1] * (255 - texturePtr[3]) / 255;
					screenPtr[2] = texturePtr[2] * texturePtr[3] / 255 + screenPtr[2] * (255 - texturePtr[3]) / 255;
				}
				screenPtr += 4;
				texturePtr += 4;
			}

			texturePtr += textureEndOfLineOffset;
			screenPtr += screenEndOfLineOffset;
		}
	}
	else
	{
		if (renderedBox.GetWidth() > 0)
		{
			int screenLine{ m_screenSpace.GetWidth() * 4 };
			int textureLine{ textureBoundingBox.GetWidth() * 4 };

			for (int i = 0; i < renderedBox.GetHeight(); i++)
			{
				memcpy(screenPtr, texturePtr, (size_t)renderedBox.GetWidth() * 4);
				texturePtr += textureLine;
				screenPtr += screenLine;
			}
		}
	}
}

// This constructor sets the window
Graphics::Graphics(int W, int H, string name)
{
	if (!HAPI.Initialise(W, H, name))
	{
		HAPI.UserMessage("Could not open window.", "Window Error");
		HAPI.Close();
	}

	HAPI.SetShowFPS(true);
	HAPI.LimitFrameRate(targetFPS);
	m_start = HAPI.GetScreenPointer();

	m_screenSpace = BoundingBox(W, H);

	m_screenSize = m_screenSpace.Size() * 4;
}

// This function returns the camera position
Vector2 Graphics::GetScreenPosition() const
{
	return m_screenPosition;
}

// This function locks the camera on a position
void Graphics::FocusScreen(Vector2 position)
{
	m_screenPosition = position - Vector2(screenWidth / 2, screenHeight / 2);
}

// This function moves the camera back to origin
void Graphics::ResetScreen()
{
	m_screenPosition = Vector2();
}

// This function clears the screen
void Graphics::ClearScreen() const
{
	memset(m_start, 0, m_screenSize);
}

// This function clears the screen to a colour
void Graphics::ClearScreen(const HAPI_TColour colour) const
{
	for (size_t i = 0; i < m_screenSize; i += 4)
		memcpy(m_start + i, &colour, 4);
}

// This function sorts the vector by the Y position
void Graphics::SortRenderingQueue(vector< std::shared_ptr <GameObject> >& gameObjects) const
{
	for (size_t i = 0; i < gameObjects.size() - 1; i++)
	{
		for (size_t j = 0; j < gameObjects.size() - i - 1; j++)
		{
			if (gameObjects.at(j)->GetPosition().y + gameObjects.at(j)->GetVisuals()->GetHeight() > gameObjects.at(j + 1)->GetPosition().y + gameObjects.at(j + 1)->GetVisuals()->GetHeight())
			{
				std::shared_ptr<GameObject> aux = gameObjects.at(j);
				gameObjects.at(j) = gameObjects.at(j + 1);
				gameObjects.at(j + 1) = aux;
			}
		}
	}
}

// This function renders a sprite on the screen, disregarding screen position
void Graphics::RenderStatic(UIObject* sprite, Vector2 position) const
{
	Render(position + m_screenPosition, sprite->GetSpriteData()->GetFrameStart(targetFPS, sprite->GetCounter()), sprite->GetSpriteData()->GetBoundingBox(), sprite->GetRenderedArea(), sprite->GetSpriteData()->GetTransparency());
}

// This function renders a sprite on the screen
void Graphics::Render(UIObject* sprite, Vector2 position) const
{
	Render(position, sprite->GetSpriteData()->GetFrameStart(targetFPS, sprite->GetCounter()), sprite->GetSpriteData()->GetBoundingBox(), sprite->GetRenderedArea(), sprite->GetSpriteData()->GetTransparency());
}

// This function renders a progress bas on the screen, disregarding screen position
void Graphics::RenderStatic(ProgressBar* progressBar, Vector2 position) const
{
	RenderStatic(progressBar->GetBorder(), position);
	RenderStatic(progressBar->GetProgress(), position + progressBar->GetProgressPosition());
}

// This function renders a progress bas on the screen
void Graphics::Render(ProgressBar* progressBar, Vector2 position) const
{
	Render(progressBar->GetBorder(), position);
	Render(progressBar->GetProgress(), position + progressBar->GetProgressPosition());
}