/***********************
 * File:		ShaderLoader.h
 * Description: Header file for the ShaderLoader class
 * Author:		Kerry Pellett
 * Contact:		kerry.pellet@gmail.com
********************/
#ifndef __SHADERLOADER_H__
#define __SHADERLOADER_H__

#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
#include <iostream>
#include <map>

class ShaderLoader {
private:

	std::string ReadShader(const char *filename);
	GLuint CreateShader(GLenum shaderType,
		std::string source,
		const char* shaderName);
	std::map<std::pair<std::string, std::string>, GLuint> m_ShaderMap;
	std::map<std::string, GLuint> m_VertexMap, m_FragmentMap, m_GeometryMap, m_TessControlMap, m_TessEvalMap, m_ComputeMap;

public:
	ShaderLoader(void);
	~ShaderLoader(void);
	GLuint CreateProgram(const char* VertexShaderFilename,
		const char* FragmentShaderFilename);
	GLuint CreateProgram(const char* VertexShaderFilename, const char* GeometryShaderFilename,
		const char* FragmentShaderFilename);
	GLuint CreateProgram(const char* VertexShaderFilename, const char* TessellationControlShader,
		const char* TessellationEvalShader, const char* FragmentShaderFilename);
	GLuint CreateProgram(const char* ComputeShaderFilename);

};


#endif // !__SHADERLOADER_H__


