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

	/*
	//Render a color to our window.
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
	*/

	//Define what part of the viewport OpenGL should render in.
	glViewport(0, 0, 800, 800);


	



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
	glLinkProgram(shaderProgram);

	//We can delete our previous shaders because they're already in our shaderProgram.
	glDeleteShader(myVertexShader);
	glDeleteShader(myFragmentShader);



	//Coordinates for a vertex shader
	//We use openGL-float datatype because normal floats may differ in size causing errors.
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //Upper Corner

		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //Inner Left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f //Inner bottom
	};
	
	//This is our index buffer, so we can simply reuse indices
	GLuint indices[] =
	{
		0, 3, 5, //Lower left triangle
		3, 2, 4, //Lower right triangle
		5, 4, 1 //Upper triangle
	};



	//Vertex buffer objects are large sets of data passed between the CPU and GPU (since that communication is quite expensive and slow).
	//Vertex array objects tell openGL how to use vertex buffer objects.

	//Initialize a vertex array object, a vertex buffer object, and an index buffer object.
	GLuint VAO, VBO, EBO;

	//We only have one of each currently currently:

	//*****The VAO MUST be generated BEFORE the VBO.
	glGenVertexArrays(1, &VAO);

	//Generate the Vertex Buffer Object
	glGenBuffers(1, &VBO);

	//Generate Index Buffer
	glGenBuffers(1, &EBO);

	//Make the VAO the current Vertex Array Object by binding it.
	glBindVertexArray(VAO);



	//bind our vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//^All of this results in a nicely packed object with our vertex data.

	//Make the index buffer current via binding
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Tells openGL how to interpret our vertices (how many, what type, how big are they, and some other things).
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Bind our vertex array to 0 so it can't be modified by a function call.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//*****The Index buffer is contained WITHIN the VAO, so you have to bind it AFTER the VAO otherwise you are telling openGL that you don't want to use the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	



	

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES,9, GL_UNSIGNED_INT, 0);

		//Make sure to swap buffers so the vertices are actually drawn to the frame.
		glfwSwapBuffers(window);

		//Take care of all GLFW events
		glfwPollEvents();
	}

	//Terminate out VAO(s), VBO(s), and shaderProgram before the program ends.
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	//Terminate the glfw window before the program ends.
	glfwDestroyWindow(window);
	//Terminate GLFW before the program ends.
	glfwTerminate();
	return 0;
}