#include <iostream>
#include <glad/glad.h>
#include <SDL.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"
#include <vector>

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_Window* window = SDL_CreateWindow("WE TRY, I SWEAR", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
	if (window == nullptr)
	{
		std::cout << "Failed to create SDL Window" << std::endl;
		SDL_Quit();
		return -1;
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		SDL_Quit();
		return -2;
	}


	float vertices[] = {
		//	X	  Y      Z        R    G    B         S    T
		// Background
		 1.0f,  1.0f, 0.0f,      1.0f, 1.0f, 1.0f,   1.0f, 1.0f,     // top right
		 1.0f, -1.0f, 0.0f,      1.0f, 1.0f, 1.0f,   1.0f, 0.0f,     // bottom right
		-1.0f, -1.0f, 0.0f,      1.0f, 1.0f, 1.0f,   0.0f, 0.0f,     // bottom left
		-1.0f,  1.0f, 0.0f,      1.0f, 1.0f, 1.0f,   0.0f, 1.0f,     // top left

		// Object 1
		 0.0f,     0.125f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.0f,    -0.125f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.1875f, -0.125f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.1875f,  0.125f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left

		// Object 2
		-0.1875f,  0.625f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		-0.1875f,  0.375f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.375f,   0.375f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.375f,   0.625f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left

		// Object 3
		-0.375f,   0.125f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		-0.375f,  -0.125f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5625f, -0.125f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5625f,  0.125f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left

		// Object 4
		 0.125f,  -0.375f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.125f,  -0.625f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.0625f, -0.625f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.0625f, -0.375f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left

		//test for UI
		 0.04f,  0.08f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,     // top right
		 0.04f, -0.04f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,     // bottom right
		-0.04f, -0.04f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,     // bottom left
		-0.04f,  0.08f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,     // top left

		//test for UI
		 0.04f,  0.04f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,     // top right
		 0.04f, -0.04f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,     // bottom right
		-0.04f, -0.04f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,     // bottom left
		-0.04f,  0.04f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,		// top left

		// Rocks
		1.5625f, -0.375f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,	// top right
		1.5625f, -0.625f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,	// bottom right
		0.4375f, -0.625f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,	// bottom left
		0.4375f, -0.375f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,	// top left


		// Ship
		 0.3125f,  -0.375f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.3125f,  -0.625f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		0.125f, -0.625f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		0.125f, -0.375f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left

		// Rocks 2
		1.5625f, -0.375f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,	// top right
		1.5625f, -0.625f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,	// bottom right
		0.4375f, -0.625f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,	// bottom left
		0.4375f, -0.375f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,	// top left
	};

	unsigned int indices[] = {

		0, 1, 3,   // first triangle
		1, 2, 3,   // second triangle

	};

	GLuint vbo, ebo, vao;  // vertex buffer object
	glGenBuffers(1, &vbo); // Generate 1 buffer
	glGenBuffers(1, &ebo);
	glGenVertexArrays(1, &vao);

	// 1. bind Vertex Array Object
	glBindVertexArray(vao);

	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	const char* vertexShaderSource = R"glsl(
		#version 330 core

		in vec3 position;
		in vec3 color;
		in vec2 texCoord;
    
		out vec3 Color;
		out vec2 TexCoord;

		uniform mat4 transform;
		uniform vec2 spriteSheetSize;
		uniform int frameIndex;

		void main()
		{
			Color = color;
	
			int cols = int(spriteSheetSize.x);
			int rows = int(spriteSheetSize.y);

			int column = frameIndex % cols;
			int row = frameIndex / cols;

			float texWidth = 1.0 / float(cols);
			float texHeight = 1.0 / float(rows);

			TexCoord = texCoord * vec2(texWidth, texHeight) + vec2(float(column) * texWidth, 1.0 - float(row + 1) * texHeight);

			gl_Position = transform * vec4(position, 1.0);
		}
		)glsl";
	//function above inside void goes through the img file to pick which sprite to draw

	// Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Fragment Shader
	const char* fragmentShaderSource = R"glsl(
		#version 330 core

		in vec3 Color;
		in vec2 TexCoord;

		out vec4 outColor;

		uniform sampler2D ourTexture;

		void main()
		{
			outColor = texture(ourTexture, TexCoord);

			if (outColor == vec4(1.0f, 0.0f, 1.0f, 1.0f))
				discard;
		}
		)glsl";

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 3. then set our vertex attributes pointers
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	GLint colorAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	GLint texCoordAttrib = glGetAttribLocation(shaderProgram, "texCoord");
	glEnableVertexAttribArray(texCoordAttrib);
	glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	Texture LonerA("graphics/LonerA.bmp", glm::vec2(4.0f, 4.0f));
	Texture LonerB("graphics/LonerB.bmp", glm::vec2(4.0f, 4.0f));
	Texture LonerC("graphics/LonerC.bmp", glm::vec2(4.0f, 4.0f));
	Texture Background("graphics/galaxy2.bmp", glm::vec2(1.0f, 1.0f));
	Texture PUDive("graphics/PUDive.bmp", glm::vec2(4.0f, 2.0f));
	Texture fontLarge("graphics/font16x16.bmp", glm::vec2(8.0f, 12.0f));
	Texture fontSmall("graphics/font8x8.bmp", glm::vec2(8.0f, 16.0f)); // loads of blank space on sprite
	Texture Rocks("graphics/Blocks.bmp", glm::vec2(2.0f, 64.0f));
	Texture Ship("graphics/Ship1.bmp", glm::vec2(7.0f, 1.0f));

	glUseProgram(shaderProgram);

	GLuint textureLocationA = glGetUniformLocation(shaderProgram, "ourTexture");
	glUniform1i(textureLocationA, 0); // Texture unit 0 for LonerA

	GLuint textureLocationB = glGetUniformLocation(shaderProgram, "ourTexture");
	glUniform1i(textureLocationB, 1); // Texture unit 1 for LonerB

	GLuint textureLocationC = glGetUniformLocation(shaderProgram, "ourTexture");
	glUniform1i(textureLocationC, 2); // Texture unit 1 for LonerC

	GLuint textureLocationD = glGetUniformLocation(shaderProgram, "ourTexture");
	glUniform1i(textureLocationD, 3); // Texture unit 1 for PUDive

	GLuint textureLocationE = glGetUniformLocation(shaderProgram, "ourTexture");
	glUniform1i(textureLocationE, 4); // Texture unit UIlarge

	GLuint textureLocationF = glGetUniformLocation(shaderProgram, "ourTexture");
	glUniform1i(textureLocationF, 5); // Texture unit UIsmall

	GLuint textureLocationG = glGetUniformLocation(shaderProgram, "ourTexture");
	glUniform1i(textureLocationG, 6); // Texture unit 6 for Rocks

	GLuint textureLocationH = glGetUniformLocation(shaderProgram, "ourTexture");
	glUniform1i(textureLocationH, 7); // Texture unit 7 for Ship

	GLuint textureLocationI = glGetUniformLocation(shaderProgram, "ourTexture");
	glUniform1i(textureLocationI, 8); // Texture unit 8 for Rocks 2

	SDL_Event windowEvent;
	float lastTime = SDL_GetTicks();
	int frameIndex = 0;

	//Displays all the textures and their information at the start of runtime
	//for (const auto& texture : textures) {
	//	std::cout << "Texture ID: " << texture.m_TextureID << std::endl;
	//	std::cout << "Width: " << texture.m_Width << ", Height: " << texture.m_Height << ", Channels: " << texture.m_NumChannels << std::endl;
	//	std::cout << "Sprite Sheet Size: (" << texture.m_SpriteSheetSize.x << ", " << texture.m_SpriteSheetSize.y << ")" << std::endl;
	//}

	// Draw UI

	//fontLarge
	glm::mat4 transformP = glm::mat4(1.0f);
	transformP = glm::translate(transformP, glm::vec3(-0.94f, 0.85f, 0.0f)); // Position for 'P'
	glm::mat4 transformL = glm::mat4(1.0f);
	transformL = glm::translate(transformL, glm::vec3(-0.87f, 0.85f, 0.0f)); // Position for 'l'
	glm::mat4 transformA = glm::mat4(1.0f);
	transformA = glm::translate(transformA, glm::vec3(-0.79f, 0.85f, 0.0f)); // Position for 'a'
	glm::mat4 transformY = glm::mat4(1.0f);
	transformY = glm::translate(transformY, glm::vec3(-0.69f, 0.85f, 0.0f)); // Position for 'y'
	glm::mat4 transformE = glm::mat4(1.0f);
	transformE = glm::translate(transformE, glm::vec3(-0.59f, 0.85f, 0.0f)); // Position for 'e'
	glm::mat4 transformR = glm::mat4(1.0f);
	transformR = glm::translate(transformR, glm::vec3(-0.49f, 0.85f, 0.0f)); // Position for 'r'

	glm::mat4 transformO = glm::mat4(1.0f);
	transformO = glm::translate(transformO, glm::vec3(-0.34f, 0.85f, 0.0f)); // Position for 'O'
	glm::mat4 transformN = glm::mat4(1.0f);
	transformN = glm::translate(transformN, glm::vec3(-0.24f, 0.85f, 0.0f)); // Position for 'n'
	glm::mat4 transformE2 = glm::mat4(1.0f);
	transformE2 = glm::translate(transformE2, glm::vec3(-0.14f, 0.85f, 0.0f)); // Position for 'e2'

	//fontSmall
	glm::mat4 transformH = glm::mat4(1.0f);
	transformH = glm::translate(transformH, glm::vec3(0.45f, 0.9f, 0.0f)); // Position for 'H'
	glm::mat4 transformI = glm::mat4(1.0f);
	transformI = glm::translate(transformI, glm::vec3(0.52f, 0.9f, 0.0f)); // Position for 'i'

	glm::mat4 transformS = glm::mat4(1.0f);
	transformS = glm::translate(transformS, glm::vec3(0.62f, 0.9f, 0.0f)); // Position for 'S'
	glm::mat4 transformC = glm::mat4(1.0f);
	transformC = glm::translate(transformC, glm::vec3(0.70f, 0.9f, 0.0f)); // Position for 'c'
	glm::mat4 transformO2 = glm::mat4(1.0f);
	transformO2 = glm::translate(transformO2, glm::vec3(0.78f, 0.9f, 0.0f)); // Position for 'o2'
	glm::mat4 transformR2 = glm::mat4(1.0f);
	transformR2 = glm::translate(transformR2, glm::vec3(0.86f, 0.9f, 0.0f)); // Position for 'r2'
	glm::mat4 transformE3 = glm::mat4(1.0f);
	transformE3 = glm::translate(transformE3, glm::vec3(0.95f, 0.9f, 0.0f)); // Position for 'e3'


	// Get the location of the transform uniform
	GLint transformLoc = glGetUniformLocation(shaderProgram, "transform");

	float rockSpeed = 0.5f; // Speed of the movement
	float top1Position = 1.5f; // Top position for rock 1
	float bottom1Position = -1.5f; // Bottom position for rock 1
	float rock1Position = top1Position; // Initial position for rock 1
	bool moving1Down = true; // Initial direction for rock 1

	float top2Position = 1.5f; // Top position for rock 2
	float bottom2Position = -1.5f; // Bottom position for rock 2
	float rock2Position = 0; // Initial position for rock 2
	bool moving2Down = true; // Initial direction for rock 2

	float alienSpeed = 0.5f; // Speed of the movement
	float alienLeftPosition = 1.0f; // Left position
	float alienRightPosition = 0.0f; // Right position
	float alienPosition = alienRightPosition; // Initial position
	bool movingLeft = true; // Initial direction

	float shipX = 0.0f;
	float shipY = -0.5f;
	float shipSpeed = 0.5f;

	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
		}


		float currentTime = SDL_GetTicks();
		float deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		float framesPerSecond = 12.0f;

		static float animationTime = 0.0f;
		float frameDuration = 1.0f / framesPerSecond;
		animationTime += deltaTime;

		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_W])
		{
			shipY += shipSpeed * deltaTime;
		}
		if (state[SDL_SCANCODE_S])
		{
			shipY -= shipSpeed * deltaTime;
		}
		if (state[SDL_SCANCODE_A])
		{
			shipX -= shipSpeed * deltaTime;
		}
		if (state[SDL_SCANCODE_D])
		{
			shipX += shipSpeed * deltaTime;
		}

		if (animationTime >= frameDuration)
		{
			frameIndex = (frameIndex + 1) % (int)(LonerA.GetSpriteSheetSize().x * LonerA.GetSpriteSheetSize().y);
			animationTime -= frameDuration;
		}

		if (moving1Down)
		{
			rock1Position -= rockSpeed * deltaTime;
			if (rock1Position <= bottom1Position)
			{
				rock1Position = top1Position;

			}
		}

		if (moving2Down)
		{
			rock2Position -= rockSpeed * deltaTime;
			if (rock2Position <= bottom2Position)
			{
				rock2Position = top2Position;

			}
		}

		if (movingLeft)
		{
			alienPosition += alienSpeed * deltaTime;
			if (alienPosition >= alienLeftPosition)
			{
				alienSpeed = -alienSpeed;
				movingLeft = false;
			}
		}
		else
		{
			alienPosition += alienSpeed * deltaTime;
			if (alienPosition <= alienRightPosition)
			{
				alienSpeed = -alienSpeed;
				movingLeft = true;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		glBindVertexArray(vao);

		GLint frameIndexLocation = glGetUniformLocation(shaderProgram, "frameIndex");
		GLint spriteSheetSizeLocation = glGetUniformLocation(shaderProgram, "spriteSheetSize");

		// Draw Background
		Background.Bind(0);
		glUniform1i(frameIndexLocation, 0); // No animation for background
		glUniform2fv(spriteSheetSizeLocation, 1, &Background.GetSpriteSheetSize()[0]);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f))); //stops the background from moving with glm
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 0);

		glm::mat4 rock1Transform = glm::mat4(1.0f);
		rock1Transform = glm::translate(rock1Transform, glm::vec3(0.0f, rock1Position, 0.0f));

		Rocks.Bind(6);
		glUniform1i(frameIndexLocation, 101); // No animation for Rocks
		glUniform2fv(spriteSheetSizeLocation, 1, &Rocks.GetSpriteSheetSize()[0]);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(rock1Transform));
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 6);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 28);

		glm::mat4 rock2Transform = glm::mat4(1.0f);
		rock2Transform = glm::translate(rock2Transform, glm::vec3(0.0f, rock2Position, 0.0f));

		Rocks.Bind(8);
		glUniform1i(frameIndexLocation, 101); // No animation for Rocks
		glUniform2fv(spriteSheetSizeLocation, 1, &Rocks.GetSpriteSheetSize()[0]);
		glm::mat4 flipTransform = glm::scale(rock2Transform, glm::vec3(-1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(flipTransform));
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 6);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 36);

		glm::mat4 alienTransform = glm::mat4(1.0f);
		alienTransform = glm::translate(alienTransform, glm::vec3(alienPosition, 0.0f, 0.0f));

		// Draw Object 1 with LonerA texture
		LonerA.Bind(0);
		glUniform1i(frameIndexLocation, frameIndex);
		glUniform2fv(spriteSheetSizeLocation, 1, &LonerA.GetSpriteSheetSize()[0]);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(alienTransform));
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 4);

		// Draw Object 2 with LonerB texture
		LonerB.Bind(1);
		glUniform1i(frameIndexLocation, frameIndex);
		glUniform2fv(spriteSheetSizeLocation, 1, &LonerB.GetSpriteSheetSize()[0]);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 1);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 8);

		// Draw Object 3 with LonerC texture
		LonerC.Bind(2);
		glUniform1i(frameIndexLocation, frameIndex);
		glUniform2fv(spriteSheetSizeLocation, 1, &LonerC.GetSpriteSheetSize()[0]);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 2);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 12);

		glm::mat4 shipTransform = glm::mat4(1.0f);
		shipTransform = glm::translate(shipTransform, glm::vec3(shipX, shipY, 0.0f));

		Ship.Bind(7);
		glUniform1i(frameIndexLocation, 4);
		glUniform2fv(spriteSheetSizeLocation, 1, &Ship.GetSpriteSheetSize()[0]);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(shipTransform));
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 7);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 32);


		// Draw Object 4 with PUDive texture
		PUDive.Bind(3);
		glUniform1i(frameIndexLocation, frameIndex);
		glUniform2fv(spriteSheetSizeLocation, 1, &PUDive.GetSpriteSheetSize()[0]);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 3);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 16);



		//UI
		// Draw the characters with their respective transformations
		fontLarge.Bind(4);

		// Draw 'P'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformP));
		glUniform1i(frameIndexLocation, 48); // P, position 48 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontLarge.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 4);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 20);
		// Draw 'l'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformL));
		glUniform1i(frameIndexLocation, 76); // l, position 76 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontLarge.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 4);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 20);
		// Draw 'a'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformA));
		glUniform1i(frameIndexLocation, 65); // a, position 65 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontLarge.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 4);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 20);
		// Draw 'y'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformY));
		glUniform1i(frameIndexLocation, 89); // y, position 89 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontLarge.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 4);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 20);
		// Draw 'e'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformE));
		glUniform1i(frameIndexLocation, 69); // e, position 69 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontLarge.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 4);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 20);
		// Draw 'r'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformR));
		glUniform1i(frameIndexLocation, 82); // r, position 82 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontLarge.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 4);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 20);

		// Draw 'O'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformO));
		glUniform1i(frameIndexLocation, 47); // O, position 47 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontLarge.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 4);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 20);
		// Draw 'n'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformN));
		glUniform1i(frameIndexLocation, 78); // n, position 78 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontLarge.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 4);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 20);
		// Draw 'e2'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformE2));
		glUniform1i(frameIndexLocation, 69); // e, position 69 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontLarge.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 4);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 20);


		fontSmall.Bind(5);
		// Draw 'H'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformH));
		glUniform1i(frameIndexLocation, 40); // H, position 41 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontSmall.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 5);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 24);
		// Draw 'i'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformI));
		glUniform1i(frameIndexLocation, 73); // i, position 69 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontSmall.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 5);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 24);

		// Draw 'S'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformS));
		glUniform1i(frameIndexLocation, 51); // e, position 69 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontSmall.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 5);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 24);
		// Draw 'c'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformC));
		glUniform1i(frameIndexLocation, 67); // e, position 69 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontSmall.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 5);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 24);
		// Draw 'o2'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformO2));
		glUniform1i(frameIndexLocation, 79); // e, position 69 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontSmall.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 5);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 24);
		// Draw 'r2'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformR2));
		glUniform1i(frameIndexLocation, 82); // e, position 69 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontSmall.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 5);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 24);
		// Draw 'e3'
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformE3));
		glUniform1i(frameIndexLocation, 69); // e, position 69 on the sheet
		glUniform2fv(spriteSheetSizeLocation, 1, &fontSmall.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 5);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 24);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}