#include "Engine.h"

/*
** The view and projection matrices will be the same for every GObject, and every GObject's shader can be the same with an if statement in the shader
** that determines if the object is also a light source. With that in mind, only one set of shaders is needed.
** Moving forward: -need to account for attenuation distance before computing a GObject as a light source
*/
Engine::Engine() {

}
//need a VAO and the number of vertices in model to pass to each object
Engine::~Engine() {
	glfwTerminate();
	delete gameState;
	delete this;
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
	window = glfwCreateWindow(mode->width, mode->height, "Worm Hole Space Adventure", glfwGetPrimaryMonitor(), NULL);
	//window = glfwCreateWindow(1024, 768, "Worm Hole Space Adventure", NULL, NULL);

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
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);
	// Hide the mouse and enable unlimited mouvement
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	bool res = loadOBJ("L200-OBJ-triangles/truck.obj", vertices, uvs, normals);

	//creating a VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//creating a vertex VBO to put in the vao and create vertex attribute pointer
	GLuint vert_VBO;
	glGenBuffers(1, &vert_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vert_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	//glVertexAttributePointer(index, size, type, normalized, stride, offset) is the format
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	// uv BO (uv Buffer Object)
	GLuint uv_VBO;
	glGenBuffers(1, &uv_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, uv_VBO);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	//glVertexAttributePointer(index, size, type, normalized, stride, offset) is the format
	//stride is byte count of the size of a "VBO", offset is offset within a "VBO"
	//
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

	//glBindVertexArray(0); //delete buffers from CPU mem once it's loaded to GPU mem
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, 1);
	//after deleting the VAO from CPU mem, add its IDs to our vaos vector
	vaoIDs.push_back(vao);
	vaoVertexCounts.push_back(vertices.size()); //index 0 is our VAO vertex count for our first object
	//done creating one VAO, need to do 2 more times

	//Load Textures
	GLuint Texture = loadtextures("L200-OBJ-triangles/truck_color.jpg");
	textures.push_back(Texture); //index 0 is our first VAO's texture
	Texture = loadtextures("Resources/Particle.png");
	textures.push_back(Texture);
	Texture = loadtextures("Asteroid/10464_Asteroid_v1_diffuse.png");
	textures.push_back(Texture);
	//GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler"); used in object class, not here

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

	GLuint vao1;
	glGenVertexArrays(1, &vao1);
	glBindVertexArray(vao1);

	glGenBuffers(1, &vert_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vert_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

	glGenBuffers(1, &uv_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, uv_VBO);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

	vaoIDs.push_back(vao1);
	vaoVertexCounts.push_back(vertices.size()); //index 0 is our VAO vertex count for our first object
	vertices.clear();
	uvs.clear();
	normals.clear();


	res = loadOBJ("Asteroid/asteroid1.obj", vertices, uvs, normals);
	GLuint vao2;
	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);

	glGenBuffers(1, &vert_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vert_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

	glGenBuffers(1, &uv_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, uv_VBO);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

	vaoIDs.push_back(vao2);
	vaoVertexCounts.push_back(vertices.size()); //index 0 is our VAO vertex count for our first object*/
	//construct game menu

	if (isRunning) {
		//Create GameState
		gameState = new GameState();
		gameState->addCamera(new Camera(shaders[0],90.0f, 4.0f / 3.0f, 0.1f, 1000.0f));
		gameState->addWormhole(new Wormhole(&shaders, &textures, &vaoIDs, &vaoVertexCounts, 1000, 10, glm::vec3(0.0f, 0.0f, 0.0f)));
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
	this->~Engine();
}

void Engine::input() {
	glfwPollEvents();

	if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) || glfwWindowShouldClose(window)) {
		isRunning = false;
	}

	if (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		keys[0] = true;
	else
		keys[0] = false;

	if (glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS)
		keys[1] = true;
	else
		keys[1] = false;

	if (glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window,  GLFW_KEY_DOWN) == GLFW_PRESS)
		keys[2] = true;
	else
		keys[2] = false;

	if (glfwGetKey(window, GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		keys[3] = true;
	else
		keys[3] = false;
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
