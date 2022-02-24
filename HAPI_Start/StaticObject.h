#pragma once

#include "GameObject.h"

/*
    StaticObject expands the GameObject by implementing behaviour for stationary objects.
*/

class StaticObject :
    public GameObject
{
private:

public:
    StaticObject() = default;
    StaticObject(Simulation* simulation, string name, SpriteLibrary* spriteLibrary, Vector2 position = Vector2(0, 0));

    E_ObjectType GetType() const override;

    void Update() override;
    void Render(float t) override;
};