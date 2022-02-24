#include "ExitButton.h"

// This constructor sets the position and visuals of the button.
ExitButton::ExitButton(Scene* scene, string name, SpriteLibrary* spriteLibrary, Vector2 position)
	:	Button(scene, name, spriteLibrary, position)
{

}

// This function closes the application
void ExitButton::Action()
{
	HAPI.Close();
}
