/***********************
 * File:		clock.h
 * Description: Header file for the clock class
 * Author:		Asma Shakil & Kerry Pellett
 * Contact:		kerry.pellet@gmail.com
********************/

#ifndef _CLOCK_H_
#define _CLOCK_H_

// Library Includes
#include <chrono>
#include <vector>

class Clock
{
	// Member Functions
public:
	Clock();
	~Clock();
	bool Initialise();
	void Process();
	float GetDeltaTick();

protected:

private:
	Clock(const Clock& _kr);
	Clock& operator= (const Clock& _kr);

	// Member Variables
public:

protected:
	double m_fTimeElapsed;
	double m_fDeltaTime;
	std::chrono::high_resolution_clock::time_point m_fLastTime;
	std::chrono::high_resolution_clock::time_point m_fCurrentTime;

	std::vector<double> m_vecTimeHistory;

	long long m_llNumCounts;

private:

};
#endif // 
