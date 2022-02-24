#pragma once

#include "Defines.h"
#include "Vector2.h"

class Application;
class SpriteLibrary;
class Button;
class Graphics;
class Input;

/*
	This class is used in a stack structure inside the Application class.
	It is a pure virtual class that is used to create a scene for the application.
	Its main functions are Init, Update and Render.
*/
class Scene
{
private:
	Application* m_application;

protected:
	std::shared_ptr <SpriteLibrary> m_SpriteLibrary;
	vector< std::shared_ptr <Button> > m_Buttons;

public:
	Scene(Application* application);

	virtual void SetSprites() = 0;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render(float t) = 0;

	Application* GetApplication();
	Graphics* GetGraphics() const;
	Input* GetInput() const;

	Vector2 GetMousePosition() const;
	Vector2 GetPlayerAimInput() const;
	Vector2 GetPlayerMovementInput() const;
	bool IsClicking();
};

