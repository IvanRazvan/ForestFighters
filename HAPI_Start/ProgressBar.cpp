#include "ProgressBar.h"
#include "UIObject.h"

// This constructor sets the progress bar
ProgressBar::ProgressBar(string name, SpriteLibrary* spriteLibrary, Vector2 position)
{
	m_progress = std::make_shared<UIObject>(name + "_progress", spriteLibrary);
	m_border = std::make_shared<UIObject>(name + "_border", spriteLibrary);

	m_position = position;

	m_progressPosition.x = (m_border->GetWidth() - m_progress->GetWidth()) / 2;
	m_progressPosition.y = (m_border->GetHeight() - m_progress->GetHeight()) / 2;
}

// This constructor sets the progress bar
ProgressBar::ProgressBar(string name, SpriteLibrary* spriteLibrary, Vector2 position, Vector2 progressPosition)
{
	m_progress = std::make_shared<UIObject>(name + "_progress", spriteLibrary);
	m_border = std::make_shared<UIObject>(name + "_border", spriteLibrary);

	m_position = position;
	m_progressPosition = progressPosition;
}

// This function returns the progress sprite
UIObject* ProgressBar::GetProgress() const
{
	return m_progress.get();
}

// This function returns the border sprite
UIObject* ProgressBar::GetBorder() const
{
	return m_border.get();
}

// This function sets the position of the progress bar
void ProgressBar::SetPosition(Vector2 position)
{
	m_position = position;
}

// This function returns the position of the progress bar
Vector2 ProgressBar::GetPosition() const
{
	return m_position;
}

// This function returns the position of the relative progress sprite
Vector2 ProgressBar::GetProgressPosition() const
{
	return m_progressPosition;
}

// This function updates the progress sprite
void ProgressBar::UpdateProgress(float t)
{
	m_progress->SetWidth(t);
}
