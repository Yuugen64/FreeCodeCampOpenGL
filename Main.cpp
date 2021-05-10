#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Texture.h"
#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"


// Vertices coordinates
GLfloat vertices[] =
{ //               COORDINATES                  /     COLORS  (RGB)         //       TEXTURE
	-0.5f, -0.5f, 0.0f,								1.0f, 0.0f, 0.0f,			0.0f, 0.0f,//Lower left corner RED
	-0.5f, 0.5f, 0.0f,								0.0f, 1.0f, 0.0f,			0.0f, 1.0f,//Upper left corner GREEN
	0.5f, 0.5f, 0.0f,								0.0f, 0.0f, 1.0f,			1.0f, 1.0f,//Upper right corner BLUE
	0.5f, -0.5f, 0.0f,								1.0f, 1.0f, 1.0f,			1.0f, 0.0f//Lower right corner WHITE
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, //Upper triangle
	0, 2, 3  //Lower triangle
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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	//Texture
	Texture vaporwave("vaporwave.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	vaporwave.texUnit(shaderProgram, "tex0", 0);



	//Main WHILE loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();

		//Where we control the 'scale' Uniform for our triangles.
		//This HAS to be used AFTER our shader program is activated since the shaderProgram handles it.
		glUniform1f(uniID, 0);
		vaporwave.Bind();

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
	vaporwave.Delete();
	shaderProgram.Delete();

	//Terminate the glfw window before the program ends.
	glfwDestroyWindow(window);
	//Terminate GLFW before the program ends.
	glfwTerminate();
	return 0;
}