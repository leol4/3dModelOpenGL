#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
#include<glm/ext/matrix_transform.hpp>

class LightSource {
public:
	glm::vec4 Color;
	glm::vec3 Pos;
	glm::mat4 Model;
	float speed = 0.01f;
	
	LightSource() {
		Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		Pos = glm::vec3(0.0f, 0.5f, 0.0f);
		Model = glm::mat4(1.0f);
	}
	void Inputs(GLFWwindow* window);
};

#endif
