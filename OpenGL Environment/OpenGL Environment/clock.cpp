
// Library Includes
#include <chrono>

// Local Includes
#include "clock.h"

/*********
 * @Name:				Exit
 * @Description:		Handles the termination of the application
 * @Arguments:			void
 * @Returns:			void
**********/
Clock::Clock(): m_fTimeElapsed(0.0f), m_fDeltaTime(0.0f){
}

/*********
 * @Name:				Exit
 * @Description:		Handles the termination of the application
 * @Arguments:			void
 * @Returns:			void
**********/
Clock::~Clock(){
}

/*********
 * @Name:				Exit
 * @Description:		Handles the termination of the application
 * @Arguments:			void
 * @Returns:			void
**********/
bool Clock::Initialise()
{
	m_fCurrentTime = std::chrono::high_resolution_clock::now();
	return (true);
}

/*********
 * @Name:				Exit
 * @Description:		Handles the termination of the application
 * @Arguments:			void
 * @Returns:			void
**********/
void
Clock::Process(){
	m_fLastTime = m_fCurrentTime;

	m_fCurrentTime = std::chrono::high_resolution_clock::now();

	m_fDeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_fCurrentTime - m_fLastTime).count();

	m_fTimeElapsed += m_fDeltaTime;
}

/*********
 * @Name:				GetDeltaTick
 * @Description:		Obtains the time between clock ticks, representing the time between frames (in seconds)
 * @Arguments:			void
 * @Returns:			float (m_fDeltaTime)
**********/
float Clock::GetDeltaTick(){
	return static_cast<float>(m_fDeltaTime);
}