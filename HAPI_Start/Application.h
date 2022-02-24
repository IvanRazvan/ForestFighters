#pragma once

#include "Defines.h"

class Graphics;
class SoundManager;
class Input;
class Scene;

/*
	Application is the main class of the project.
	It implements a stack of scenes in order to compute and display the contents of the game.
*/

class Application
{
private:
	std::shared_ptr <Graphics> m_graphics;
	std::shared_ptr <SoundManager> m_sound;
	std::shared_ptr <Input> m_input;

	int m_globalClock{ 0 };
	int m_updateClock{ 0 };


	std::stack< std::shared_ptr <Scene> > m_scenes;
	bool m_popScene{ false };
	bool m_pushScene{ false };
	std::shared_ptr <Scene> m_sceneToPush;

	void PushScene();
	void PopScene();

public:
	Application();

	void RequestPushScene(std::shared_ptr <Scene> newScene);
	void RequestPopScene();
	void Run();

	Graphics* GetGraphics() const;
	SoundManager* GetSound() const;
	Input* GetInput() const;
};

