/***********************
 * File:		GameObject.h
 * Description: Header file for the base GameObject class
 * Author:		Kerry Pellett
 * Contact:		kerry.pellet@gmail.com
********************/
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

// Library Includes
#include <vector>
#include <memory>

// Local Includes
#include "Transform.h"
#include "Component.h"

class GameObject {
	public:
		GameObject();
		virtual ~GameObject();

		// Key functions
		virtual void Update(float _fDeltaTick);
		void AddComponent(std::shared_ptr<Component> _pComponent);

		// Accessors | Mutators
		Transform& GetTransform();

		// Type generic GETCOMPONENT
		template <class T>
		T* GetComponent()const;

	protected:
		// Member variables
		Transform m_transform;										// Describes the object's location in world space
		std::vector<std::shared_ptr<Component>> m_vecpComponents;	// A list of components to be added to the object
};


template<class T>
T* GameObject::GetComponent() const {
	// Iterate through components
	for (auto& component : m_vecpComponents) {
		// Attempt a dynamic cast for the component to the desired type
		T* pCast(dynamic_cast<T*>(component.get()));
		if (pCast) {
			// return the component
			return pCast;
		}
	}

	return (T*)nullptr;
}


#endif // !__GAMEOBJECT_H__

