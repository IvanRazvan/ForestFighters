#pragma once
#include "Button.h"

/*
	E_Difficulty is an enum used to define the difficulty of the game.
*/

enum class E_Difficulty {
	EASY,
	HARD,
	ENDLESS
};

/*
	PlayButton expands the Button by implementing the push Simulation scene functionality.
*/

class PlayButton :
    public Button
{
private:
	E_Difficulty m_difficulty;

public:
	PlayButton() = default;
	PlayButton(Scene* scene, string name, SpriteLibrary* spriteLibrary, Vector2 position, E_Difficulty difficulty);

	void Action() override;
};

