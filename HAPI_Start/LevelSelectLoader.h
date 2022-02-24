#pragma once

#include "Button.h"

/*
	LevelSelectLoader expands the Button by implementing the push LevelSelect scene functionality.
*/

class LevelSelectLoader :
    public Button
{
public:
	LevelSelectLoader() = default;
	LevelSelectLoader(Scene * scene, string name, SpriteLibrary * spriteLibrary, Vector2 position);

	void Action() override;
};

