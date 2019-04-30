#include "Engine.h"
#include "DigitalClock.h"

/*
** The view and projection matrices will be the same for every GObject, and every GObject's shader can be the same with an if statement in the shader
** that determines if the object is also a light source. With that in mind, only one set of shaders is needed.
** Moving forward: -need to adjust to one set of shaders	-need to account for attenuation distance before computing a GObject as a light source
** -need to declare globals to pass between classes
*/
Engine::Engine() {
	state = 0;
}
//need a VAO and the number of vertices in model to pass to each object
Engine::~Engine() {
	glfwTerminate();
	//****************************
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
	//window = glfwCreateWindow(mode->width, mode->height, "Worm Hole Space Adventure", glfwGetPrimaryMonitor(), NULL);
	window = glfwCreateWindow(1024, 768, "Worm Hole Space Adventure", NULL, NULL);
	//window = glfwCreateWindow(1400, 1050, "Worm Hole Space Adventure", NULL, NULL);


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
	//****************************//****************************//****************************
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);
	//glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//****************************//****************************//****************************
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

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
	Texture = loadtextures("Resources/ParticleGradient_BK.png");
	textures.push_back(Texture);
	Texture = loadtextures("ExportedModels/Asteroid/10464_Asteroid_v1_diffuse.png");
	textures.push_back(Texture);
	Texture = loadtextures("ExportedModels/Boom/BOOM.png");
	textures.push_back(Texture);
	Texture = loadtextures("Resources/digits.png");
	textures.push_back(Texture);
	//GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler"); used in object class, not here

	//ship
	/********************************************************************************/
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
	
	//particle
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
	vertices.clear();
	uvs.clear();
	normals.clear();
	   
	//asteroid
	/********************************************************************************/
	res = loadOBJ("ExportedModels/Asteroid/asteroid1.obj", vertices, uvs, normals);//make va
	vertexArray* va3 = new vertexArray();

	//make vb
	vertexBuffer* vert_VB3 = new vertexBuffer(&vertices[0], vertices.size() * sizeof(glm::vec3));
	va3->addBuffer(vert_VB3, 0, 0, 3, GL_FLOAT, false, 0, 0);

	//make uv vb
	vertexBuffer* uv_VB3 = new vertexBuffer(&uvs[0], uvs.size() * sizeof(glm::vec2));
	va3->addBuffer(uv_VB3, 1, 1, 2, GL_FLOAT, false, 0, 0);

	//get it on 
	vaoIDs.push_back(va3->arrayID);
	vaoVertexCounts.push_back(vertices.size());
	/********************************************************************************/


	vertices.clear();

	// 2 triangles per "digit" 0123456789:
	float r = 5.0f;
	for (int i = 0; i < 11; i++)
	{
		vertices.push_back(glm::vec3(-r, r, 0));
		vertices.push_back(glm::vec3(-r, -r, 0));
		vertices.push_back(glm::vec3(r, r, 0));
		vertices.push_back(glm::vec3(r, r, 0));
		vertices.push_back(glm::vec3(-r, -r, 0));
		vertices.push_back(glm::vec3(r, -r, 0));
	};
	uvs.clear();
	for (int i = 0; i < 11; i++)
	{
		float smin = 95.0f *i / 1024.0f;
		float smax = 95.0f *(i + 1) / 1024.0f;
		if (i == 10)
			smax = 1.0f;
		//smin = 95.0f / 1024.0f; smax = 2*95.0f / 1024.0f;
		uvs.push_back(glm::vec2(smin, 0));
		uvs.push_back(glm::vec2(smin, 1));
		uvs.push_back(glm::vec2(smax, 0));
		uvs.push_back(glm::vec2(smax, 0));
		uvs.push_back(glm::vec2(smin, 1));
		uvs.push_back(glm::vec2(smax, 1));
	};

	vertexArray* va4 = new vertexArray();

	//make vb
	vertexBuffer* vert_VB4 = new vertexBuffer(&vertices[0], vertices.size() * sizeof(glm::vec3));
	va4->addBuffer(vert_VB4, 0, 0, 3, GL_FLOAT, false, 0, 0);

	//make uv vb
	vertexBuffer* uv_VB4 = new vertexBuffer(&uvs[0], uvs.size() * sizeof(glm::vec2));
	va4->addBuffer(uv_VB4, 1, 1, 2, GL_FLOAT, false, 0, 0);

	//get it on 
	vaoIDs.push_back(va4->arrayID);
	vaoVertexCounts.push_back(vertices.size());

	if (isRunning) {
		//Create GameState

		reset();

		//
		//gameState = new GameState();
		//gameState->init();



		////Load Entities
		////GLuint MatrixID = glGetUniformLocation(programID, "MVP"); not used here, will be later in gamestate (basically one instance of a possible camera class)

		//gameState->addCamera(new Camera(shaders[0], 90.0f, 4.0f / 3.0f, 0.1f, 1000.0f));

		//Player* player0 = new Player(&shaders, &textures, &vaoIDs,
		//	&vaoVertexCounts, glm::vec3(0.0f, 0.0f, 75.0f), glm::vec3(0.0, 1.0, 0.0));
		//	//&vaoVertexCounts, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 0.0, 1.0));
		//gameState->addPlayer(player0);

		//gameState->addWormhole(new Wormhole(&shaders, &textures, &vaoIDs, 
		//	&vaoVertexCounts, 10000, 10, glm::vec3(0.0f, 0.0f, 0.0f)));

	}
	createMenu();
}



void Engine::reset()
{
	//if (isRunning) {
		//Create GameState

		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		gameState = new GameState();
		gameState->init();
		//Load Entities
		//GLuint MatrixID = glGetUniformLocation(programID, "MVP"); not used here, will be later in gamestate (basically one instance of a possible camera class)

		gameState->addCamera(new Camera(shaders[0], 90.0f, 4.0f / 3.0f, 0.1f, 1000.0f));

		Player* player0 = new Player(&shaders, &textures, &vaoIDs,
			&vaoVertexCounts, glm::vec3(0.0f, 0.0f, 75.0f), glm::vec3(0.0, 1.0, 0.0));
		//&vaoVertexCounts, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 0.0, 1.0));
		gameState->addPlayer(player0);

		gameState->addWormhole(new Wormhole(&shaders, &textures, &vaoIDs,
			&vaoVertexCounts, 10000, 10, glm::vec3(0.0f, 0.0f, 0.0f)));

		gameState->addGObject(new DigitalClock(shaders[0], textures[4], vaoIDs[3], vaoVertexCounts[3], glm::vec3(-150.0f, 150.0f, -81.0f)));

	//}
}

GLuint Engine::createVao(std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs)
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//creating a vertex VBO to put in the vao and create vertex attribute pointer
	GLuint vert_VBO;
	glGenBuffers(1, &vert_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vert_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	// uv BO (uv Buffer Object)
	GLuint uv_VBO;
	glGenBuffers(1, &uv_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, uv_VBO);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	//glVertexAttributePointer(index, size, type, normalized, stride, offset) is the format
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

	glBindVertexArray(0); //delete buffers from CPU mem once it's loaded to GPU mem
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 1);
	return vao;
}

void Engine::createMenu()
{
	// vertexes and UVs for a background QUAD
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	vertices.push_back(glm::vec3(-1, -1, 0));
	vertices.push_back(glm::vec3(+1, -1, 0));
	vertices.push_back(glm::vec3(+1, +1, 0));

	vertices.push_back(glm::vec3(-1, -1, 0));
	vertices.push_back(glm::vec3(+1, +1, 0));
	vertices.push_back(glm::vec3(-1, +1, 0));

	uvs.push_back(glm::vec2(0, 1));
	uvs.push_back(glm::vec2(1, 1));
	uvs.push_back(glm::vec2(1, 0));
	uvs.push_back(glm::vec2(0, 1));
	uvs.push_back(glm::vec2(1, 0));
	uvs.push_back(glm::vec2(0, 0));

	//creating a VAO
	GLuint vao = createVao(vertices, uvs);

	vaoIDs.push_back(vao);
	vaoVertexCounts.push_back(vertices.size());

	//Load Texture
	GLuint Texture = loadtextures("L200-OBJ-triangles/menu-background.jpg");
	textures.push_back(Texture);

	//Create menustate
	menuState = new GameState();

	int d = 3;
	// ortho camera
	menuState->addCamera(new Camera(shaders[0], 90.0f, 4.0f / 3.0f, 0.1f, 1000.0f, true));
	menuState->addGObject(new GObject(shaders[0], textures[1 + d + 1], vaoIDs[1 + d], vaoVertexCounts[1 + d], glm::vec3(0.0f, 0.0f, -0.9f), glm::vec3(0.0f, 0.0f, 0.0f)));


	// PLAY
	vertices.clear();
	float xmin = -0.8f, ymin = 0.6f;
	float xmax = -0.4f, ymax = 0.8f;
	vertices.push_back(glm::vec3(xmin, ymin, 0.0f));
	vertices.push_back(glm::vec3(xmax, ymin, 0.0f));
	vertices.push_back(glm::vec3(xmax, ymax, 0.0f));
	vertices.push_back(glm::vec3(xmin, ymin, 0.0f));
	vertices.push_back(glm::vec3(xmax, ymax, 0.0f));
	vertices.push_back(glm::vec3(xmin, ymax, 0.0f));
	vao = createVao(vertices, uvs);
	vaoIDs.push_back(vao);
	vaoVertexCounts.push_back(vertices.size());
	Texture = loadtextures("L200-OBJ-triangles/play1.jpg"); //2
	textures.push_back(Texture);
	Texture = loadtextures("L200-OBJ-triangles/play2.jpg"); //3
	textures.push_back(Texture);
	menuState->addGObject(new GObject(shaders[0], textures[2 + d + 1], vaoIDs[2 + d], vaoVertexCounts[2 + d], glm::vec3(0.0f, 0.0f, -0.8f), glm::vec3(0.0f, 0.0f, 0.0f)));
	playHighLight = new GObject(shaders[0], textures[3 + d + 1], vaoIDs[2 + d], vaoVertexCounts[2 + d], glm::vec3(0.0f, 0.0f, -0.7f), glm::vec3(0.0f, 0.0f, 0.0f));
	menuState->addGObject(playHighLight);

	// EXIT
	ymin = 0.3f; ymax = 0.5f;
	vertices.clear();
	vertices.push_back(glm::vec3(xmin, ymin, 0.0f));
	vertices.push_back(glm::vec3(xmax, ymin, 0.0f));
	vertices.push_back(glm::vec3(xmax, ymax, 0.0f));
	vertices.push_back(glm::vec3(xmin, ymin, 0.0f));
	vertices.push_back(glm::vec3(xmax, ymax, 0.0f));
	vertices.push_back(glm::vec3(xmin, ymax, 0.0f));
	vao = createVao(vertices, uvs);
	vaoIDs.push_back(vao);
	vaoVertexCounts.push_back(vertices.size());
	Texture = loadtextures("L200-OBJ-triangles/exit1.jpg"); //4
	textures.push_back(Texture);
	Texture = loadtextures("L200-OBJ-triangles/exit2.jpg"); //5
	textures.push_back(Texture);
	menuState->addGObject(new GObject(shaders[0], textures[4 + d + 1], vaoIDs[3 + d], vaoVertexCounts[3 + d], glm::vec3(0.0f, 0.0f, -0.8f), glm::vec3(0.0f, 0.0f, 0.0f)));
	exitHighLight = new GObject(shaders[0], textures[5 + d + 1], vaoIDs[3 + d], vaoVertexCounts[3 + d], glm::vec3(0.0f, 0.0f, -0.7f), glm::vec3(0.0f, 0.0f, 0.0f));
	menuState->addGObject(exitHighLight);

	
	//playHighLight->enableObject(false);
	//exitHighLight->enableObject(false);
}



void Engine::loop() {
	while (state == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		menuState->render(1.0);
		glfwSwapBuffers(window);
		//Poll Inputs
		input();
	}

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

		auto t = newFrameTime;
		if (gameState->isHit )
		{
			/*if (gameState->timeHit != 0) {*/
				//gameState->timeHit += (int)t.time_since_epoch().count()/10000000;
			gameState->timeHit++;
				std::cout << gameState->timeHit << std::endl;
			
				//gameState->timeHit = ((t.time_since_epoch().count() / 100000) + 3);
				//if ( ((t.time_since_epoch().count() /100000) +3 ) == (newFrameTime.time_since_epoch().count() / 100000))
				if (gameState->timeHit == 300)
				{
					std::cout << "RESET" << std::endl;
					gameState->timeHit = 0;
					reset();

				}
			//}

		}

		//Spiral of death?

		accumulator += (double)frameTime.count();/*Adding length of frame*/

		while (accumulator >= dt) {
	/*		if (state) {
				hisstate->.update/input
			}else{
			below update
			}*/
			gameState->update(time, dt, keys);

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

		//if(state)****************
		//his render
		//else
		//our render
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

	if (state == 1)	// play mode
	{
		glfwSetCursorPos(window, mode->width / 2, mode->height / 2);

		if (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			keys[0] = true;
		else
			keys[0] = false;

		if (glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			keys[1] = true;
		else
			keys[1] = false;

		if (glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			keys[2] = true;
		else
			keys[2] = false;

		if (glfwGetKey(window, GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			keys[3] = true;
		else
			keys[3] = false;
	}
	else
	{
		// we have to check which menu item is "hover"
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		// normalizing (-1,1)
		x = 2 * x / w - 1;
		y = 2 * (h - y) / h - 1;

		playHighLight->enableObject(false);
		exitHighLight->enableObject(false);
		// check over "play"
		if (x >= -0.8f && x <= -0.4f && y >= 0.6f && y <= 0.8f)
		{
			playHighLight->enableObject(true);
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
				setState(1);
		}
		if (x >= -0.8f && x <= -0.4f && y >= 0.3f && y <= 0.5f)
		{
			exitHighLight->enableObject(true);
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
				exit(0);
		}
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

void Engine::setState(int state)
{
	if (state == this->state) return;
	if (state == 1)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPos(window, mode->width / 2, mode->height / 2);
	}
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR);
	this->state = state;
}