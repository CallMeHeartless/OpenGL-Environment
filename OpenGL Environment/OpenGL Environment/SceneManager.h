/***********************
 * File:		SceneManager.h
 * Description: Header file for the SceneManager class
 * Author:		Kerry Pellett
 * Contact:		kerry.pellet@gmail.com
********************/
#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

// Library Includes
#include <memory>

// Forward Declaration
class Scene;

class SceneManager {
	public:
		~SceneManager();

		static std::unique_ptr<SceneManager>& GetInstance();

		void Update(float _fDeltaTick);
		void Render();

		void LoadScene();
		std::unique_ptr<Scene>& GetActiveScene();

	private:
		SceneManager(); // Enforce singleton 
		static std::unique_ptr<SceneManager> s_pInstance;

		std::unique_ptr<Scene> m_pScene;

};

#endif // !__SCENEMANAGER_H__
