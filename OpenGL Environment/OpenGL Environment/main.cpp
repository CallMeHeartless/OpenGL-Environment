/************
 * File:			main.cpp
 * Description:		Program entry point, defines glut functions and handles clock ticks
*/

// Library Includes
#include <memory>
#include <iostream>

// Local Includes
#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
#include "clock.h"
#include "SceneManager.h"
#include "Input.h"
#include "Scene.h"
#include "Mesh.h"

// Function Signatures
void InitialiseDefaultParameters();

// Global Variables
std::unique_ptr<Clock> g_pClock;


/*********
 * @Name:				Update
 * @Description:		Processes game entities and systems each frame, using the time between frames
 * @Arguments:			void
 * @Returns:			void
**********/
void Update() {
	// Update the clock
	if (g_pClock) {
		g_pClock->Process();
		float fDeltaTick = g_pClock->GetDeltaTick() / 1000.0f;

		// Update the scene
		SceneManager::GetInstance()->Update(fDeltaTick);
	}


	// Update the input state of the keys / mouse
	Input::GetInstance()->MakePressedOrRelease();

	// Notify that the frame has finished updating
	glutPostRedisplay();
}

/*********
 * @Name:				Render
 * @Description:		Renders the active scene for the current frame
 * @Arguments:			void
 * @Returns:			void
**********/
void Render() {
	// Clear the frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Render the current frame
	SceneManager::GetInstance()->Render();

	// Swap frame buffers
	glutSwapBuffers();
}

/*********
 * @Name:				Exit
 * @Description:		Handles the termination of the application
 * @Arguments:			void
 * @Returns:			void
**********/
void Exit() {
	Mesh::ClearStaticMeshStorage();
}

int main(int argc, char** argv) {
	// Initialise OpenGL Utilities
	glutInit(&argc, argv);

	// Initialise the OpenGL environment parameters and create a window
	InitialiseDefaultParameters();

	// Initialise the clock
	g_pClock = std::make_unique<Clock>();
	g_pClock->Initialise();

	// Initialise input
	Input::GetInstance()->Initialise();

	// Initialise default scene
	SceneManager::GetInstance()->LoadScene();

	// Enter main loop
	glutMainLoop();
	return 0;
}

/*********
 * @Name:				InitialiseMainWindow
 * @Description:		Creates the main application window
 * @Arguments:			void
 * @Returns:			void
**********/
void InitialiseMainWindow() {
	// These settings will allow for 2D or 3D rendering, with support for blending and anti-aliasing
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(750, 0);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("OpenGLEnvironment - Kerry Pellett");
}

/*********
 * @Name:				InitialiseDefaultRenderParameters
 * @Description:		Sets the OpenGL environment to be ready for 2D or 3D rendering with appropriate culling parameters
 * @Arguments:			void
 * @Returns:			void
**********/
void InitialiseDefaultRenderParameters() {
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Set vertex winding to CCW
	glEnable(GL_CCW);

	// Enable back face culling
	//glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

/*********
 * @Name:				InitialiseGlutFunctions
 * @Description:		Initialises the update and render loops, as well as the on exit function
 * @Arguments:			void
 * @Returns:			void
**********/
void InitialiseGlutFunctions() {
	glutIdleFunc(Update);
	glutDisplayFunc(Render);
	glutCloseFunc(Exit);
}

/*********
 * @Name:				InitialiseDefaultParameters
 * @Description:		Initialises the OpenGL environment
 * @Arguments:			void
 * @Returns:			void
**********/
void InitialiseDefaultParameters() {
	// Create the main window
	InitialiseMainWindow();

	glewInit();

	// Set default render parameters
	InitialiseDefaultRenderParameters();

	// Set glut loop functions
	InitialiseGlutFunctions();
}