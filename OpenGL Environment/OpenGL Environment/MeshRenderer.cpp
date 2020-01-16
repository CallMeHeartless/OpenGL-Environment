#include "MeshRenderer.h"
#include "Dependencies/glm/gtc/matrix_transform.hpp"
#include "Dependencies/glm/gtc/type_ptr.hpp"
#include "Dependencies/glm/gtx/intersect.hpp"
#include "Dependencies/glm/gtc/quaternion.hpp"
#include "GameObject.h"
#include "camera.h"
#include "ShaderLoader.h"

std::shared_ptr<ShaderLoader> MeshRenderer::s_pShaderLoader = nullptr;

MeshRenderer::MeshRenderer() {
	// Establish ShaderLoader
	if (!s_pShaderLoader) {
		s_pShaderLoader = std::make_shared<ShaderLoader>();
	}

	// Set default shader program
	m_uiShaderProgram = s_pShaderLoader->CreateProgram("VertexShader.vs", "FragmentShader.fs");

	// Set default mesh
	m_pMesh = Mesh::CreateMesh(EMeshType::eTriangle);
}

MeshRenderer::~MeshRenderer() {
}

/*********
 * @Name:				Render
 * @Description:		Performs a basic render of the object
 * @Arguments:			std::unique_ptr<Camera>& _kpCamera (the scene's camera)
 * @Returns:			void
 * @Note:				This function could be greatly expanded to provide different render modes, with a switch statement and a render mode enum
**********/
void MeshRenderer::Render(std::unique_ptr<Camera>& _kpCamera) {
	// Do not render if there is no valid mesh
	if (!m_pMesh || !m_pParent) {
		return;
	}

	// Set the program
	glUseProgram(m_uiShaderProgram);

	// Obtain reference to the game object's transform
	Transform parentTransform = m_pParent->GetTransform();

	// Convert transform to relevant matrices
	glm::mat4 Translate = glm::translate(glm::mat4(), parentTransform.position);
	glm::mat4 RotationX = glm::rotate(glm::mat4(), parentTransform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 RotationY = glm::rotate(glm::mat4(), parentTransform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 RotationZ = glm::rotate(glm::mat4(), parentTransform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 Rotation = RotationZ * RotationY * RotationX;
	glm::mat4 Scale = glm::scale(glm::mat4(), parentTransform.scale);

	// Create model matrix
	glm::mat4 Model = Translate * Rotation * Scale;

	// Create Normal matrix - if lighting was being included, this calculation is best performed here, then sent to the vertex shader
	// glm::mat3 Normal = glm::mat3(glm::transpose(glm::inverse(Model)));

	// Create MVP matrix
	glm::mat4 MVP = _kpCamera->GetProjection() * _kpCamera->GetView() * Model;
	//glm::mat4 MVP = Model;

	// Send uniforms to shader
	glUniformMatrix4fv(5, 1, GL_FALSE, glm::value_ptr(MVP));	// 5 is the basic shader uniform location for the MVP matrix
	glUniform4fv(6, 1, glm::value_ptr(m_Colour));				// 6 is the location for the colour

	// Perform rendering
	glBindVertexArray(m_pMesh->GetVAO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pMesh->GetEBO());
	glDrawElements(GL_TRIANGLES, m_pMesh->GetIndices().size(), GL_UNSIGNED_INT, 0);//&m_pMesh->GetIndices()
	glBindVertexArray(0);

}

/*********
 * @Name:				SetMesh
 * @Description:		Assigns a mesh to the component
 * @Arguments:			EMeshType _eMeshType (the type of mesh to be assigned)
 * @Returns:			void
**********/
void MeshRenderer::SetMesh(EMeshType _eMeshType) {
	m_pMesh = Mesh::CreateMesh(_eMeshType);
}

/*********
 * @Name:				GetMesh
 * @Description:		Obtains the assigned mesh
 * @Arguments:			void
 * @Returns:			std::shared_ptr<Mesh> (m_pMesh)
**********/
std::shared_ptr<Mesh> MeshRenderer::GetMesh() const {
	return m_pMesh;
}

/*********
 * @Name:				SetShaderProgram
 * @Description:		Assigns a shader program based on a vertex and fragment shader
 * @Arguments:			std::string _strVertexShaderPath (vertex shader), std::string _strFragmentShaderPath (fragment shader)
 * @Returns:			void
**********/
void MeshRenderer::SetShaderProgram(std::string _strVertexShaderPath, std::string _strFragmentShaderPath) {
}

/*********
 * @Name:				SetColour
 * @Description:		Assigns a base colour to the MeshRenderer
 * @Arguments:			glm::vec4 _colour (the new colour to be assigned)
 * @Returns:			void
**********/
void MeshRenderer::SetColour(glm::vec4 _colour) {
	m_Colour = _colour;
}

void MeshRenderer::Update(float _fDeltaTick) {
	// Do things
}
