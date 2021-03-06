#pragma once
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>
//#include <GL/glut.h>
// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
// to scale
//#include <glm/gtc/matrix_transform.hpp> 


#include "shader.hpp"
//#include "controls.hpp"
#include "objloader.hpp"
//For using the clock
#include <chrono>
//for loading the image
#include <soil.h>

#include "GameState.h"
#include <iostream>
//#include <ratio>

//vao/vbo classes
#include "emigration/vertexArray.h"
#include "emigration/vertexBuffer.h"


//#include "Camera.h"
//#include "GObject.h"

class Engine {
	public:
		Engine();
		~Engine();
	
		void init();
		void loop();
		void input();

	private:
		//Window
		GLFWwindow* window;
		const GLFWvidmode* mode;

		//GameState
		GameState *gameState;

		//Loop
		bool isRunning = true; 
		bool mouseEnabled = true; //used later for mouse input feature
		
		//Shaders
		std::vector<GLuint> shaders;

		//VAOs
		std::vector<GLuint> vaoIDs; //identifies which VAO will be sent to the shaders for each object
		std::vector<GLsizei> vaoVertexCounts; //simply passed to the shaders for each object
		
		//Texture
		GLuint loadtextures(const char* fileName);
		std::vector<GLuint> textures; //textureIDs
};