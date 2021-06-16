// I've created a Triangle in a window using graphics with OpenGL
// Always include glad file before GLFW to build the program
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
using namespace std;


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";


//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";



int main()
{
	// Initialize GLFW
	glfwInit();

	// Giving GLFW hint that we're using version 3 : (3.4)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Give hint to GLFW that we're using CORE; using modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating a GLFWwindow object
	GLFWwindow* window = glfwCreateWindow(800, 800, "SHADY windows", NULL, NULL);
	// Error checking
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	// Introducing the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, 900, 900);



	// Creating a Vertex Shader Object and getting its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compiling the Vertex Shade
	glCompileShader(vertexShader);

	// Doing exact same thing for Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Creating Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attaching the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Linking all the shaders in shaderProgram
	glLinkProgram(shaderProgram);

	// Deleting Vertex and Fragment Shader objects as now their work is over
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	// Vertix Coordinates for a Triangle
	GLfloat vertices[] =
	{
		 -0.5f, -0.5f, 0.0f, // Lower Left Corner
		0.5f, -0.5f, 0.0f,	// Lower Right Corner
		0.0f,  0.5f, 0.0f  // Upper Corner
	};

	// Create reference containers for the Vertex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO;

	// Generating the VAO and VBO each having only one object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
  
	// Giving inputs of the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL can read the VBO and interpret it
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  
	// Enable the Vertex Attribute so that OpenGL can use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 in order NOT to modify the VAO and VBO that we've created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIANGLES
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Swapping back buffer with front buffer
		glfwSwapBuffers(window);
		// For all GLFW events
		glfwPollEvents();
	}



	// Deleting all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Delete window before ending the program
	glfwDestroyWindow(window);

	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
