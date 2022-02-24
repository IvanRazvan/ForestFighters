#include "Scene.h"
#include "Application.h"
#include "SpriteLibrary.h"
#include "Graphics.h"
#include "Input.h"

// This constructor sets the scene
Scene::Scene(Application* application)
	:	m_application(application)
{
	m_SpriteLibrary = std::make_shared <SpriteLibrary>();
}

// This function returns the application
Application* Scene::GetApplication()
{
	return m_application;
}

// This function returns the graphics system
Graphics* Scene::GetGraphics() const
{
	return m_application->GetGraphics();
}

// This function returns the input system
Input* Scene::GetInput() const
{
	return m_application->GetInput();
}

// This function returns the mouse screen position
Vector2 Scene::GetMousePosition() const
{
	return GetInput()->GetMousePosition(GetGraphics()->GetScreenPosition());
}

// This function returns the relative player aim 
Vector2 Scene::GetPlayerAimInput() const
{
	return GetInput()->GetPlayerAimInput(GetGraphics()->GetScreenPosition());
}

// This function returns the player movement 
Vector2 Scene::GetPlayerMovementInput() const
{
	return GetInput()->GetPlayerMovementInput();
}

// This function returns true if the player is clicking
bool Scene::IsClicking()
{
	return GetInput()->IsClickingMouse();
}
