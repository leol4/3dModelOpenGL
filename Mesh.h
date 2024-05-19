#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>
#include<glm/glm.hpp>
#include<glad/glad.h>
#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"


class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	glm::mat4 objectModel; 
	bool isDynamic;
	// Store VAO in public so it can be used in the Draw function
	VAO VAO;
	GLuint vboID;
	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures, bool isDynamic = false);

	void rotateMesh(double time);

	void Inputs(GLFWwindow* window);
	// Draws the mesh
	void Draw(Shader& shader, Camera& camera);
};
#endif