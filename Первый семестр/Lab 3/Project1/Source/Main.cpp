#include <iostream>
#include <conio.h>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow*, int, int, int, int); //Prototype of function which is reading keys from keyboard;


//Shaders:
//Vertex
const GLchar* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\n\0";

//Fragment
const GLchar* fragShaderSource = "#version 330 core\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

int main()
{
	int width, height;

	glfwInit(); //Initialisation of GLFW

	//Configuring GLFW
	//Minimal needed version. (Means, that will be used version 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Major
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Minor
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Installing profile
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //Window's size is now changable

	GLFWwindow* window = glfwCreateWindow(720, 480, "Program", nullptr, nullptr); //Creating window

	if (window == nullptr) //Checking for unsuccessfull creation
	{
		std::cout << "Can not create window for some reasons." << std::endl;
		glfwTerminate(); //Terminating glfw process
		return -1;		//Terminating whole program
	}

	glfwMakeContextCurrent(window); //Current context is created window.
	
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,		// Vertexes
		0.0f, 0.5f, 0.0f
	};

	//To use GLEW (for controling pointers to funtions of OpenGL
	//We should initialize it
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) //If initialization failed
	{
		std::cout << "Unable to init GLEW." << std::endl;
		return -1;
	}

	glfwGetFramebufferSize(window, &width, &height); //Getting window's size.
	//It's required to tell OpenGL, how we want to visualise data

	glViewport(0, 0, width, height); //Creating viewport

	//Passing values to the vertex shader.

	//Creating buffer
	GLuint vertexBuff;
	glGenBuffers(1, &vertexBuff);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuff); //Binding array buffer to our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Copying data to this buffer, GL_STATIC_DRAW, because data will not change
	
	//VERTEX SHADER:
	//Creating shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Building and compiling this shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint errTest; //Value, that shows the build success
	GLchar infoLog[512]; //Saving message about error
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &errTest); //Test of success

	//if error:
	if (!errTest)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error has expected. Stopped shader compilation\n" << infoLog << std::endl;
	}

	//FRAGMENTED SHADER
	//creating shader
	GLuint fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSource, NULL);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &errTest);
	if (!errTest)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "Error has expected. Stopped shader compilation\n" << infoLog << std::endl;
	}

	//Creating shader program
	GLuint shader_program;
	shader_program = glCreateProgram();

	//Attaching shaders to shader program
	glAttachShader(shader_program, vertexShader);
	glAttachShader(shader_program, fragShader);
	glLinkProgram(shader_program);
	//Same error handling
	glGetProgramiv(shader_program, GL_LINK_STATUS, &errTest);
	if (!errTest)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << "Error with shader program. Stopping...\n" << infoLog << std::endl;
	}
	
	glUseProgram(shader_program); //Call this to use our program

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	//Interpretating of vertex data for OpenGL to draw
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Drawing in OpenGL:
	// At first copying array with vertexes to buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Pointers for vertex attributes:
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	//Using shader_program()
	glUseProgram(shader_program);
	
	//Now we need to generate Vertex Array Object

	GLuint vertexArrayObj;
	glGenVertexArrays(1, &vertexArrayObj);

	glBindVertexArray(vertexArrayObj);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) //To continue work, while not closed
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindVertexArray(vertexArrayObj);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);		

		glfwPollEvents(); //Checking for any called events
		glfwSwapBuffers(window); //Swapping buffer, which contains color of every pixel

		glfwSetKeyCallback(window, key_callback); //Transfering this function into GLFW
	}

	glfwTerminate(); //To clear resources
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) //If escape is pressed -> program will close window
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		glfwSetWindowTitle(window, "Click!");
}