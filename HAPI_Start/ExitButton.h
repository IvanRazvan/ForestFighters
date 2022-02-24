#pragma once

#include "Button.h"

/*
	ExitButton expands the Button by implementing the close application functionality.
*/

class ExitButton :
    public Button
{
public:
	ExitButton() = default;
	ExitButton(Scene* scene, string name, SpriteLibrary* spriteLibrary, Vector2 position);

	void Action() override;
};

