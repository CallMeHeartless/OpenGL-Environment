/***********************
 * File:		Mesh.h
 * Description: Header file for the Mesh object
 * Author:		Kerry Pellett
 * Contact:		kerry.pellet@gmail.com
********************/
#ifndef __MESH_H__
#define __MESH_H__

// Library includes
#include <vector>
#include <memory>

// Local Includes
#include "Vertex.h"
#include "Dependencies/glew/glew.h"


enum EMeshType {
	eCircle = 0,
	eTriangle,
	eSquare,
	eHexagon,
	eMESHTYPE_COUNT
};

class Mesh {
	public:
		Mesh();
		~Mesh();

		// Factory method
		static std::shared_ptr<Mesh> CreateMesh(EMeshType _eMeshType);

		// Static storage clear
		static void ClearStaticMeshStorage();

		// Accessors & Mutators
		std::vector<Vertex>& GetVertices();
		std::vector<unsigned int>& GetIndices();
		GLuint GetVAO()const;
		GLuint GetVBO()const;
		GLuint GetEBO()const;

	private:
		// Render data
		std::vector<Vertex> m_vecVertices;
		std::vector<unsigned int> m_veciIndices;
		GLuint m_uiVAO;
		GLuint m_uiVBO;
		GLuint m_uiEBO;

		// Mesh storage data
		static std::vector<std::shared_ptr<Mesh>> s_vecpMeshes;

#pragma region INTERNAL_CONSTRUCTION_FUNCTIONS
		// Internal mesh creation methods
		void GenerateBuffers();

		static std::shared_ptr<Mesh> CreateCircleMesh();
		static std::shared_ptr<Mesh> CreateTriangleMesh();
		static std::shared_ptr<Mesh> CreateSquareMesh();
		static std::shared_ptr<Mesh> CreateHexagonMesh();
#pragma endregion

};

#endif // !__MESH_H__
