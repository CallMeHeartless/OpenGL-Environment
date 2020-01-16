#ifndef __VERTEX_H__
#define __VERTEX_H__

// Local Includes
#include "Dependencies/glm/glm.hpp"

struct Vertex {
	glm::vec3 position; // The vertex position in normalised device coordinates
	glm::vec3 normal;	// The normal vector of the vertex
	glm::vec2 UV;		// The texture coordinates of the vertex
};

#endif // !__VERTEX_H__
