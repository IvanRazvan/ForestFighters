#pragma once

#include "Character.h"

class SpriteLibrary;
class CharacterLibrary;
class CharacterData;
class ProgressBar;
class Projectile;

/*
    E_AICharacterState is an enum used for the states of the AI.
*/

enum class E_AICharacterState {
    PATROL,
    CHASE,
    ATTACK,
    KITE
};

/*
    AICharacter expands the Character by implementing AI.
*/

class AICharacter :
    public Character
{
private:
    E_AICharacterState m_state{ E_AICharacterState::PATROL };
    Vector2 m_target;
    Vector2 m_wander;
    float m_movementspeed{ 0 };
    float m_attackRange{ 0 };
    float m_wanderRange{ 0 };

    bool TargetFound();
    Vector2 ComputeClosestTarget(vector<std::shared_ptr <GameObject>>& objects);
    Vector2 GetRandomSurroundingPosition(int range);

    bool ChangeState();
    void ComputeState();
    void BehaveOnState();

public:
    AICharacter() = default;
    AICharacter(Simulation* simulation, string name, CharacterLibrary* characterLibrary, SpriteLibrary* spriteLibrary, Vector2 position);

    void Update() override;
};

