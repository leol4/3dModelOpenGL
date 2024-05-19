#include "Mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures, bool isDynamic)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;
	Mesh::isDynamic = isDynamic;

	objectModel = glm::mat4(1.f);
	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	objectModel = glm::translate(objectModel, objectPos);

	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO(vertices, Mesh::isDynamic);

	vboID = VBO.ID;
	// Generates Element Buffer Object and links it to indices
	EBO EBO(indices);
	// Links VBO attributes such as coordinates and colors to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)(0 * sizeof(float))); // coords
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float))); // colors
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float))); // normals
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float))); // tex UV
	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}


void Mesh::Draw(Shader& shader, Camera& camera)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	VAO.Bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}
	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	// Draw the actual mesh
	if (Mesh::isDynamic) {
		// dynamic vbo
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, indices.size(), indices.data());
	}
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			objectModel = glm::translate(objectModel, glm::vec3(0.0f, 0.0f, 0.005f));
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			objectModel = glm::translate(objectModel, glm::vec3(0.005f, 0.0f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			objectModel = glm::translate(objectModel, glm::vec3(0.0f, 0.0f, -0.005f));
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			objectModel = glm::translate(objectModel, glm::vec3(-0.005f, 0.0f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			objectModel = glm::translate(objectModel, glm::vec3(0.0f, 0.005f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			objectModel = glm::translate(objectModel, glm::vec3(0.0f, -0.005f, 0.0f));
		}
	}
}

void Mesh::rotateMesh(double time) {
	if (time < 2.5) {
		objectModel = glm::translate(objectModel, glm::vec3(0.005f, 0.0f, 0.0f));
		objectModel = glm::translate(objectModel, glm::vec3(0.0f, 0.005f, 0.0f));
	}
	else if (time < 5) {
		objectModel = glm::translate(objectModel, glm::vec3(-0.005f, 0.0f, 0.0f));
		objectModel = glm::translate(objectModel, glm::vec3(0.0f, 0.005f, 0.0f));
	}
	else if (time < 7.5) {
		objectModel = glm::translate(objectModel, glm::vec3(-0.005f, 0.0f, 0.0f));
		objectModel = glm::translate(objectModel, glm::vec3(0.0f, -0.005f, 0.0f));
	}
	else {
		objectModel = glm::translate(objectModel, glm::vec3(0.005f, 0.0f, 0.0f));
		objectModel = glm::translate(objectModel, glm::vec3(0.0f, -0.005f, 0.0f));
	}
}