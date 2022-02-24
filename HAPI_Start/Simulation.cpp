#include "Simulation.h"
#include "StaticObject.h"
#include "CharacterLibrary.h"
#include "PlayableCharacter.h"
#include "AICharacter.h"
#include "BackButton.h"
#include "ResetButton.h"
#include "Graphics.h"
#include "ProgressBar.h"
#include "SpriteLibrary.h"

// This constructor sets the scene
Simulation::Simulation(Application* application)
	 :	Scene(application)
{
	// Set the world bounding
	 m_worldBoundaries.left = GameBoundaryLeft;
	 m_worldBoundaries.right = GameBoundaryRight;
	 m_worldBoundaries.bottom = GameBoundaryBottom;
	 m_worldBoundaries.top = GameBoundaryTop;

	 SetSprites();

	 // Add the characters
	 m_characterLibrary = std::make_shared <CharacterLibrary>();
	 m_characterLibrary->AddEntry("Druid");
	 m_characterLibrary->AddEntry("Warrior");
	 m_characterLibrary->AddEntry("Ranger");
	 m_characterLibrary->AddEntry("Mage");

	 ifstream in(levelMainFilePath + (string)"LevelData.txt");
	 string templateWord, difficultyFactor;
	 in >> templateWord >> m_finalWave;

	 string enemyname;
	 int amount;
	 m_enemyTotalNumber = 0;
	 while (in >> enemyname >> amount)
	 {
		 // Add Enemies
		 m_characterLibrary->AddEntry(enemyname);
		 m_enemyTotalNumber += amount;
		 for (int i = 0; i < amount; i++)
			 m_gameObjects.emplace_back(std::make_shared <AICharacter>(this, enemyname, m_characterLibrary.get(), m_SpriteLibrary.get(), Vector2()));
	 }
	 in.close();

	 // Add the Statics
	 for (int i = 0; i < 13; i++)
	 {
		 m_gameObjects.emplace_back(std::make_shared <StaticObject>(this, "Bush", m_SpriteLibrary.get(), m_worldBoundaries.GetRandomPosition()));
		 m_gameObjects.emplace_back(std::make_shared <StaticObject>(this, "Tree", m_SpriteLibrary.get(), m_worldBoundaries.GetRandomPosition()));
	 }

	 // Add the Player
	 m_gameObjects.emplace_back(std::make_shared <PlayableCharacter>(this, "Druid", m_characterLibrary.get(), m_SpriteLibrary.get(), Vector2(300, 100)));
	 m_player = m_gameObjects.back().get();

	 // Add friendly AI
	 m_gameObjects.emplace_back(std::make_shared <AICharacter>(this, "Ranger", m_characterLibrary.get(), m_SpriteLibrary.get(), Vector2(300, 200)));
	 m_gameObjects.emplace_back(std::make_shared <AICharacter>(this, "Warrior", m_characterLibrary.get(), m_SpriteLibrary.get(), Vector2(300, 200)));
	 m_gameObjects.emplace_back(std::make_shared <AICharacter>(this, "Mage", m_characterLibrary.get(), m_SpriteLibrary.get(), Vector2(300, 200)));

	 // Add buttonds
	 m_Buttons.emplace_back(std::make_shared <BackButton>(this, "BackButton", m_SpriteLibrary.get(), Vector2(500, 550)));
	 m_Buttons.emplace_back(std::make_shared <ResetButton>(this, "RestartButton", m_SpriteLibrary.get(), Vector2(825, 550)));

	 // Set the rest of the UI
	 m_map = make_shared<UIObject>("Map", m_SpriteLibrary.get());
	 m_win = make_shared<UIObject>("Win", m_SpriteLibrary.get());
	 m_lose = make_shared<UIObject>("Lose", m_SpriteLibrary.get());
	 m_waveBar = make_shared<ProgressBar>("Wave", m_SpriteLibrary.get(), Vector2());
	 m_waveBar->SetPosition(Vector2(800 - m_waveBar->GetBorder()->GetWidth() / 2, 0));
}

// This function returns true if the position is in boundaries
bool Simulation::IsInBoundaries(Vector2 position) const
{
	return m_worldBoundaries.HoldsPosition(position);
}

// This function returns a random position in boundaries
Vector2 Simulation::GetRandomPosition() const
{
	return m_worldBoundaries.GetRandomPosition();
}

// This function returns a reference to the GameObject vector 
vector<std::shared_ptr<GameObject>>& Simulation::GetGameObjects()
{
	return m_gameObjects;
}

// This function returns the player position
Vector2 Simulation::GetPlayerPosition() const
{
	return m_player->GetPosition();
}

// This function loads the sprites
void Simulation::SetSprites()
{
	m_SpriteLibrary->AddEntry("Map", false);
	m_SpriteLibrary->AddEntry("Win", true);
	m_SpriteLibrary->AddEntry("Lose", true);
	m_SpriteLibrary->AddEntry("Bush", true);
	m_SpriteLibrary->AddEntry("Tree", true);

	m_SpriteLibrary->AddEntry("BackButton", true);
	m_SpriteLibrary->AddEntry("RestartButton", true);

	m_SpriteLibrary->AddEntry("Progress_border", true);
	m_SpriteLibrary->AddEntry("Progress_progress", true);
	m_SpriteLibrary->AddEntry("Wave_border", true);
	m_SpriteLibrary->AddEntry("Wave_progress", true, 10, 2.5f);

	m_SpriteLibrary->AddEntry("Druid", true, 4, 0.5f);
	m_SpriteLibrary->AddEntry("DruidProjectile", true, 4, 0.5f);
	m_SpriteLibrary->AddEntry("DruidProjectileExplosion", true, 5, 0.1f);

	m_SpriteLibrary->AddEntry("Mage", true, 4, 0.5f);
	m_SpriteLibrary->AddEntry("MageProjectile", true, 4, 0.5f);
	m_SpriteLibrary->AddEntry("MageProjectileExplosion", true, 5, 0.1f);

	m_SpriteLibrary->AddEntry("Warrior", true, 4, 1.0f);
	m_SpriteLibrary->AddEntry("WarriorProjectile", true, 4, 0.5f);
	m_SpriteLibrary->AddEntry("WarriorProjectileExplosion", true, 5, 0.1f);

	m_SpriteLibrary->AddEntry("Ranger", true, 4, 0.5f);
	m_SpriteLibrary->AddEntry("RangerProjectile", true, 4, 0.2f);
	m_SpriteLibrary->AddEntry("RangerProjectileExplosion", true, 5, 0.1f);

	m_SpriteLibrary->AddEntry("Shooter", true);
	m_SpriteLibrary->AddEntry("Trooper", true, 4, 0.5f);
	m_SpriteLibrary->AddEntry("Tank", true, 4, 0.5f);
	m_SpriteLibrary->AddEntry("EnemyProjectile", true, 4, 0.5f);
	m_SpriteLibrary->AddEntry("EnemyProjectileExplosion", true, 6, 0.1f);
}

// This function initialises the scene
void Simulation::Init()
{
	m_isRunning = true;
	m_wave = 1;

	for (shared_ptr<GameObject> object : m_gameObjects)
	{
		object->Reset();
	}

	for (std::shared_ptr <Button> button : m_Buttons)
	{
		button->SetActiveState(false);
	}
}

// This function handles the update loop for the game world
void Simulation::Update()
{
	for (std::shared_ptr<Button> button : m_Buttons)
		if(button->IsActive())
			button->Update();

	if (m_isRunning == false)
		return;

	// If the player is dead, we activate the buttons 
	if (m_player->IsActive() == false)
	{
		m_isRunning = false;

		for (std::shared_ptr <Button> button : m_Buttons)
		{
			button->SetActiveState(true);
		}
	}

	if (m_wave <= m_finalWave)
	{
		// It counts the remaining enemies
		m_enemyCounter = 0;
		for (std::shared_ptr<GameObject> object : m_gameObjects)
		{
			if (object->IsActive())
			{
				object->Update();

				if (object->GetType() == E_ObjectType::CHARACTER && object->GetTag() != "player_team")
					m_enemyCounter++;
			}
		}

		m_waveBar->UpdateProgress(1.0f - (float)m_enemyCounter / m_enemyTotalNumber);

		// It progresses to the next wave if needed
		if (m_enemyCounter == 0)
		{
			m_wave++;

			// It stops if it reaches the end of the level
			if (m_wave <= m_finalWave)
			{
				for (std::shared_ptr<GameObject> object : m_gameObjects)
				{
					if (object->GetType() == E_ObjectType::CHARACTER && object->GetTag() != "player_team")
						object->Reset();
				}
			}
			else
			{
				for (std::shared_ptr <Button> button : m_Buttons)
				{
					button->SetActiveState(true);
				}
			}
		}
	}
	else
	{
		m_isRunning = false;
	}
}

// This function handles the rendering for all entities
void Simulation::Render(float t)
{
	GetGraphics()->ClearScreen();

	GetGraphics()->Render(m_map.get(), Vector2(-m_map->GetWidth() / 2, -m_map->GetHeight() / 2));

	GetGraphics()->SortRenderingQueue(m_gameObjects);

	if (m_isRunning == false)
		t = 0;

	for (std::shared_ptr<GameObject> object : m_gameObjects)
		if (object->IsActive())
			object->Render(t);

	if (m_wave > m_finalWave)
	{
		GetGraphics()->RenderStatic(m_win.get(), Vector2());
	}

	if (m_player->IsActive() == false)
	{
		GetGraphics()->RenderStatic(m_lose.get(), Vector2());
	}

	for (std::shared_ptr<Button> button : m_Buttons)
		if (button->IsActive())
			button->Render(t);

	GetGraphics()->RenderStatic(m_waveBar.get(), m_waveBar->GetPosition());
	HAPI.RenderText(785, 0, HAPI_TColour::WHITE, to_string(m_wave), 50);
}
