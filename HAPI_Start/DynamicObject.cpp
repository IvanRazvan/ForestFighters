#include "DynamicObject.h"
#include "Simulation.h"

// This constructor sets the object
DynamicObject::DynamicObject(Simulation* scene, Vector2 position)
	:	GameObject(scene, position)
{
}

// This function returns true if a collision with the other object will happen on the next step
bool DynamicObject::willCollide(const std::shared_ptr <GameObject> other) const
{
	return Clip(GetHitBox() + GetFuturePosition(), other->GetHitBox() + other->GetFuturePosition()).IsValid();
}

// This function returns true if a collision with the other object is happening on the current step
bool DynamicObject::isColliding(const std::shared_ptr <GameObject> other) const
{
	return Clip(GetHitBox(), other->GetHitBox()).IsValid();
}

// This virtual function handles the collision event
void DynamicObject::OnCollision(std::shared_ptr<GameObject> other)
{

}

// This function moves the object ignoring collisions
void DynamicObject::Move(Vector2 direction)
{
	// It toggles the animation
	if (direction.isNull())
	{
		GetVisuals()->ToggleAnimation(false);
		return;
	}
	else
		GetVisuals()->ToggleAnimation(true);

	if(m_simulation->IsInBoundaries(GetPosition() + direction) || m_ignoreBoundings)
		SetFuturePosition(GetPosition() + direction);
}

// This function moves the object accounting collisions
void DynamicObject::Move(Vector2 direction, const vector<std::shared_ptr <GameObject>>& Objects)
{
	// It toggles the animation
	if (direction.isNull())
	{
		GetVisuals()->ToggleAnimation(false);
		return;
	}
	else
		GetVisuals()->ToggleAnimation(true);

	if (m_ignoreBoundings || m_simulation->IsInBoundaries(GetPosition() + direction))
	{
		SetFuturePosition(GetPosition() + direction);

		// It checks possible collisions with active CHARACTER objects from other teams
		for (std::shared_ptr<GameObject> object : Objects)
		{
			if (object->IsActive() == false)
				continue;
			if (object->GetType() != E_ObjectType::CHARACTER)
				continue;
			if (GetTag() == object->GetTag())
				continue;

			if (willCollide(object))
			{
				OnCollision(object);
				break;
			}
		}
	}
}
