#include "Input.h"

std::unique_ptr<Input> Input::s_pInstance = nullptr;

Input::~Input() {
}

/*********
 * @Name:				GetInstance
 * @Description:		Obtains a pointer to the singleton instance, creating a new one if needed
 * @Arguments:			void
 * @Returns:			std::unique_ptr<Input>& (s_pInstance)
**********/
std::unique_ptr<Input>& Input::GetInstance() {
	if (!s_pInstance) {
		s_pInstance = std::unique_ptr<Input>(new Input());
	}
	return s_pInstance;
}

/*********
 * @Name:				Initialise
 * @Description:		Assigns the glut input functions
 * @Arguments:			void
 * @Returns:			void
**********/
void Input::Initialise() {
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
}

void Input::MouseButton(int _iButton, int _iButtonState, int _iX, int _iY) {
}

/*********
 * @Name:				KeyDown
 * @Description:		Processes glut keyboard down events
 * @Arguments:			unsigned char _ucKey (the keyboard key), int _iX (mouse X), int _iY (mouse Y)
 * @Returns:			void
**********/
void Input::KeyDown(unsigned char _ucKey, int _iX, int _iY) {
	if (!s_pInstance) { return; }
	switch (s_pInstance->m_eKeyStates[_ucKey]) {
		case eFirstReleased:{
			// Fall through
		}

		case eReleased:{
			s_pInstance->m_eKeyStates[_ucKey] = eFirstPressed;
			break;
		}

		case eFirstPressed:{
			s_pInstance->m_eKeyStates[_ucKey] = ePressed;
			break;
		}

		default:break;

	}
}

/*********
 * @Name:				KeyUp
 * @Description:		Processes glut keyboard up events
 * @Arguments:			unsigned char _ucKey (the keyboard key), int _iX (mouse X), int _iY (mouse Y)
 * @Returns:			void
**********/
void Input::KeyUp(unsigned char _ucKey, int _iX, int _iY) {
	if (!s_pInstance) { return; }
	switch (s_pInstance->m_eKeyStates[_ucKey]) {
		case eFirstPressed:	{
			// Fall through
		}

		case ePressed:{
			s_pInstance->m_eKeyStates[_ucKey] = eFirstReleased;
			break;
		}

		case eFirstReleased:{
			s_pInstance->m_eKeyStates[_ucKey] = eReleased;
			break;
		}

		default:break;

	}
}

/*********
 * @Name:				GetKeyState
 * @Description:		Gets the current input state of a given key
 * @Arguments:			unsigned char _ucKey (the key whose state we wish to know)
 * @Returns:			EInputState (the state of the key passed in)
**********/
EInputState Input::GetKeyState(unsigned char _ucKey) const {
	return m_eKeyStates[_ucKey];
}

/*********
 * @Name:				MakePressedOrReleased
 * @Description:		To be called at the end of Update to ensure key states are updated logically
 * @Arguments:			void
 * @Returns:			void
**********/
void Input::MakePressedOrRelease() {
	// Iterate through the characters and make them pressed or released
	//for (unsigned int i = 0; i < 255; ++i) {
	//	if (m_eKeyStates[i] == eFirstPressed) {
	//		m_eKeyStates[i] = ePressed;
	//	}
	//	else if (m_eKeyStates[i] == eFirstReleased) {
	//		m_eKeyStates[i] = eReleased;
	//	}
	//}

	// We only actually care about one key here, so we'll only examine that
	if (m_eKeyStates['f'] == eFirstPressed) {
		m_eKeyStates['f'] = ePressed;
	}
	else if (m_eKeyStates['f'] == eFirstReleased) {
		m_eKeyStates['f'] = eReleased;
	}
}

Input::Input() {
}
