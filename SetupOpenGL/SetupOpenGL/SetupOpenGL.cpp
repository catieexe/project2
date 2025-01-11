#include <iostream>
#include <glad/glad.h>
#include <SDL.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"
#include <vector>

int main(int argc, char **argv)
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
	//	X		Y      Z        R    G    B         S    T
		// Background
		1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
		1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
	   -1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	   -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   // top left

	   // Object 1
	   0.0f,      0.125f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	   0.0f,     -0.125f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	  -0.1875f, -0.125f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	  -0.1875f,  0.125f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left

	  // Object 2
	  -0.1875f,  0.625f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	  -0.1875f,  0.375f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	  -0.375f,   0.375f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	  -0.375f,   0.625f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left

	  // Object 3
	  -0.375f,  0.125f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	  -0.375f, -0.125f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	  -0.5625f, -0.125f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	  -0.5625f,  0.125f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left

		// Object 4
		0.125f, -0.375f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.125f, -0.625f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	   -0.0625f, -0.625f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	   -0.0625f, -0.375f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left

		//test for UI
		0.2f,  0.4f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
		0.2f, -0.2f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
	   -0.2f, -0.2f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	   -0.2f,  0.4f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   // top left


	};

	unsigned int indices[] = {
		// Background
		0, 1, 3,   // first triangle
		1, 2, 3,   // second triangle

		// Object 1
		4, 5, 7,   // first triangle
		5, 6, 7,   // second triangle

		// Object 2
		8, 9, 11,   // first triangle
		9, 10, 11,   // second triangle

		// Object 3
		12, 13, 15,   // first triangle
		13, 14, 15,   // second triangle

		// Object 4
		16, 17, 19,   // first triangle
		17, 18, 19,   // second triangle0
		
		//test for UI
		20, 21, 23,   // first triangle
		21, 22, 23,   // second triangle
	};

	GLuint vbo, ebo; // vertex buffer object
	glGenBuffers(1, &vbo); // Generate 1 buffer
	glGenBuffers(1, &ebo);	

	GLuint vao;
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

			gl_Position = vec4(position, 1.0);
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
	glUniform1i(textureLocationE, 4); // Texture unit UI

	SDL_Event windowEvent;
	float lastTime = SDL_GetTicks();
	int frameIndex = 0;

	//Displays all the textures and their information at the start of runtime
	//for (const auto& texture : textures) {
	//	std::cout << "Texture ID: " << texture.m_TextureID << std::endl;
	//	std::cout << "Width: " << texture.m_Width << ", Height: " << texture.m_Height << ", Channels: " << texture.m_NumChannels << std::endl;
	//	std::cout << "Sprite Sheet Size: (" << texture.m_SpriteSheetSize.x << ", " << texture.m_SpriteSheetSize.y << ")" << std::endl;
	//}

	// Draw test for UI
		// Create transformation matrices for each character
	glm::mat4 transformP = glm::mat4(1.0f);
	transformP = glm::translate(transformP, glm::vec3(0.0f, 0.0f, 0.0f)); // Position for 'P'

	glm::mat4 transformL = glm::mat4(1.0f);
	transformL = glm::translate(transformL, glm::vec3(0.2f, 0.0f, 0.0f)); // Position for 'l'

	glm::mat4 transformA = glm::mat4(1.0f);
	transformA = glm::translate(transformA, glm::vec3(0.4f, 0.0f, 0.0f)); // Position for 'a'

	glm::mat4 transformY = glm::mat4(1.0f);
	transformY = glm::translate(transformY, glm::vec3(0.6f, 0.0f, 0.0f)); // Position for 'y'

	glm::mat4 transformE = glm::mat4(1.0f);
	transformE = glm::translate(transformE, glm::vec3(0.8f, 0.0f, 0.0f)); // Position for 'e'

	glm::mat4 transformR = glm::mat4(1.0f);
	transformR = glm::translate(transformR, glm::vec3(1.0f, 0.0f, 0.0f)); // Position for 'r'

	// Get the location of the transform uniform
	GLint transformLoc = glGetUniformLocation(shaderProgram, "transform");

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

		if (animationTime >= frameDuration)
		{
			frameIndex = (frameIndex + 1) % (int)(LonerA.GetSpriteSheetSize().x * LonerA.GetSpriteSheetSize().y);
			animationTime -= frameDuration;
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
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 0);

		// Draw Object 1 with LonerA texture
		LonerA.Bind(0);
		glUniform1i(frameIndexLocation, frameIndex);
		glUniform2fv(spriteSheetSizeLocation, 1, &LonerA.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 4);

		// Draw Object 2 with LonerB texture
		LonerB.Bind(1);
		glUniform1i(frameIndexLocation, frameIndex);
		glUniform2fv(spriteSheetSizeLocation, 1, &LonerB.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 1);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 8);

		// Draw Object 3 with LonerC texture
		LonerC.Bind(2);
		glUniform1i(frameIndexLocation, frameIndex);
		glUniform2fv(spriteSheetSizeLocation, 1, &LonerC.GetSpriteSheetSize()[0]);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 2);
		glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 12);

		// Draw Object 4 with PUDive texture
		PUDive.Bind(3);
		glUniform1i(frameIndexLocation, frameIndex);
		glUniform2fv(spriteSheetSizeLocation, 1, &PUDive.GetSpriteSheetSize()[0]);
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

		SDL_GL_SwapWindow(window);
	}



	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}