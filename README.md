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
  
