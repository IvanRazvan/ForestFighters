#pragma once

#include "Scene.h"
#include "BoundingBox.h"

class GameObject;
class CharacterLibrary;
class UIObject;
class ProgressBar;

/*
	Simulation is a Scene that handles game world.
*/

class Simulation :
	public Scene
{
private:
	bool m_isRunning{ true };
	int m_wave{ 1 };
	int m_finalWave{ 0 };
	int m_enemyCounter{ 0 };
	int m_enemyTotalNumber{ 0 };

	BoundingBox m_worldBoundaries;

	GameObject* m_player{ nullptr };

	std::shared_ptr <CharacterLibrary> m_characterLibrary;

	vector< std::shared_ptr <GameObject> > m_gameObjects;

	std::shared_ptr<UIObject> m_map;
	std::shared_ptr<UIObject> m_win;
	std::shared_ptr<UIObject> m_lose;
	std::shared_ptr<ProgressBar> m_waveBar;

public:
	Simulation(Application* application);

	bool IsInBoundaries(Vector2 position) const;
	Vector2 GetRandomPosition() const;
	Vector2 GetPlayerPosition() const;
	vector< std::shared_ptr <GameObject> >& GetGameObjects();

	void SetSprites() override;
	void Init() override;
	void Update() override;
	void Render(float t) override;
};

