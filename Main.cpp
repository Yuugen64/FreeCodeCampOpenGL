#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
	//Initialize glfw so we can use its functions.
	glfwInit();

	//glfw doesnt know which version of glfw we are using, so we need to tell it via hints.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//an openGL profile is a set of functions. 2 types, 'core' (modern funcs), and 'compatability' (modern + older funcs).
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Coordinates for a vertex shader
	//We use openGL-float datatype because normal floats may differ in size causing errors.
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3.0f,
		-0.5f, -0.5f * float(sqrt(3)) / 3.0f,
		0.0f, 0.5 * float(sqrt(3)) * 2 / 3, 0.0f
	};





	//glfw window type
	GLFWwindow* window = glfwCreateWindow(800, 800, "FreeCodeCampOpenGL", NULL, NULL);

	//Attempting to create our vertex shader by referencing an openGL vertex shader
	//GLuint -> openGL unsigned integer, i.e. a positive integer using all 8 bits for values.
	//glCreateShader() is the call, GL_VERTEX_SHADER is the type of shader.
	GLuint myVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(myVertexShader, 1, &vertexShaderSource, NULL);
	//The graphics card can't understand our shader code however, so it must be compiled into MACHINE CODE right now.
	glCompileShader(myVertexShader);

	//Repeat for fragment shader
	GLuint myFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(myFragmentShader, 1, &fragmentShaderSource, NULL);
	//The graphics card can't understand our shader code however, so it must be compiled into MACHINE CODE right now.
	glCompileShader(myFragmentShader);

	//In order to use the shaders we need to "wrap" them into a shader program.
	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, myVertexShader);
	glAttachShader(shaderProgram, myFragmentShader);
	glLineWidth(shaderProgram);

	//We can delete our previous shaders because they're already in our shaderProgram.
	glDeleteShader(myVertexShader);
	glDeleteShader(myFragmentShader);



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