#pragma once

#include "BaseObject.h"
#include "UIObject.h"

class Simulation;

/*
	E_ObjectType is an enum used to define the type of game objects.
*/

enum class E_ObjectType {
	OBSTACLE,
	CHARACTER,
	PROJECTILE
};

/*
	GameObject expands the BaseObject by implementing visuals and hitbox functionality.
*/

class GameObject :
	public BaseObject
{
private:
	void SetHitBox(float scale);

protected:
	Simulation* m_simulation;
	string m_tag{ "default" };

	BoundingBox m_hitBox;
	
	std::shared_ptr<UIObject> m_visuals;

	void SetVisuals(SpriteData* spriteData, float scale = 0.6f);
	void SetVisuals(string name, SpriteLibrary* spriteLibrary, float scale = 0.6f);

public:
	GameObject();
	GameObject(Simulation* scene, Vector2 position);

	virtual E_ObjectType GetType() const = 0;
	string GetTag() const;

	virtual void TakeDamage(int amount);
	virtual void Reset();

	Vector2 GetCenter(float t = 0) const;
	BoundingBox GetHitBox() const;

	UIObject* GetVisuals() const;
};

float Distance(const GameObject* G1, const GameObject* G2);

