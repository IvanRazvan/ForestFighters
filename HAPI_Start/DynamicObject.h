#pragma once

#include "GameObject.h"

/*
	DynamicObject expands the GameObject by implementing behaviour for moving objects.
*/

class DynamicObject :
    public GameObject
{
protected:
	bool m_ignoreBoundings{ false };

public:
	DynamicObject() = default;
	DynamicObject(Simulation* scene, Vector2 position);

	bool willCollide(const std::shared_ptr <GameObject> other) const;
	bool isColliding(const std::shared_ptr <GameObject> other) const;
	virtual void OnCollision(std::shared_ptr <GameObject> other);

	void Move(Vector2 direction);
	void Move(Vector2 direction, const vector<std::shared_ptr <GameObject>>& Objects);
};

