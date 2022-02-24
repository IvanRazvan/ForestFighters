#include "Input.h"

// This function returns the sign of a number
int Input::Sign(int value) const
{
	return 2 * (value >= 0) - 1;
}

// This function maps value from minB to maxB
int Input::Map(int value, int minA, int maxA, int minB, int maxB) const
{
	if (abs(value) < minA)
		return minB;
	return minA + abs(value) * (maxB - minB) / (maxA - minA);
}

// This function returns the sum of the keyboard inputs
Vector2 Input::GetKeyboardInput() const
{
	Vector2 dir;

	if (keyData.scanCode['W'])
		dir = dir + Vector2(0, -1);

	if (keyData.scanCode['A'])
		dir = dir + Vector2(-1, 0);

	if (keyData.scanCode['S'])
		dir = dir + Vector2(0, 1);

	if (keyData.scanCode['D'])
		dir = dir + Vector2(1, 0);

	return dir;
}

// This function returns the left joystick input
Vector2 Input::GetControllerLeftInput(int controller) const
{
	HAPI_TControllerData controllerData = HAPI.GetControllerData(controller);

	if (controllerData.isAttached)
	{
		int x = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
		int y = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
		int deadzone = HK_GAMEPAD_LEFT_THUMB_DEADZONE;

		return Vector2(Sign(x) * Map(x, deadzone, 32767, 0, 32767), -Sign(y) * Map(y, deadzone, 32767, 0, 32767));
	}

	return Vector2();
}

// This function returns the right joystick input
Vector2 Input::GetControllerRightInput(int controller) const
{
	HAPI_TControllerData controllerData = HAPI.GetControllerData(controller);

	if (controllerData.isAttached)
	{
		int x = controllerData.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_X];
		int y = controllerData.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_Y];
		int deadzone = HK_GAMEPAD_RIGHT_THUMB_DEADZONE;

		return Vector2(Sign(x) * Map(x, deadzone, 32767, 0, 32767), -Sign(y) * Map(y, deadzone, 32767, 0, 32767));
	}

	return Vector2();
}

// This function makes the controller rumble
void Input::SetControllerRumble(int controller, int left, int right) const
{
	HAPI_TControllerData controllerData = HAPI.GetControllerData(controller);

	if (controllerData.isAttached)
		HAPI.SetControllerRumble(controller, left, right);
}

// This function returns true if the player presses the right shoulder of the controller
bool Input::GetControllerFireInput(int controller) const
{
	HAPI_TControllerData controllerData = HAPI.GetControllerData(controller);

	if (controllerData.isAttached)
	{
		return controllerData.digitalButtons[HK_DIGITAL_RIGHT_SHOULDER];
	}

	return false;
}

// This function returns values depending on what was used to trigger fire
int Input::GetFireInputType()
{
	if (IsClickingMouse())
		return 1;

	if(IsClickingController())
		return 2;

	return 0;
}

// This function returns the aimed position
Vector2 Input::GetPlayerAimInput(Vector2 screenPosition)
{
	Vector2 result;
	switch (GetFireInputType()) {
	case 0:
		return Vector2();
	case 1:
		result = GetMousePosition(screenPosition);

		return result;
	case 2:
		for (int i = 0; i < HAPI.GetMaxControllers(); i++)
		{
			result = result + GetControllerRightInput(i);
		}

		return result;
	}
}

// This function returns the sum of all movement inputs
Vector2 Input::GetPlayerMovementInput() const
{
	Vector2 result;

	result = result + GetKeyboardInput();

	for (int i = 0; i < HAPI.GetMaxControllers(); i++)
	{
		result = result + GetControllerLeftInput(i);
	}

	result.normalize();

	return result;
}

// This function returns the mouse position
Vector2 Input::GetMousePosition(Vector2 screenPosition) const
{
	return Vector2(mouseData.x, mouseData.y) + screenPosition;
}

// This function returns true if the player is clicking the mouse
bool Input::IsClickingMouse()
{
	if (mouseData.leftButtonDown && !m_hasClickedMouse)
	{
		m_hasClickedMouse = true;
		return true;
	}
	if (!mouseData.leftButtonDown)
		m_hasClickedMouse = false;
	return false;
}

// This function returns true if the player is clicking the controller
bool Input::IsClickingController()
{
	bool click{ false };
	for (int i = 0; i < HAPI.GetMaxControllers() && click == false; i++)
	{
		click = click || GetControllerFireInput(i);
	}

	if (click && !m_hasClickedController)
	{
		m_hasClickedController = true;

		return true;
	}

	if (!click)
		m_hasClickedController = false;
	return false;
}
