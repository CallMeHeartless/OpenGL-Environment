/***********************
 * File:		Scene.h
 * Description: Header file for the Scene class
 * Author:		Kerry Pellett
 * Contact:		kerry.pellet@gmail.com
********************/
#ifndef __SCENE_H__
#define __SCENE_H__

// Library Includes
#include <memory>
#include <vector>

// Forward Declaration
class Camera;
class GameObject;

class Scene {
	public:
		Scene();
		~Scene();

		void Update(float _fDeltaTick);
		void Render();

	protected:
		std::vector<std::shared_ptr<GameObject>> m_vecpGameObjects;
		std::unique_ptr<Camera> m_pCamera;

};

#endif // !__SCENE_H__

