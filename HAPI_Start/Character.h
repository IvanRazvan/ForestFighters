#pragma once

#include "DynamicObject.h"

class CharacterLibrary;
class CharacterData;
class ProgressBar;
class Projectile;

/*
    Character expands the DynamicObject by implementing behaviour for character entity.
*/

class Character :
    public DynamicObject
{
protected:
    float m_health{ 0 };
    int m_maxhealth{ 0 };
    CharacterData* m_data{ nullptr };

    std::shared_ptr<ProgressBar> m_healthBar;

    vector< std::shared_ptr <Projectile> > m_projectiles;
public:
    Character() = default;
    Character(Simulation* simulation, string name, CharacterLibrary* characterLibrary, SpriteLibrary* spriteLibrary, Vector2 position);

    E_ObjectType GetType() const override;

    void Heal(float amount);
    void TakeDamage(int amount) override;

    void Reset() override;

    void FireBullet(Vector2 target);

    void Render(float t) override;
};

