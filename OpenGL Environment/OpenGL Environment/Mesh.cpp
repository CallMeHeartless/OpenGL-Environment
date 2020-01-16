#include "Mesh.h"
#include <iostream>

std::vector<std::shared_ptr<Mesh>> Mesh::s_vecpMeshes;

Mesh::Mesh() {

	// Check to see if static mesh vector exists
	if (s_vecpMeshes.empty()) {
		// Initialise the vector with nullptrs
		s_vecpMeshes.resize(EMeshType::eMESHTYPE_COUNT-1, nullptr);
	}
}

Mesh::~Mesh() {
}

/*********
 * @Name:				Exit
 * @Description:		Handles the termination of the application
 * @Arguments:			void
 * @Returns:			void
**********/
std::shared_ptr<Mesh> Mesh::CreateMesh(EMeshType _eMeshType) {
	// Check if the argument could exist within the static vector of meshes
	if ((unsigned)_eMeshType < s_vecpMeshes.size() && _eMeshType >= 0 && !s_vecpMeshes.empty()) {
		// Check if that mesh has already been created
		if (s_vecpMeshes[_eMeshType]) {
			// Simply return that mesh
			return s_vecpMeshes[_eMeshType];
		}
	}
	
	// Switch based on the mesh type desired
	switch (_eMeshType) {
		// Create a circle mesh
		case EMeshType::eCircle:{
			return CreateCircleMesh();
			break;
		}

		// Create a triangle
		case EMeshType::eTriangle:{
			return CreateTriangleMesh();
			break;
		}

		// Create a square
		case EMeshType::eSquare:{
			return CreateSquareMesh();
			break;
		}

		// Create a hexagon
		case EMeshType::eHexagon:{
			return CreateHexagonMesh();
			break;
		}

		// Default case
		default:{
			break;
		}
	}

	return nullptr;
}

/*********
 * @Name:				Exit
 * @Description:		Handles the termination of the application
 * @Arguments:			void
 * @Returns:			void
**********/
void Mesh::ClearStaticMeshStorage() {
	s_vecpMeshes.clear();
}

/*********
 * @Name:				GetVertices
 * @Description:		Obtains the vertices of the mesh
 * @Arguments:			void
 * @Returns:			std::vector<Vertex>& (m_vecVertices)
**********/
std::vector<Vertex>& Mesh::GetVertices(){
	return m_vecVertices;
}

/*********
 * @Name:				GetIndices
 * @Description:		Obtains the indicies of the mesh
 * @Arguments:			void
 * @Returns:			std::vector<unsigned int>& (m_veciIndices)
**********/
std::vector<unsigned int>& Mesh::GetIndices() {
	return m_veciIndices;
}

/*********
 * @Name:				GetVAO
 * @Description:		Obtains the vertex array object
 * @Arguments:			void
 * @Returns:			GLuint (m_VAO)
**********/
GLuint Mesh::GetVAO() const {
	return m_uiVAO;
}

/*********
 * @Name:				GetVBO
 * @Description:		Obtains the vertex buffer object
 * @Arguments:			void
 * @Returns:			GLuint (m_VBO)
**********/
GLuint Mesh::GetVBO() const {
	return m_uiVBO;
}

/*********
 * @Name:				GetEBO
 * @Description:		Obtains the element buffer object
 * @Arguments:			void
 * @Returns:			GLuint (m_EBO)
**********/
GLuint Mesh::GetEBO() const {
	return m_uiEBO;
}

/*********
 * @Name:				GenerateBuffers
 * @Description:		Constructs the vertex array, vertex buffer, and element buffer objects
 * @Arguments:			void
 * @Returns:			void
**********/
void Mesh::GenerateBuffers() {
	// Create Vertex Array
	glGenVertexArrays(1, &m_uiVAO);
	glBindVertexArray(m_uiVAO);

	// Create Vertex Buffer
	glGenBuffers(1, &m_uiVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vecVertices.size(), &m_vecVertices[0], GL_STATIC_DRAW);

	// Create Element Buffer
	glGenBuffers(1, &m_uiEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_veciIndices.size(), &m_veciIndices[0], GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); // Positional information
	glEnableVertexAttribArray(0);

	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));
	glEnableVertexAttribArray(1);

	// UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2*sizeof(glm::vec3)));
	glEnableVertexAttribArray(2);
}

/*********
 * @Name:				CreateCircleMesh
 * @Description:		Constructs the vertices, indices, and buffer objects for a 2D circle mesh
 * @Arguments:			void
 * @Returns:			void
**********/
std::shared_ptr<Mesh> Mesh::CreateCircleMesh() {
	// Create a new mesh
	std::shared_ptr<Mesh> pCircle = std::make_shared<Mesh>();

	// Create vertices
	pCircle->m_vecVertices.push_back({ glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 0.5f) }); // Center
	
	for (unsigned int i = 0; i < 360; ++i) {
		float fAngle = glm::radians(static_cast<float>(i));
		pCircle->m_vecVertices.push_back({ 0.5f * glm::vec3(glm::cos(fAngle), glm::sin(fAngle), 0.0f), 
												  glm::vec3(0.0f, 0.0f, 1.0f), 
												  glm::vec2(0.5f * glm::cos(fAngle) + 0.5f, 0.5f * glm::sin(fAngle) + 0.5f) });
	}

	// Set Indices
	for (unsigned int i = 1; i < 360; ++i) {
		pCircle->m_veciIndices.push_back(0);
		pCircle->m_veciIndices.push_back(i);
		pCircle->m_veciIndices.push_back(i+1);
	}
	pCircle->m_veciIndices.back() = 1;

	// Create buffers
	pCircle->GenerateBuffers();

	return pCircle;
}

/*********
 * @Name:				CreateTriangleMesh
 * @Description:		Constructs the vertices, indices, and buffer objects for a 2D triangle mesh
 * @Arguments:			void
 * @Returns:			void
**********/
std::shared_ptr<Mesh> Mesh::CreateTriangleMesh() {
	// Create a new mesh for the triangle
	std::shared_ptr<Mesh> pTriangle = std::make_shared<Mesh>();

	// Set the vertices
	pTriangle->m_vecVertices.push_back({ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) });
	pTriangle->m_vecVertices.push_back({ glm::vec3(0.0f, 0.5f, 0.0f),	glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f) });
	pTriangle->m_vecVertices.push_back({ glm::vec3(0.5f, -0.5f, 0.0f),	glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f) });

	// Set the indices
	pTriangle->m_veciIndices.push_back(0);
	pTriangle->m_veciIndices.push_back(2);
	pTriangle->m_veciIndices.push_back(1);

	// Generate vertex buffers
	pTriangle->GenerateBuffers();

	return pTriangle;
}

/*********
 * @Name:				CreateSquareMesh
 * @Description:		Constructs the vertices, indices, and buffer objects for a 2D square mesh
 * @Arguments:			void
 * @Returns:			void
**********/
std::shared_ptr<Mesh> Mesh::CreateSquareMesh() {
	// Create a new mesh for the square
	std::shared_ptr<Mesh> pSquare = std::make_shared<Mesh>();

	// Set vertices
	pSquare->m_vecVertices.push_back({ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) });
	pSquare->m_vecVertices.push_back({ glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f) });
	pSquare->m_vecVertices.push_back({ glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) });
	pSquare->m_vecVertices.push_back({ glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f) });

	// Set indices
	pSquare->m_veciIndices.push_back(0);
	pSquare->m_veciIndices.push_back(2);
	pSquare->m_veciIndices.push_back(1);

	pSquare->m_veciIndices.push_back(0);
	pSquare->m_veciIndices.push_back(3);
	pSquare->m_veciIndices.push_back(2);

	// Generate buffers
	pSquare->GenerateBuffers();
	
	return pSquare;
}

/*********
 * @Name:				CreateHexagonMesh
 * @Description:		Constructs the vertices, indices, and buffer objects for a 2D hexagonal mesh
 * @Arguments:			void
 * @Returns:			void
**********/
std::shared_ptr<Mesh> Mesh::CreateHexagonMesh() {
	// Create a new mesh for the hexagon
	std::shared_ptr<Mesh> pHexagon = std::make_shared<Mesh>();

	// Set vertices
	pHexagon->m_vecVertices.push_back({ glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 0.5f) }); // Center
	float fAngleIncrement = 360.0f / 6.0f;
	float fAngle = 0.0f;
	for (unsigned int i = 0; i < 6; ++i) {
		// Find the angle
		fAngle = glm::radians(fAngleIncrement * static_cast<float>(i));
		pHexagon->m_vecVertices.push_back({0.5f * glm::vec3(glm::cos(fAngle), glm::sin(fAngle), 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2() });
	}

	// Manually assign UVs
	pHexagon->m_vecVertices[1].UV = glm::vec2(1.0f, 0.5f);
	pHexagon->m_vecVertices[2].UV = glm::vec2(0.75f, 1.0f);
	pHexagon->m_vecVertices[3].UV = glm::vec2(0.25f, 1.0f);
	pHexagon->m_vecVertices[4].UV = glm::vec2(0.0f, 0.5f);
	pHexagon->m_vecVertices[5].UV = glm::vec2(0.25f, 0.25f);
	pHexagon->m_vecVertices[6].UV = glm::vec2(0.75f, 0.25f);

	// Set indices
	pHexagon->m_veciIndices.push_back(0);
	pHexagon->m_veciIndices.push_back(1);
	pHexagon->m_veciIndices.push_back(2);

	pHexagon->m_veciIndices.push_back(0);
	pHexagon->m_veciIndices.push_back(2);
	pHexagon->m_veciIndices.push_back(3);

	pHexagon->m_veciIndices.push_back(0);
	pHexagon->m_veciIndices.push_back(3);
	pHexagon->m_veciIndices.push_back(4);

	pHexagon->m_veciIndices.push_back(0);
	pHexagon->m_veciIndices.push_back(4);
	pHexagon->m_veciIndices.push_back(5);

	pHexagon->m_veciIndices.push_back(0);
	pHexagon->m_veciIndices.push_back(5);
	pHexagon->m_veciIndices.push_back(6);

	pHexagon->m_veciIndices.push_back(0);
	pHexagon->m_veciIndices.push_back(6);
	pHexagon->m_veciIndices.push_back(1);

	// Generate buffers
	pHexagon->GenerateBuffers();

	return pHexagon;
}
