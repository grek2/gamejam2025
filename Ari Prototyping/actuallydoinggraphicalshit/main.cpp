#include "definitions.h"
#include "graphical.h"
#include <iostream>
#include <string>	
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"shell32.lib")

int level = 0;

int playerx;
int playery;

const int screenwidth;
const int screenheight;

const int WIDTH = 7;
const int HEIGHT= 7;

const char* fragmentpath="";
const char* vertexpath="";
const char* blockspritepath="";
const char* subspritepath="";

const char* levelfiles[] = {"a","a","a","a"};


float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left 
};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		playery++;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		playerx++;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		playery--;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		playerx--;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
int main(){

	
	graphicsinit(4,6);

	GLFWwindow* window;
	generateWindow(&window, 800,600, "gamejam2025", &framebuffer_size_callback);

	unsigned int shaderProgram = compileshaders(fragmentpath,vertexpath);
	if (shaderProgram==NULL){
		return -1;
	}	

	unsigned int textureblock, texturesub;

	bool success; 

	texturesub = generatetexture(texturesub,0,subspritepath, GL_RGB, GL_RGB, shaderProgram, true, "subTexture");	

	textureblock = generatetexture(textureblock,1,blockspritepath, GL_RGB, GL_RGB, shaderProgram, true, "blockTexture");

	if(texturesub==NULL || textureblock ==NULL){
		return -1;
	}


	int levelnumber = 0;
	Level level = readmapfile(levelfiles[0]);

	const int vertexlistsize = 24*screenwidth*screenheight;
	std::vector<float> vertexlist(vertexlistsize);
	//float vertexlist[vertexlistsize];

	for(int i =0;i<screenheight;i++){
		for(int i1=0;i1<screenwidth;i1++){
			for(int i2=0;i2<24;i2+=6){
				int index = 24*(i*screenwidth+i1)+i2;
				vertexlist[index]=vertices[i2+0];
				vertexlist[index+1]=vertices[i2+1];
				vertexlist[index+2]=vertices[i2+2];		
				vertexlist[index+3]=vertices[i2+3];
				vertexlist[index+4]=vertices[i2+4];
				vertexlist[index+5]=vertices[i2+5];
				vertexlist[index+6]=level.sprites[i][i2];
			}
		}
	}	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texturesub);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureblock);


		//glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);




		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();

	return 0;

}
