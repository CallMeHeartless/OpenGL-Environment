#include "Component.h"
#include "GameObject.h"

Component::Component() {
}

Component::~Component() {
}

void Component::OnAdd() {
}

/*********
 * @Name:				SetParent
 * @Description:		Attaches the component to a parent game object, and invokes its OnAdd function
 * @Arguments:			GameObject* _pParent (the new parent, can be nullptr)
 * @Returns:			void
**********/
void Component::SetParent(GameObject* _pParent) {
	m_pParent = std::shared_ptr<GameObject>(_pParent);
	OnAdd();
}
