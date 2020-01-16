/***********************
 * File:		Input.h
 * Description: Header file for the Input class
 * Author:		Kerry Pellett
 * Contact:		kerry.pellet@gmail.com
********************/
#ifndef __INPUT_H__
#define __INPUT_H__

// Library Includes
#include <memory>

// Local Includes
#include "Dependencies/freeglut/freeglut.h"
#include "Dependencies/glm/vec2.hpp"

enum EInputState {
	eFirstReleased = 0,
	eReleased,
	eFirstPressed,
	ePressed
};

enum EInputMouse {
	eMouseLeft = 0,
	eMouseMiddle,
	eMouseRight
};

class Input {
	public:
		~Input();
		static std::unique_ptr<Input>& GetInstance();

		void Initialise();

		static void MouseButton(int _iButton, int _iButtonState, int _iX, int _iY);
		static void KeyDown(unsigned char _ucKey, int _iX, int _iY);
		static void KeyUp(unsigned char _ucKey, int _iX, int _iY);

		EInputState GetKeyState(unsigned char _ucKey)const;
		void MakePressedOrRelease();

	private:
		Input(); // Enforce singleton
		static std::unique_ptr<Input> s_pInstance;
		glm::vec2 m_MousePosition;
		EInputState m_eKeyStates[255] = { eReleased };
		EInputState m_eMouseState[3] = { eReleased };
};

#endif // !__INPUT_H__
