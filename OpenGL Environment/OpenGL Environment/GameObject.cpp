#include "GameObject.h"

GameObject::GameObject() {
	// Assign a default transform
	m_transform = Transform::CreateDefaultTransform();
}

GameObject::~GameObject() {
	// Clear components list
	m_vecpComponents.clear();
}

/*********
 * @Name:				Update
 * @Description:		Iterates through components and updates them
 * @Arguments:			float _fDeltaTick (the time between frames in seconds)
 * @Returns:			void
**********/
void GameObject::Update(float _fDeltaTick) {
	// Iterate through and update all components
	for (auto& component : m_vecpComponents) {
		// Ensure reference is valid
		if (component) {
			// Update
			component->Update(_fDeltaTick);
		}
	}
}

/*********
 * @Name:				GetTransform
 * @Description:		Obtains a reference to the object's transform
 * @Arguments:			void
 * @Returns:			Transform& (m_transform)
**********/
Transform& GameObject::GetTransform(){
	return m_transform;
}

/*********
 * @Name:				AddComponent
 * @Description:		Adds a component to the game object
 * @Arguments:			std::shared_prt<Component> _pComponent (pointer to the component to be added)
 * @Returns:			void
**********/
 void GameObject::AddComponent(std::shared_ptr<Component> _pComponent) {
	 // Do not add an empty component
	 if (!_pComponent) { return; }

	 // Set this object to be the component's parent
	 _pComponent->SetParent(this);
	 
	 // Add to vector
	 m_vecpComponents.push_back(_pComponent);
 }