#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	//Initialize glfw so we can use its functions.
	glfwInit();

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

	//Render a color to our window.
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	//Define what part of the viewport OpenGL should render in.
	glViewport(0, 0, 800, 800);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}




	//Terminate the glfw window before the program ends.
	glfwDestroyWindow(window);
	//End glfw
	glfwTerminate();
	return 0;
}