#pragma once

#include "Defines.h"
#include "Vector2.h"

class Application;
class Scene;

/*
	BaseObject is the base class for the other Objects.
	It implements functionality regarding positions and states.
*/
class BaseObject
{
private:
	Scene* m_scene;
	bool m_isActive{ true };
	Vector2 m_position{ 0,0 };
	Vector2 m_futurePosition{ 0,0 };

protected:
	Scene* GetScene() const;
	Application* GetApplication() const;

public:
	BaseObject() = default;
	BaseObject(Scene* scene, Vector2 position);

	bool IsActive() const;
	void SetActiveState(bool state);

	Vector2 GetPosition() const;
	Vector2 GetPosition(float t) const;
	Vector2 GetFuturePosition() const;

	void SetPosition(Vector2 position);
	void SetFuturePosition(Vector2 position);

	void TakeStep();
	void TakeStep(Vector2 newFuturePosition);

	virtual void Update() = 0;
	virtual void Render(float t) = 0;
};

