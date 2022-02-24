#include "LevelSelectLoader.h"
#include "Scene.h"
#include "LevelSelect.h"
#include "Application.h"
#include "SoundManager.h"

// This constructor sets the position and visuals of the button.
LevelSelectLoader::LevelSelectLoader(Scene* scene, string name, SpriteLibrary* spriteLibrary, Vector2 position)
	: Button(scene, name, spriteLibrary, position)
{

}

// This function pushes the LevelSelect scene on the stack
void LevelSelectLoader::Action()
{
	GetApplication()->RequestPushScene(std::make_shared <LevelSelect>(GetApplication()));
	GetApplication()->GetSound()->Play("click");
}
