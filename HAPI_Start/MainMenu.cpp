#include "MainMenu.h"
#include "LevelSelectLoader.h"
#include "ExitButton.h"
#include "Graphics.h"
#include "SpriteLibrary.h"

// This constructor sets the scene
MainMenu::MainMenu(Application* application)
	: Scene(application)
{
	SetSprites();

	m_Background = make_shared<UIObject>("TitleScreen", m_SpriteLibrary.get());

	m_Buttons.emplace_back(std::make_shared <LevelSelectLoader>(this, "PlayButton", m_SpriteLibrary.get(), Vector2(screenWidth / 2 - 100, 400)));
	m_Buttons.emplace_back(std::make_shared <ExitButton>(this, "ExitButton", m_SpriteLibrary.get(), Vector2(screenWidth / 2 - 100, 600)));
}

// This function loads the sprites
void MainMenu::SetSprites()
{
	m_SpriteLibrary->AddEntry("PlayButton", true);
	m_SpriteLibrary->AddEntry("ExitButton", true);
	m_SpriteLibrary->AddEntry("TitleScreen", false);
}

// This function initialises the scene
void MainMenu::Init()
{
	
}

// This function updates the buttons
void MainMenu::Update()
{
	for (std::shared_ptr<Button> button : m_Buttons)
		button->Update();
}

// This function renders the buttons
void MainMenu::Render(float t)
{
	GetGraphics()->ClearScreen();
	
	GetGraphics()->Render(m_Background.get(), Vector2());

	for (std::shared_ptr<Button> button : m_Buttons)
		button->Render(t);
}
