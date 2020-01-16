#include <iostream>
#include <memory>

#include "Scene.h"
#include "camera.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Shape.h"

Scene::Scene() {
	// Create an authographic camera
	m_pCamera = std::make_unique<Camera>(45.0f, 1920.0f/1080.0f, 0.1f, 1000.0f);

	// Create default shapes for the demo
	m_vecpGameObjects.push_back(Shape::CreateShape(eShapeTriangle));
	m_vecpGameObjects.push_back(Shape::CreateShape(EShapeTypes::eShapeSquare));
	m_vecpGameObjects.push_back(Shape::CreateShape(EShapeTypes::eShapeHexagon));
	m_vecpGameObjects.push_back(Shape::CreateShape(eShapeCircle));

	// Move positions
	m_vecpGameObjects[1]->GetTransform().position = glm::vec3(1.0f, 1.0f, 0.0f);
	m_vecpGameObjects[2]->GetTransform().position = glm::vec3(-1.0f, -1.0f, 0.0f);
	m_vecpGameObjects[3]->GetTransform().position = glm::vec3(2.0f, 2.0f, 1.0f);

	// Change colours
	m_vecpGameObjects[1]->GetComponent<MeshRenderer>()->SetColour(glm::vec4(1.0f, 0.5f, 0.5f, 1.0f));
	m_vecpGameObjects[2]->GetComponent<MeshRenderer>()->SetColour(glm::vec4(0.3f, 1.0f, 0.8f, 1.0f));
	m_vecpGameObjects[3]->GetComponent<MeshRenderer>()->SetColour(glm::vec4(0.0f, 0.75f, 1.0f, 1.0f));
}

Scene::~Scene() {
	// Clear game objects
	m_vecpGameObjects.clear();
}

/*********
 * @Name:				Update
 * @Description:		Updates all game objects in the scene
 * @Arguments:			float _fDeltaTick (the time between frames in seconds)
 * @Returns:			void
**********/
void Scene::Update(float _fDeltaTick) {
	// Iterate through game objects and pass the delta tick to them
	for (auto& gameObject : m_vecpGameObjects) {
		// Check for valid reference
		if (gameObject) {
			gameObject->Update(_fDeltaTick);
		}
	}
}

/*********
 * @Name:				Render
 * @Description:		Renders the current scene
 * @Arguments:			void
 * @Returns:			void
**********/
void Scene::Render() {
	// The scene can't be rendered without a valid camera, so return
	if (!m_pCamera) {
		// Debug statement - make this better later
		std::cout << "ERROR: The active Scene does not have a valid camera - it cannot be rendered" << std::endl;
		return;
	}

	// Iterate through game objects and see if they have a render component
	for (auto& gameObject : m_vecpGameObjects) {
		//std::shared_ptr<MeshRenderer> pMeshRenderer = gameObject->GetComponent<MeshRenderer>();
		MeshRenderer* pMeshRenderer = gameObject->GetComponent<MeshRenderer>();

		// Check if component was found
		if (pMeshRenderer) {
			// Render the object
			pMeshRenderer->Render(m_pCamera);
			
		}
	}
}


