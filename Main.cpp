#include"Mesh.h"
#include"Lightsource.h"
#include <chrono>
#include "Render.h"

const unsigned int width = 1600;
const unsigned int height = 900;



// Vertices coordinates
Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)}
};


// Vertices coordinates
Vertex vertices1[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(1.0f, -1.0f,  -2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 1.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 8.0f)},
	Vertex{glm::vec3(-1.0f, 1.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(8.0f, 8.0f)},
	Vertex{glm::vec3(-1.0f, -1.0f,  -2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(8.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.01f, -0.01f,  0.01f)},
	Vertex{glm::vec3(-0.01f, -0.01f, -0.01f)},
	Vertex{glm::vec3(0.01f, -0.01f, -0.01f)},
	Vertex{glm::vec3(0.01f, -0.01f,  0.01f)},
	Vertex{glm::vec3(-0.01f,  0.01f,  0.01f)},
	Vertex{glm::vec3(-0.01f,  0.01f, -0.01f)},
	Vertex{glm::vec3(0.01f,  0.01f, -0.01f)},
	Vertex{glm::vec3(0.01f,  0.01f,  0.01f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	

	Texture textures[]
	{
		Texture("texture.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("textureSpec.png", "specular", 1, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	Texture textures1[]
	{
		Texture("texture1.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("texture1Spec.png", "specular", 1, GL_RGBA, GL_UNSIGNED_BYTE)
	};



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	Shader shaderProgram1("default.vert", "default.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <Vertex> verts1(vertices1, vertices1 + sizeof(vertices1) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	std::vector <Texture> tex1(textures1, textures1 + sizeof(textures1) / sizeof(Texture));
	// Create floor mesh
	Mesh floor(verts, ind, tex);
	Mesh floor1(verts1, ind, tex);


	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	// Create light mesh
	Mesh light(lightVerts, lightInd, tex);



	LightSource lightsource;
	lightsource.Model = glm::translate(lightsource.Model, lightsource.Pos);

	shaderProgram.Activate();
	//shaderprog
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(floor.objectModel));
	glUseProgram(0);



	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 1.0f, 2.0f));
	float type = 0;
	bool isPressed = false;
	auto start = std::chrono::high_resolution_clock::now();
	auto current = start;
	double delta_time;
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		current = std::chrono::high_resolution_clock::now();
		delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(current - start).count();
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !isPressed)
		{
			isPressed = true;
			type += 1.0f;
			if (type >= 3)
				type = 0.0f;
			lightsource.Pos = glm::vec3(0.0f, 0.5f, 0.0f);
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE && isPressed)
		{
			isPressed = false;
		}

		lightsource.Model = glm::translate(lightsource.Model, lightsource.Pos);

		lightShader.Activate();
		//lightshader
		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightsource.Model));
		glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightsource.Color.x, lightsource.Color.y, lightsource.Color.z, lightsource.Color.w);


		shaderProgram.Activate();
		//shaderprog
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(floor.objectModel));
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightsource.Color.x, lightsource.Color.y, lightsource.Color.z, lightsource.Color.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightsource.Pos.x, lightsource.Pos.y, lightsource.Pos.z);
		glUniform1f(glGetUniformLocation(shaderProgram.ID, "type"), type);


		shaderProgram1.Activate();
		//shaderprog
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(floor1.objectModel));
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightsource.Color.x, lightsource.Color.y, lightsource.Color.z, lightsource.Color.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightsource.Pos.x, lightsource.Pos.y, lightsource.Pos.z);
		glUniform1f(glGetUniformLocation(shaderProgram.ID, "type"), type);


		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Handles camera inputs
		camera.Inputs(window);
		floor.Inputs(window);
		lightsource.Inputs(window);

		// render, but not working
		Render(delta_time);
		// Get rotated
		floor1.rotateMesh(delta_time);

		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);


		// Draws different meshes
		floor.Draw(shaderProgram, camera);
		floor1.Draw(shaderProgram1, camera);
		light.Draw(lightShader, camera);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	shaderProgram.Delete();
	shaderProgram1.Delete();
	lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
