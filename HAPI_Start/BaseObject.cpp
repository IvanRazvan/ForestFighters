#include "BaseObject.h"
#include "Scene.h"

// This function returns the scene this object exists in.
Scene* BaseObject::GetScene() const
{
    return m_scene;
}

// This function returns the application this object exists in.
Application* BaseObject::GetApplication() const
{
    return GetScene()->GetApplication();
}

// This constructor sets the scene and position
BaseObject::BaseObject(Scene* scene, Vector2 position)
    :   m_scene(scene)
{
    SetPosition(position);
    SetFuturePosition(position);
}

// This function returns the state of the object
bool BaseObject::IsActive() const
{
    return m_isActive;
}

// This function sets the state of the object
void BaseObject::SetActiveState(bool state)
{
    m_isActive = state;
}

// This function returns the position of the object
Vector2 BaseObject::GetPosition() const
{
    return m_position;
}

// This function returns the position of the object considering interpolation between steps
Vector2 BaseObject::GetPosition(float t) const
{
    return Interpolate(m_position, m_futurePosition, t);
}

// This function returns the next step's position of the object
Vector2 BaseObject::GetFuturePosition() const
{
    return m_futurePosition;
}

// This function sets the position of the object
void BaseObject::SetPosition(Vector2 position)
{
    m_position = position;
}

// This function sets the next step's position of the object
void BaseObject::SetFuturePosition(Vector2 position)
{
    m_futurePosition = position;
}

// This function moves the object to the next step's position
void BaseObject::TakeStep()
{
    m_position = m_futurePosition;
}

// This function moves the object to the next step's position while setting a new next step
void BaseObject::TakeStep(Vector2 newFuturePosition)
{
    TakeStep();
    SetFuturePosition(newFuturePosition);
}
