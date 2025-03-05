
#include <iostream>
#include <string>


#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"shell32.lib")
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfwnative.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//initializes glfw
void graphicsinit(int major, int minor){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}
//ensures glad is loaded
bool loadglad(){
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress){
		std::cout <<"Failed to initialize GLAD" <<std::endl;
		return false;
	}
	return true;
}

//generates a window
bool generateWindow(GLFWwindow** window, int width, int height, std::string name, void() framebuffer_size_callback){
	*window = glfwCreateWindow(width, height, name, NULL,NULL);
	if(*window ==NULL){
		std::cout<<"Failed to create GLFW window" <<std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFrambufferSizeCallback(window, framebuffer_size_callback);
	
	if(!loadglad()){
		return false;
	}

	glViewport(0,0,width,height);
}

//compiles and returns the id of given shaders, or -1 if there is a failure//compiles and returns the id of given shaders, or -1 if there is a failure//compiles and returns the id of given shaders, or -1 if there is a failure
int compileshaders(std::string fragmentpath, std::string vertexpath){
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try 
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode   = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
		return -1;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();

	unsigned int vertexshader, fragmentshader;
	vertexShader= glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, vShaderCode, NULL);
	glCompileShader(vertexShader);

	int success;
	char infolog[512];
	glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vertexShader,512,NULL, infoLog);
		std::cout<< "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<infoLog<<std::endl;
		return -1;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, fShaderCode,NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader,GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragmentShader,512,NULL, infoLog);
		std::cout<< "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<infoLog<<std::endl;
		return -1;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(shaderProgram,512,NULL, infoLog);
		std::cout<<"ERROR::SHADER::VERTEX::LINKING_FAILED\n"<<infoLog<<std::endl;
		return -1;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
} 
