
// Library Includes
#include <memory>

// Local Includes
#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
#include "clock.h"
#include "main.h"

// Global Variables
std::unique_ptr<Clock> g_pClock;

/*********
* @Description: Processes game entities and systems each frame, using the time between frames 
* @Arguments: void
* @Returns: void
**********/
void Update() {
	// Update the clock
	g_pClock->Process();
	float fDeltaTick = g_pClock->GetDeltaTick();
}

void Render() {

}

void Exit() {

}

int main(int argc, char** argv) {
	// Initialise OpenGL Utilities
	glutInit(&argc, argv);

	// Set the default window and OpenGL render properties
	InitialiseDefaultParameters();

	// Initialise the clock
	g_pClock = std::make_unique<Clock>();
	g_pClock->Initialise();

	// Enter main loop
	glutMainLoop();
	return 0;
}

void InitialiseMainWindow() {
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(500, 0);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("OpenGL Environment by Kerry Pellett");
}

void InitialiseDefaultRenderParameters() {
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Set vertex winding to CCW
	glEnable(GL_CCW);

	// Enable back face culling
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void InitialiseGlutFunctions() {
	glutIdleFunc(Update);
	glutDisplayFunc(Render);
	glutCloseFunc(Exit);
}

void InitialiseDefaultParameters() {
	// Create the main window
	InitialiseMainWindow();

	glewInit();

	// Set default render parameters
	InitialiseDefaultRenderParameters();

	// Set glut loop functions
	InitialiseGlutFunctions();
}

