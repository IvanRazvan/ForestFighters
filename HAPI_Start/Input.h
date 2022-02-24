#pragma once

#include "Defines.h"
#include "Vector2.h"

/*
	Input class handles keyboard, mouse and controller input.
*/

class Input
{
private:
	bool m_hasClickedMouse{ false };
	bool m_hasClickedController{ false };
	const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();
	const HAPI_TMouseData& mouseData = HAPI.GetMouseData();

	int Sign(int value) const;
	int Map(int value, int minA, int maxA, int minB, int maxB) const;

	Vector2 GetKeyboardInput() const;
	Vector2 GetControllerLeftInput(int controller) const;

	Vector2 GetControllerRightInput(int controller) const;

	void SetControllerRumble(int controller, int left, int right) const;

	bool GetControllerFireInput(int controller) const;
	int GetFireInputType();

public:
	Vector2 GetPlayerAimInput(Vector2 screenPosition);
	Vector2 GetPlayerMovementInput() const;

	Vector2 GetMousePosition(Vector2 screenPosition) const;

	bool IsClickingMouse();
	bool IsClickingController();
};

