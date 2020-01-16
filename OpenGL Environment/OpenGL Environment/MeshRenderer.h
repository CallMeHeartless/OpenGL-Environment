/***********************
 * File:		MeshRenderer.h
 * Description: Header file for the MeshRenderer component
 * Author:		Kerry Pellett
 * Contact:		kerry.pellet@gmail.com
********************/
#ifndef __MESHRENDERER_H__
#define __MESHRENDERER_H__

// Local Includes
#include "Component.h"
#include "Mesh.h"

// Forward Declaration
class Camera;
class ShaderLoader;

class MeshRenderer : public Component {
	public:
		MeshRenderer();
		~MeshRenderer();

		void Update(float _fDeltaTick);

		void Render(std::unique_ptr<Camera>& _kpCamera);

		void SetMesh(EMeshType _eMeshType);
		std::shared_ptr<Mesh> GetMesh()const;
		void SetShaderProgram(std::string _strVertexShaderPath, std::string _strFragmentShaderPath);
		void SetColour(glm::vec4 _colour);

	protected:
		std::shared_ptr<Mesh> m_pMesh;
		GLuint m_uiShaderProgram;
		glm::vec4 m_Colour = glm::vec4(1.0f); // Set default colour to white

		// Class wide shader loader
		static std::shared_ptr<ShaderLoader> s_pShaderLoader;
			   
};

#endif // !__MESHRENDERER_H__

