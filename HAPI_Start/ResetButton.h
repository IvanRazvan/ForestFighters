#pragma once

#include "Button.h"

/*
	ResetButton expands the Button by implementing the reset scene functionality.
*/

class ResetButton :
    public Button
{
public:
	ResetButton() = default;
	ResetButton(Scene * scene, string name, SpriteLibrary * spriteLibrary, Vector2 position);

	void Action() override;
};
