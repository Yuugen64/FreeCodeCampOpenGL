#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"


// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};



int main()
{
	//Initialize glfw so we can use its functions.
	if (!glfwInit())
	{
		std::cout << "Error initializing GLFW." << std::endl;
	}
	else
	{
		std::cout << "Initialized GLFW." << std::endl;
	}

	//glfw doesnt know which version of glfw we are using, so we need to tell it via hints.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//an openGL profile is a set of functions. 2 types, 'core' (modern funcs), and 'compatability' (modern + older funcs).
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	





	//glfw window type
	GLFWwindow* window = glfwCreateWindow(800, 800, "FreeCodeCampOpenGL", NULL, NULL);

	//Error checking in case window fails to create.
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Tell the openGL context that we want to use the window.
	glfwMakeContextCurrent(window);

	//Using GLAD and loading needed configs for OpenGL
	gladLoadGL();

	//Define what part of the viewport OpenGL should render in.
	glViewport(0, 0, 800, 800);

	//Add our two shaders defined externally to our shaderProgram so we can use them.
	Shader shaderProgram("default.vert", "default.frag");


	//Create a Vertex Array Object
	VAO VAO1;
	VAO1.Bind();

	//Generates a Vertex Buffer Object and links it to vertices[]
	VBO VBO1(vertices, sizeof(vertices));
	//Generates a Element Buffer Object and links it to indices[]
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	



	//Main WHILE loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		//Make sure to swap buffers so the vertices are actually drawn to the frame.
		glfwSwapBuffers(window);

		//Take care of all GLFW events
		glfwPollEvents();
	}

	//Terminate out VAO(s), VBO(s), and shaderProgram before the program ends.
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	//Terminate the glfw window before the program ends.
	glfwDestroyWindow(window);
	//Terminate GLFW before the program ends.
	glfwTerminate();
	return 0;
}