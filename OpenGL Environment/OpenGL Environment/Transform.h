#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

// Local Includes
#include "Dependencies/glm/glm.hpp"

struct Transform {
	glm::vec3 position;		// The position in world space, relative to the origin
	glm::vec3 rotation;		// The rotation of the object (in degrees)
	glm::vec3 scale;		// The scale of the object

	// Creates a transform with default values
	static Transform CreateDefaultTransform() {
		Transform transform;
		transform.position = glm::vec3(0.0f);
		transform.rotation = glm::vec3(0.0f);
		transform.scale = glm::vec3(1.0f);
		return transform;
	}

	// Performs basic translation
	void Translate(glm::vec3 _translation) {
		position += _translation;
	}
};

#endif // !__TRANSFORM_H__

