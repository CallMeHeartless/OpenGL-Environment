#include "SceneManager.h"
#include "Scene.h"

std::unique_ptr<SceneManager> SceneManager::s_pInstance = nullptr;

SceneManager::SceneManager(){}

SceneManager::~SceneManager() {
}

/*********
 * @Name:				GetInstance
 * @Description:		Returns the static singleton instance, or creates a new one if none exist
 * @Arguments:			void
 * @Returns:			std::unique_ptr<SceneManager>& (s_pInstance)
**********/
std::unique_ptr<SceneManager>& SceneManager::GetInstance() {
	if (!s_pInstance) {
		s_pInstance = std::unique_ptr<SceneManager>(new SceneManager());
	}
	return s_pInstance;
}

/*********
 * @Name:				Update
 * @Description:		Update the active scene
 * @Arguments:			float _fDeltaTick (the time between frames in seconds)
 * @Returns:			void
**********/
void SceneManager::Update(float _fDeltaTick) {
	// Ensure a scene exists
	if (!m_pScene) { return; }

	// Update the scene
	m_pScene->Update(_fDeltaTick);
}

/*********
 * @Name:				Render
 * @Description:		Instructs the active scene to render the current frame
 * @Arguments:			void
 * @Returns:			void
**********/
void SceneManager::Render() {
	// Ensure a scene exists
	if (!m_pScene) { return; }

	// Render the current frame
	m_pScene->Render();
}

/*********
 * @Name:				LoadScene
 * @Description:		Creates a default scene
 * @Arguments:			void
 * @Returns:			void
**********/
void SceneManager::LoadScene() {
	m_pScene = std::make_unique<Scene>();
}

/*********
 * @Name:				GetActiveScene
 * @Description:		Obtains the active scene
 * @Arguments:			void
 * @Returns:			std::unique_ptr<Scene>& (m_pScene)
**********/
std::unique_ptr<Scene>& SceneManager::GetActiveScene() {
	return m_pScene;
}
