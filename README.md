# FreeCodeCampOpenGL

5.2.21
- Redownloaded Visual Studio Community 2019.
- Downloaded CMake (quite excited for this bit since it seems to be one of the recommended ways to create modern C++ programs).
- Downloaded GLFW to help with creating openGL windows (I believe its also cross platform).
- Followed along to set up the project in VS 2019 (The most difficult thing of all honestly).
- Downloaded GLAD 'core' version 3.3, and added the 'glad.c' file to the main project (as a source file).
- Added the 'glad' folder to my 'include' project folder.
- Also added the GLFW and KHR folders to my 'include' folder.
- Added the glfw3.lib to my 'lib' folder.
- Initialized and pushed to a new repository on Github called 'FreeCodeCampOpenGL'. (It took two pushes for the repo to appear in my Github.com account??).

- Initialized GLFW with: glfwInit();
```
glfwInit();
```

- Told GLFW which version we would like to use via Hints.
```
//glfw doesnt know which version of glfw we are using, so we need to tell it via hints.
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
```
  
- Set openGL to use the correct 'core' profile.
```
//an openGL profile is a set of functions. 2 types, 'core' (modern funcs), and 'compatability' (modern + older funcs).
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```
  
- Initialized a GLFW window.
```
GLFWwindow* window = glfwCreateWindow(800, 800, "FreeCodeCampOpenGL", NULL, NULL);
```
  
- Did some minor error checking in case the window failed to load (which actually saved me because I had made an error by using two GLFW_CONTEXT_VERSION_MAJOR in the above hints section).
```
if (window == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
```
  
- Made the window the current context (we want to actually use the window).
```
glfwMakeContextCurrent(window);
```
  
- Corrected previously mentioned hints mistake.
- Got a GLFW Window working!
- Started using GLAD, told it to load needed configs for OpenGL
```
gladLoadGL();
```
  
- Learned how to define what part of the viewport openGL should RENDER to.
(Also learned that (0,0) is the BOTTOM RIGHT corner, and (800,800) is the TOP LEFT corner of the window
```
glViewport(0, 0, 800, 800);
```
  
- Learned the concept of buffers, and that frames are loaded in the background and then swapped out with the displayed frame. (Buffers are places in memory for pixels). 
- Learned that the FRONT BUFFER is the buffer being displayed on the screen.
- Learned that the BACK BUFFER is the buffer where the information is currently being written.
- Got a color to appear in the window!
```
glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);
glfwSwapBuffers(window);
```
  
- Learned about the Graphics Pipeline.
- The input for the Graphics Pipeline is an array of Vertex Data[]. These vertices are NOT mathematical vertices becasue they contain data for position and other things like color.
- Learned the overall flow of the Graphics Pipeline:
1. VERTEX SHADER: Gets the vertex position data)
2. SHAPE ASSEMBLY: Creates a primitive line, or shape based on the vertext data.
3. GEOMETRY SHADER: Adds vertices and creates new primatives out of already existing primatives.
4. RASTERIZATION: Perfect mathematical shapes become pixels.
5. FRAGMENT SHADER: Adds colors to the pixels (very important shader; includes lighting, shadows, etc).
6. TESTS AND BLENDING: Figures out which pixel to actually show since pixels may be overlapping.
- Learned that OpenGL doesn't provide defaults for vertex and fragment shaders.
- Learned that vertices range from -1 to 1 for the X-axis and Y-axis.
- ALL OPENGL Objects are utilized via REFERENCES.
- Used boilerplate vertex and fragment shader code just to make things a little easier at this point.
```
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
```
- Learned how to create an array of vertices:
```
//Coordinates for a vertex shader
//We use openGL-float datatype because normal floats may differ in size causing errors.
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3.0f,
	-0.5f, -0.5f * float(sqrt(3)) / 3.0f,
	0.0f, 0.5 * float(sqrt(3)) * 2 / 3, 0.0f
};
```
- Learned that we have to create our own shaders via openGL shader reference.
```
//Attempting to create our vertex shader by referencing an openGL vertex shader
//GLuint -> openGL unsigned integer, i.e. a positive integer using all 8 bits for values.
//glCreateShader() is the call, GL_VERTEX_SHADER is the type of shader.
GLuint myVertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(myVertexShader, 1, &vertexShaderSource, NULL);

//Repeat for fragment shader
GLuint myFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(myFragmentShader, 1, &fragmentShaderSource, NULL);
```
- Learned that openGL has its own set of datatypes, and utilized its version of unsigned ints for shader references. (GLuint)
- Learned that our graphics card cannot simply use our shader code; it has to be compiled immediately into Machine Code.
```
//The graphics card can't understand our shader code however, so it must be compiled into MACHINE CODE right now.
glCompileShader(myVertexShader);
glCompileShader(myFragmentShader);
```
- Learned that even though our shaders are compiled into Machine code, we still need to wrap them into a shader program so they can actually be used.
```
glAttachShader(shaderProgram, myVertexShader);
glAttachShader(shaderProgram, myFragmentShader);
glLinkProgram(shaderProgram);
```
- Learned that you can delete the previously created shaders after compiling them and adding them to a shaderProgram, since they are aready in the shaderProgram.
```
glDeleteShader(myVertexShader);
glDeleteShader(myFragmentShader);
```
- Learned that BINDING in openGL means that we make a certain object the CURRENT object, so if we were to fire a function that modifies that type of object, it modifies the current BINDED object.
- Learned that moving data between the CPU and GPU is slow, so we utilize buffers again to make sure we pass a sufficient amount.
- Learned that Vertex Buffer Objects contain our actual vertices to be passed to our shaders.
- Learned that Vertex Array Objects tell out shaders HOW TO INTERPRET our Vertex Buffer Objects.
- Learned that you better have your vertice math correct...
- Got a triangle to display!!!





5.3.21
- Learned about what an index buffer is (a way to re-use indices).
- Learned that index buffers are created and bound in a similar way to VAOs and VBOs.
- Learned that index buffers are PART of a VAO, so they need to be bound AFTER the VAO otherwise openGL will assume that you don't want to use the index buffer.
- Got a tri-force rendeirng!
- Moved the Vertex Shader to its own text file 'default.vert'.
- Moved the Fragment Shader to its own text file 'default.frag'.
- Defined my FIRST class 'shaderClass.h':
- Created 'shaderClass.cpp' where we included our 'shaderClass.h' and implemented a small function to read text files in as a string.
- Created a 'VBO.h' headerfile.
- Created a 'VBO.cpp' where we included our 'VBO.h' and implemented the code for creating, binding, unbinding, and deleting our VBO.




5.4.21
- Successfully migrated core functionality to external classes and header files.
- Verified that the tri-force still displays correctly.
- Learned that shaders are just functions that run on the CPU.
- Learned that (for openGL) shaders use GLSL (openGL Shader Language) that has a similar syntax to C.
- [42:30] A great visual for demonstrating how we are feeding data to the shader, and how we tell the shader to process the data with offsets and strides.
- Learned that the Coordinates Stride is the distance in Bytes between to sets of vertex coordinates startpoints.
- Learned that the Color Stride is the distance in Bytes between two sets of color data startpoints.
- Learned that the Color Offset controls the separation of coordinate and color data within a set of Bytes.
- Learned about "Uniforms" that are essentially universal variables, that can be accessed by multiple shaders and evenfrom within the main() function.
- *Don't declare Uniforms UNLESS you KNOW you are going to use them since OpenGL will delete them automatically which may cause errors!*
- Observed that you need to set up error catching for shaders since there doesn't seem to be any built into openGL. (The tutorial even differentiates with IF-ELSE between compilation errors and linker errors.
- Got a rainbow square to appear!
- Scale now works with a Uniform!
- Understand the coordinates system a little better now (the square was more intuitive).

5.6.21
- Learned about texture "units", essentially they are slots reserved for individual textures that come together as a bundle. (at least in openGL's implementation).
- Two modes for scaling texture resolution up or down; GL_NEAREST and GL_LINEAR. Using GL_NEAREST keeps things pixelated and is preffered when working with pixel art. Using GL_LINEAR generates NEW pixels based on the pixels nearby which softens the texture and generally results in a blurrier image. 
- Learned about some other settings regarding textures. GL_REPEAT simply repeats the texture. GL_MIRRORED_REPEAT mirrors the texture everytime it is repeated. GL_CLAMP_TO_EDGE simply stretches the image to the edges. GL_CLAMP_TO_BORDER inserts a border of your choice color around the edges of the image. ***You can mix and match them since they only apply on ONE axis at a time (s,d,r [x,y,x] respectively).***
- PAY ATTENTION TO COLOR CHANNELS! GL_RGB is for .jpegs, GL_RGBA is for .png.
- Textures are applied via coordinates from 0 to 1 on both axis, with (0,0) being the bottom left corner and (1,1) being the top right corner. Coordinates higher than 1 cause the texture to repeat.
- Learned that openGL reads images from left to right, bottom to top. While the stbi library passes images left to right from top to bottom. Utilized a standard stbi function to flip vertically on load.
