#include "ShaderLoader.h" 
#include<iostream>
#include<fstream>
#include<vector>

ShaderLoader::ShaderLoader(void){}
ShaderLoader::~ShaderLoader(void){}


std::string ShaderLoader::ReadShader(const char *filename)
{
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);

	if (!file.good()){
		std::cout << "Can't read file " << filename << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint ShaderLoader::CreateShader(GLenum shaderType, std::string
	source, const char* shaderName)
{
	// Check based on shader type
	switch (shaderType) {
	case GL_VERTEX_SHADER: {
		// Check through vertex shader map
		if (shaderName == "vertex shader") {
			if (m_VertexMap.size() != 0) {
				auto mapIterator = m_VertexMap.begin();
				while (mapIterator != m_VertexMap.end()) {
					if ((*mapIterator).first == source) {
						//std::cout << "Shader found" << std::endl;
						return (*mapIterator).second;
					}
					++mapIterator;
				}
			}
		}
		break;
	}

	case GL_FRAGMENT_SHADER: {
		if (m_FragmentMap.size() != 0) {
			auto mapIterator = m_FragmentMap.begin();
			while (mapIterator != m_FragmentMap.end()) {
				if ((*mapIterator).first == source) {
					return (*mapIterator).second;
				}
				++mapIterator;
			}
		}
		break;
	}

	case GL_GEOMETRY_SHADER: {
		if (m_GeometryMap.size() != 0) {
			auto mapIterator = m_GeometryMap.begin();
			while (mapIterator != m_GeometryMap.end()) {
				if ((*mapIterator).first == source) {
					return (*mapIterator).second;
				}
				++mapIterator;
			}
		}
		break;
	}

	case GL_TESS_CONTROL_SHADER: {
		if (m_TessControlMap.size() != 0) {
			auto mapIterator = m_TessControlMap.begin();
			while (mapIterator != m_TessControlMap.end()) {
				if ((*mapIterator).first == source) {
					return (*mapIterator).second;
				}
				++mapIterator;
			}
		}
		break;
	}

	case GL_TESS_EVALUATION_SHADER: {
		if (m_TessEvalMap.size() != 0) {
			auto mapIterator = m_TessEvalMap.begin();
			while (mapIterator != m_TessEvalMap.end()) {
				if ((*mapIterator).first == source) {
					return (*mapIterator).second;
				}
				++mapIterator;
			}
		}
		break;
	}

	case GL_COMPUTE_SHADER: {
		if (m_ComputeMap.size() != 0) {
			auto mapIterator = m_ComputeMap.begin();
			while (mapIterator != m_ComputeMap.end()) {
				if ((*mapIterator).first == source) {
					return (*mapIterator).second;
				}
				++mapIterator;
			}
		}
		break;
	}

	default:break;
	}

	int compile_result = 0;

	GLuint shader = glCreateShader(shaderType);
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	//check for errors
	if (compile_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shaderName << std::endl << &shader_log[0] << std::endl;
		return 0;
	}

	auto shaderPair = make_pair(source, shader);

	switch (shaderType) {
	case GL_VERTEX_SHADER: {
		m_VertexMap.insert(shaderPair);
		break;
	}

	case GL_FRAGMENT_SHADER: {
		m_FragmentMap.insert(shaderPair);
		break;
	}

	case GL_GEOMETRY_SHADER: {
		m_GeometryMap.insert(shaderPair);
		break;
	}

	case GL_TESS_CONTROL_SHADER: {
		m_TessControlMap.insert(shaderPair);
		break;
	}

	case GL_TESS_EVALUATION_SHADER: {
		m_TessEvalMap.insert(shaderPair);
		break;
	}
	case GL_COMPUTE_SHADER: {
		m_ComputeMap.insert(shaderPair);
		break;
	}

	default:break;
	}

	return shader;
}
GLuint ShaderLoader::CreateProgram(const char* vertexShaderFilename,
	const char* fragmentShaderFilename)
{

	//read the shader files and save the code
	std::string vertex_shader_code = ReadShader(vertexShaderFilename);
	std::string fragment_shader_code = ReadShader(fragmentShaderFilename);

	auto shaderPair = std::make_pair(std::string(vertex_shader_code), std::string(fragment_shader_code));

	if (m_ShaderMap.size() != 0) {
		auto spIterator = m_ShaderMap.begin();
		while (spIterator != m_ShaderMap.end()) {
			if ((*spIterator).first == shaderPair) {
				return (*spIterator).second;
			}
			++spIterator;
		}
	}
	

	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	int link_result = 0;
	//create the program handle, attatch the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	//check for link errors
	if (link_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		return 0;
	}

	auto key = std::make_pair(shaderPair, program);
	m_ShaderMap.insert(key);
	//std::cout << "Program key added to map" << std::endl;

	return program;
}

GLuint ShaderLoader::CreateProgram(const char* vertexShaderFilename, const char* geometryShaderFilename,
	const char* fragmentShaderFilename)
{

	//read the shader files and save the code
	std::string vertex_shader_code = ReadShader(vertexShaderFilename);
	std::string geometry_shader_code = ReadShader(geometryShaderFilename);
	std::string fragment_shader_code = ReadShader(fragmentShaderFilename);

	//auto shaderPair = std::make_pair(std::string(vertex_shader_code), std::string(fragment_shader_code));

	//if (m_ShaderMap.size() != 0) {
	//	auto spIterator = m_ShaderMap.begin();
	//	while (spIterator != m_ShaderMap.end()) {
	//		if ((*spIterator).first == shaderPair) {
	//			return (*spIterator).second;
	//		}
	//		++spIterator;
	//	}
	//}
	//

	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint geometry_shader = CreateShader(GL_GEOMETRY_SHADER, geometry_shader_code, "geometry shader");
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	int link_result = 0;
	//create the program handle, attatch the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, geometry_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	//check for link errors
	if (link_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		return 0;
	}

	//auto key = std::make_pair(shaderPair, program);
	//m_ShaderMap.insert(key);
	//std::cout << "Program key added to map" << std::endl;

	return program;
}

GLuint ShaderLoader::CreateProgram(const char* vertexShaderFilename, const char* TessellationControlShaderFilename,
	const char* TessellationEvalShaderFilename, const char* fragmentShaderFilename)
{

	//read the shader files and save the code
	std::string vertex_shader_code = ReadShader(vertexShaderFilename);
	std::string control_shader_code = ReadShader(TessellationControlShaderFilename);
	std::string eval_shader_code = ReadShader(TessellationEvalShaderFilename);
	std::string fragment_shader_code = ReadShader(fragmentShaderFilename);

	//auto shaderPair = std::make_pair(std::string(vertex_shader_code), std::string(fragment_shader_code));

	//if (m_ShaderMap.size() != 0) {
	//	auto spIterator = m_ShaderMap.begin();
	//	while (spIterator != m_ShaderMap.end()) {
	//		if ((*spIterator).first == shaderPair) {
	//			return (*spIterator).second;
	//		}
	//		++spIterator;
	//	}
	//}
	//

	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint tess_control_shader = CreateShader(GL_TESS_CONTROL_SHADER, control_shader_code, "tess control shader");
	GLuint tess_eval_shader = CreateShader(GL_TESS_EVALUATION_SHADER, eval_shader_code, "tess eval shader");
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	int link_result = 0;
	//create the program handle, attatch the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, tess_control_shader);
	glAttachShader(program, tess_eval_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	//check for link errors
	if (link_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		return 0;
	}

	//auto key = std::make_pair(shaderPair, program);
	//m_ShaderMap.insert(key);
	//std::cout << "Program key added to map" << std::endl;

	return program;
}

GLuint ShaderLoader::CreateProgram(const char* computeShaderFileName)
{
	//read the shader files and save the code
	std::string compute_shader_code = ReadShader(computeShaderFileName);

	GLuint compute_shader = CreateShader(GL_COMPUTE_SHADER, compute_shader_code, "compute shader");

	int link_result = 0;
	//create the program handle, attatch the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, compute_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	//check for link errors
	if (link_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		return 0;
	}

	//auto key = std::make_pair(shaderPair, program);
	//m_ShaderMap.insert(key);
	//std::cout << "Program key added to map" << std::endl;

	return program;
}