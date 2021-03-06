#include "Engine.h"

/*
** The view and projection matrices will be the same for every GObject, and every GObject's shader can be the same with an if statement in the shader
** that determines if the object is also a light source. With that in mind, only one set of shaders is needed.
** Moving forward: -need to adjust to one set of shaders	-need to account for attenuation distance before computing a GObject as a light source
** -need to declare globals to pass between classes
*/
Engine::Engine() {

}
//need a VAO and the number of vertices in model to pass to each object
Engine::~Engine() {
	// Cleanup VBO and shader
	/*
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	*/
	//Clean up buffers
	delete gameState;
}

void Engine::init() {
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		//Error
	}
	// Open a window and create its OpenGL context
	mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//window = glfwCreateWindow(mode->width, mode->height, "Worm Hole Space Adventure", glfwGetPrimaryMonitor(), NULL);
	window = glfwCreateWindow(1024, 768, "Worm Hole Space Adventure", NULL, NULL);


	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		//Error
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		//Error
	}

	//Escape Key listener
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	//glfwPollEvents(); not needed now, will need for Game Load Screen later
	glfwSetCursorPos(window, mode->width / 2, mode->height / 2);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//OpenGL Settings
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	//Load Shaders
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");
	shaders.push_back(programID); //add the shaderID once it's loaded for each of the shaders we use
	//Load VAOs
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = loadOBJ("ExportedModels/SS1_OBJ/SS1tri.obj", vertices, uvs, normals);


	//Load Textures
	GLuint Texture = loadtextures("ExportedModels/SS1_OBJ/SS1tri2.jpg");
	textures.push_back(Texture); //index 0 is our first VAO's texture
	Texture = loadtextures("Resources/Particle.png");
	textures.push_back(Texture);
	//GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler"); used in object class, not here


	/********************************************************************************/
	//Follow this for creating vao and binding vbos to it.  Probably just add more vbos 
	//make va
	vertexArray* va1 = new vertexArray();

	//make vb
	vertexBuffer* vert_VB1 = new vertexBuffer(&vertices[0], vertices.size() * sizeof(glm::vec3));
	va1->addBuffer(vert_VB1, 0, 0, 3, GL_FLOAT, false, 0, 0);

	//make uv vb
	vertexBuffer* uv_VB1 = new vertexBuffer(&uvs[0], uvs.size() * sizeof(glm::vec2));
	va1->addBuffer(uv_VB1, 1, 1, 2, GL_FLOAT, false, 0, 0);

	//get it on 
	vaoIDs.push_back(va1->arrayID);
	vaoVertexCounts.push_back(vertices.size());
	/********************************************************************************/
	
	//construct VAO for a particle - hardcoded first
	vertices = {
		glm::vec3(-.5, .5, -5),
		glm::vec3(-.5, -.5, -5),
		glm::vec3(.5, .5, -5),
		glm::vec3(.5, .5, -5),
		glm::vec3(-.5, -.5, -5),
		glm::vec3(.5, -.5, -5)
	};
	uvs = {
		glm::vec2(0, 0),
		glm::vec2(0, 1),
		glm::vec2(1, 0),
		glm::vec2(1, 0),
		glm::vec2(0, 1),
		glm::vec2(1, 1)
	};

	/********************************************************************************/
	vertexArray* va2 = new vertexArray();

	//make vb
	vertexBuffer* vert_VB2 = new vertexBuffer(&vertices[0], vertices.size() * sizeof(glm::vec3));
	va2->addBuffer(vert_VB2, 0, 0, 3, GL_FLOAT, false, 0, 0);

	//make uv vb
	vertexBuffer* uv_VB2 = new vertexBuffer(&uvs[0], uvs.size() * sizeof(glm::vec2));
	va2->addBuffer(uv_VB2, 1, 1, 2, GL_FLOAT, false, 0, 0);

	//get it on 
	vaoIDs.push_back(va2->arrayID);
	vaoVertexCounts.push_back(vertices.size());
	/********************************************************************************/

	if (isRunning) {
		//Create GameState
		gameState = new GameState();
		//Load Entities
		//GLuint MatrixID = glGetUniformLocation(programID, "MVP"); not used here, will be later in gamestate (basically one instance of a possible camera class)

		gameState->addCamera(new Camera(shaders[0], 90.0f, 4.0f / 3.0f, 0.1f, 1000.0f));
		//Player* player0 = new Player(shaders[0], textures[0], vaoIDs[0], vaoVertexCounts[0], glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
		gameState->addPlayer(new Player(shaders[0], textures[0], vaoIDs[0], vaoVertexCounts[0], glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0)));
		//gameState->addGObject(new GObject(shaders[0], textures[0], vaoIDs[0], vaoVertexCounts[0], glm::vec3(0.0f, 0.0f, 0.0f)));
		gameState->addWormhole(new Wormhole(shaders[0], textures[1], vaoIDs[1], vaoVertexCounts[1], 10000, glm::vec3(0.0f, 0.0f, 0.0f)));
	}
	
}





void Engine::loop() {

	using clock = std::chrono::high_resolution_clock;

	double updatesPerSecond = 60.0;
	double time = 0.0;
	double dt = 1000000000.0 / (updatesPerSecond);

	double accumulator = 0.0;
	double alpha = accumulator / dt;

	/*Start Clock*/
	auto start = clock::now();

	auto newFrameTime = clock::now();
	auto oldFrameTime = clock::now();
	std::chrono::nanoseconds frameTime;

	/***********************************************/
	/*FPS*/
	auto fps = clock::now();
	int renderCounter = 0;
	int updateCounter = 0;
	/***************************************/

	while (isRunning) {
		newFrameTime = std::chrono::high_resolution_clock::now();
		frameTime = newFrameTime - oldFrameTime;
		oldFrameTime = newFrameTime;

		//Spiral of death?

		accumulator += (double)frameTime.count();/*Adding length of frame*/

		while (accumulator >= dt) {

			gameState->update(time, dt);

			//FPS keeps track of updates
			updateCounter++;

			//Calculate Time
			time += dt;
			//subtracting dt intervals
			accumulator -= dt;
		}

		//Calculate Alpha
		alpha = accumulator / dt;

		//Render GameState
			// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gameState->render(alpha);
		glfwSwapBuffers(window);
		renderCounter++;

		//Poll Inputs
		input();
		
		if (((double)(clock::now() - fps).count()) >= 1000000000.0) {
			//FPS = renderCounter;
			//UPDATES = updateCounter;
			std::cout << "Tick: " << updateCounter << std::endl;
			std::cout << "FPS: " << renderCounter << std::endl;

			renderCounter = 0;
			updateCounter = 0;
			fps = clock::now();
		}

	}
}

void Engine::input() {
	//Poll Events
	glfwPollEvents();
	//Reset Cursor
	glfwSetCursorPos(window, mode->width / 2, mode->height / 2);

	if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) || glfwWindowShouldClose(window)) {
		isRunning = false;
	}
}


GLuint Engine::loadtextures(const char* fileName) {

	int width, height;

	unsigned char* image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	if (image == NULL)
		printf("Could not load the texture image from path %s!\n", fileName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	return textureId;
	
	return 0;
}
