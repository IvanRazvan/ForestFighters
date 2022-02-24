#include "BackButton.h"
#include "Scene.h"
#include "Application.h"
#include "SoundManager.h"

// This constructor sets the position and visuals of the button.
BackButton::BackButton(Scene* scene, string name, SpriteLibrary* spriteLibrary, Vector2 position)
	:	Button(scene, name, spriteLibrary, position)
{

}

// This function pops the current scene on the stack
void BackButton::Action()
{
	GetApplication()->RequestPopScene();
	GetApplication()->GetSound()->Play("click");
}
