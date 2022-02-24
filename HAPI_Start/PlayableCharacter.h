#pragma once

#include "Character.h"

class CharacterLibrary;
class CharacterData;
class ProgressBar;
class Projectile;

/*
    PlayableCharacter expands the Character by implementing player input.
*/

class PlayableCharacter :
    public Character
{
public:
    PlayableCharacter() = default;
    PlayableCharacter(Simulation * simulation, string name, CharacterLibrary * characterLibrary, SpriteLibrary * spriteLibrary, Vector2 position);

    void Update() override;
    void Render(float t) override;
};

