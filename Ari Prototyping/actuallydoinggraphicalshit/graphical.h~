
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


void graphicsinit(int major, int minor){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

bool loadglad(){
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress){
		std::cout <<"Failed to initialize GLAD" <<std::endl;
		return false;
	}
	return true;
}

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
