#include"Lightsource.h"

void LightSource::Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			Pos += speed * glm::vec3(1.0f, 0.0f, 0.0f);
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			Pos += speed * glm::vec3(0.0f, 0.0f, -1.0f);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			Pos += speed * glm::vec3(-1.0f, 0.0f, 0.0f);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			Pos += speed * glm::vec3(0.0f, 0.0f, 1.0f);
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			Pos += speed * glm::vec3(0.0f, 1.0f, 0.0f);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			Pos += speed * glm::vec3(0.0f, -1.0f, 0.0f);
		}
		//Model = glm::translate(Model, Pos);
	}
}