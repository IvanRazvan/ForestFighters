#pragma once

#include "BaseObject.h"
#include "UIObject.h"

/*
	Button expands the BaseObject by implementing UI button functionality.
*/

class Button :
	public BaseObject
{
private:
	std::shared_ptr<UIObject> m_visuals;

protected:
	bool isMouseHover(Vector2 mousePosition) const;
	Vector2 GetScreenPosition() const;

public:
	Button() = default;
	Button(Scene* scene, string name, SpriteLibrary* spriteLibrary, Vector2 position);

	virtual void Action() = 0;

	void Update() override;
	void Render(float t) override;
};

