#include "shaderClass.h"


//Read in data from text files.
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		//define what our contents are to be read in
		std::string contents;

		//Go to end of file.
		in.seekg(0, std::ios::end);

		//Resize the size of the contents to end of file length.
		contents.resize(in.tellg());

		//Go back to beginning of file.
		in.seekg(0, std::ios::beg);

		//Read in contents from 0 to size (we just defined)
		in.read(&contents[0], contents.size());

		//close input and return.
		in.close();
		return(contents);
	}
	throw(errno);
}


//Shader constructor.
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//Get strings from text files into variables
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//Convert those strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//Attempting to create our vertex shader by referencing an openGL vertex shader
	//GLuint -> openGL unsigned integer, i.e. a positive integer using all 8 bits for values.
	//glCreateShader() is the call, GL_VERTEX_SHADER is the type of shader.
	GLuint myVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(myVertexShader, 1, &vertexSource, NULL);
	//The graphics card can't understand our shader code however, so it must be compiled into MACHINE CODE right now.
	glCompileShader(myVertexShader);

	//Repeat for fragment shader
	GLuint myFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(myFragmentShader, 1, &fragmentSource, NULL);
	//The graphics card can't understand our shader code however, so it must be compiled into MACHINE CODE right now.
	glCompileShader(myFragmentShader);

	//In order to use the shaders we need to "wrap" them into a shader program.
	ID = glCreateProgram();

	glAttachShader(ID, myVertexShader);
	glAttachShader(ID, myFragmentShader);
	glLinkProgram(ID);

	//We can delete our previous shaders because they're already in our shaderProgram.
	glDeleteShader(myVertexShader);
	glDeleteShader(myFragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glUseProgram(ID);
}

// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}