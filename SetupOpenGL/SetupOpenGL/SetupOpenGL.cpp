#include <iostream>
#include <glad/glad.h>
#include <SDL.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include "Texture.h"

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


	// my triangle
// 	float vertices[] = {
// 	 0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
// 	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
// 	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
// 	};

// 	float vertices[] = {
// 		0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top right
// 		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
// 	   -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom left
// 	   -0.5f,  0.5f, 0.0f, 1.0f, 1.0f  // top left
// 	};

	float vertices[] = {
		// positions         // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};	

	GLuint vbo; // vertex buffer object
	glGenBuffers(1, &vbo); // Generate 1 buffer

	GLuint ebo;
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


	//insert ur textures here


	Texture texture("graphics/clone.bmp");
	texture.SetSpriteSheetSize(glm::vec2(4.0f, 5.0f));


	glUseProgram(shaderProgram);
	
	GLuint textureLocation;

	textureLocation = glGetUniformLocation(shaderProgram, "ourTexture");
	
	glUniform1i(textureLocation, 0);
	glClearColor(0.2f, 0.5f, 0.3f, 1.0f);

	SDL_Event windowEvent;
	float lastTime = SDL_GetTicks();
	int frameIndex = 0;


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
			frameIndex = (frameIndex + 1) % (int)(texture.m_SpriteSheetSize.x * texture.m_SpriteSheetSize.y);
			animationTime -= frameDuration;
		}

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		glBindVertexArray(vao);

		texture.Bind(0);

		GLint frameIndexLocation = glGetUniformLocation(shaderProgram, "frameIndex");
		GLint spriteSheetSizeLocation = glGetUniformLocation(shaderProgram, "spriteSheetSize");
		glUniform1i(frameIndexLocation, frameIndex);
		glUniform2fv(spriteSheetSizeLocation, 1, &texture.m_SpriteSheetSize[0]);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}