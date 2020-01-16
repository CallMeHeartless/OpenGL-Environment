#include "Shape.h"
#include "MeshRenderer.h"

/*********
 * @Name:				CreateShape
 * @Description:		Factory method to create a new shape
 * @Arguments:			void
 * @Returns:			void
**********/
std::shared_ptr<Shape> Shape::CreateShape(EShapeTypes _eType) {
	// Create new shape object
	std::shared_ptr<Shape> pShape = std::make_shared<Shape>();
	pShape->m_eShapeType = _eType;

	// Create and add Mesh Renderer component
	std::shared_ptr<MeshRenderer> pMeshRenderer = std::make_unique<MeshRenderer>();
	pMeshRenderer->SetMesh(static_cast<EMeshType>(_eType));

	// Add the Mesh Renderer
	pShape->AddComponent(pMeshRenderer);

	return pShape;
}

