#pragma once

#include "Scene.h"

class UIObject;

/*
	LevelSelect is a Scene that handles the difficulty selection.
*/

class LevelSelect :
    public Scene
{
private:
	std::shared_ptr<UIObject> m_Background;

public:
	LevelSelect(Application* application);

	void SetSprites() override;
	void Init() override;
	void Update() override;
	void Render(float t) override;
};

