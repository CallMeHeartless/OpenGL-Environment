/***********************
 * File:		Component.h
 * Description: Header file for the base Component class
 * Author:		Kerry Pellett
 * Contact:		kerry.pellet@gmail.com
********************/
#ifndef __COMPONENT_H__
#define __COMPONENT_H__

// Library Includes
#include <memory>

// Forward Declaration
class GameObject;

class Component {
	public:
		Component();
		virtual ~Component();

		virtual void Update(float _fDeltaTick) = 0;


		void SetParent(GameObject* _pParent);

	protected:
		std::shared_ptr<GameObject> m_pParent;		// A reference to the parent Game Object
		virtual void OnAdd();
};

#endif // !__COMPONENT_H__

