#include "LevelSelect.h"
#include "PlayButton.h"
#include "BackButton.h"
#include "Graphics.h"
#include "SpriteLibrary.h"

// This constructor sets the scene
LevelSelect::LevelSelect(Application* application)
	: Scene(application)
{
	SetSprites();

	m_Background = make_shared<UIObject>("LevelSelect", m_SpriteLibrary.get());

	m_Buttons.emplace_back(std::make_shared <PlayButton>(this, "EasyButton", m_SpriteLibrary.get(), Vector2(screenWidth / 2 - 100, 100), E_Difficulty::EASY));
	m_Buttons.emplace_back(std::make_shared <PlayButton>(this, "HardButton", m_SpriteLibrary.get(), Vector2(screenWidth / 2 - 100, 250), E_Difficulty::HARD));
	m_Buttons.emplace_back(std::make_shared <PlayButton>(this, "EndlessButton", m_SpriteLibrary.get(), Vector2(screenWidth / 2 - 150, 400), E_Difficulty::ENDLESS));
	m_Buttons.emplace_back(std::make_shared <BackButton>(this, "BackButton", m_SpriteLibrary.get(), Vector2(screenWidth / 2 - 100, 600)));
}

// This function loads the sprites
void LevelSelect::SetSprites()
{
	m_SpriteLibrary->AddEntry("EasyButton", true);
	m_SpriteLibrary->AddEntry("HardButton", true);
	m_SpriteLibrary->AddEntry("EndlessButton", true);
	m_SpriteLibrary->AddEntry("BackButton", true);
	m_SpriteLibrary->AddEntry("LevelSelect", false);
}

// This function initialises the scene
void LevelSelect::Init()
{
	
}

// This function updates the buttons
void LevelSelect::Update()
{
	for (std::shared_ptr<Button> button : m_Buttons)
		button->Update();
}

// This function renders the buttons
void LevelSelect::Render(float t)
{
	GetGraphics()->ClearScreen();

	GetGraphics()->Render(m_Background.get(), Vector2());

	for (std::shared_ptr<Button> button : m_Buttons)
		button->Render(t);
}
