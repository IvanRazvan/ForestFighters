#pragma once

#include "DynamicObject.h"

class CharacterData;

/*
    Projectile expands the DynamicObject by implementing behaviour for bullets.
*/

class Projectile :
    public DynamicObject
{
private:
    bool m_isAlive{ false };

    int m_damage{ 0 }, m_movementSpeed{ 0 }, m_range{ 0 };
    Vector2 m_direction{ 0,0 };
    Vector2 m_firedPosition{ 0,0 };

    shared_ptr<UIObject> m_explosion;

public:
    Projectile() = default;
    Projectile(Simulation* simulation, CharacterData* characterData, SpriteData* animationData, SpriteData* explosionData, Vector2 position);

    E_ObjectType GetType() const override;

    void TurnActive(Vector2 position, Vector2 direction);

    void Update() override;
    void OnCollision(std::shared_ptr <GameObject> other) override;

    void Render(float t) override;
};

