#include "ResetButton.h"
#include "Scene.h"
#include "Application.h"
#include "SoundManager.h"

// This constructor sets the position and visuals of the button.
ResetButton::ResetButton(Scene* scene, string name, SpriteLibrary* spriteLibrary, Vector2 position)
	:	Button(scene, name, spriteLibrary, position)
{

}

// This function resets the current scene
void ResetButton::Action()
{
	GetScene()->Init();
	GetApplication()->GetSound()->Play("click");
}
