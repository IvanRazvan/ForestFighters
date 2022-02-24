#include "PlayButton.h"
#include "Scene.h"
#include "Simulation.h"
#include "Application.h"
#include "SoundManager.h"

// This constructor sets the position and visuals of the button.
PlayButton::PlayButton(Scene* scene, string name, SpriteLibrary* spriteLibrary, Vector2 position, E_Difficulty difficulty)
	:	Button(scene, name, spriteLibrary, position), m_difficulty(difficulty)
{

}

// This function pushes the Simulation scene on the stack.
void PlayButton::Action()
{
	// It writes the level details into the LevelData.txt folder depending on the difficulty.
	ofstream out(levelMainFilePath + (string)"LevelData.txt");

	switch (m_difficulty) {
	case E_Difficulty::EASY:
		out << "FinalWave: 5\n";
		out << "Shooter " + to_string(4) + '\n';
		out << "Trooper " + to_string(4) + '\n';
		out << "Tank " + to_string(4) + '\n';
		break;

	case E_Difficulty::HARD:
		out << "FinalWave: 10\n";
		out << "ShooterHard " + to_string(6) + '\n';
		out << "TrooperHard " + to_string(6) + '\n';
		out << "TankHard " + to_string(6) + '\n';
		break;

	case E_Difficulty::ENDLESS:
		out << "FinalWave: 9999\n";
		out << "Shooter " + to_string(3) + '\n';
		out << "Trooper " + to_string(3) + '\n';
		out << "Tank " + to_string(3) + '\n';
		out << "ShooterHard " + to_string(1) + '\n';
		out << "TrooperHard " + to_string(1) + '\n';
		out << "TankHard " + to_string(1) + '\n';
		break;
	}
	out.close();

	// It pushes the Simulation scene on the stack
	GetApplication()->RequestPushScene(std::make_shared <Simulation>(GetApplication()));
	GetApplication()->GetSound()->Play("click");
}
