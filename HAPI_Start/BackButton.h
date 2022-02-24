#pragma once

#include "Button.h"

/*
	BackButton expands the Button by implementing the scene pop functionality.
*/

class BackButton :
    public Button
{
public:
	BackButton() = default;
	BackButton(Scene* scene, string name, SpriteLibrary* spriteLibrary, Vector2 position);

	void Action() override;
};

