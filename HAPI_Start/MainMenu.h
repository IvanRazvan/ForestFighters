#pragma once

#include "Scene.h"

class UIObject;

/*
	MainMenu is a Scene that handles the main menu.
*/

class MainMenu :
    public Scene
{
private:
	std::shared_ptr<UIObject> m_Background;

public:
	MainMenu(Application* application);

	void SetSprites() override;
	void Init() override;
	void Update() override;
	void Render(float t) override;
};

