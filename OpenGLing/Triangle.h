#pragma once

#include <iostream>
#include <chrono>

#include <GL/glew.h>

class Triangle
{
public:
	Triangle();
	~Triangle();

	void init();

	void draw(std::chrono::microseconds ms_elapsed);

private:
	GLuint vertexBufferObj;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	GLint posAttrib;
	GLint colAttrib;

	std::chrono::time_point<std::chrono::steady_clock> t_start = std::chrono::high_resolution_clock::now();

	float vertices[15] = {
		0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1 (X, Y)
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2 (X, Y)
		-0.5f, -0.5f, 1.0f, 0.0f, 1.0f  // Vertex 3 (X, Y)
	};
	const char* vertexSource = R"glsl(
		#version 150 core

		in vec2 position;
		in vec3 color;

		out vec3 Color;

		void main()
		{
			Color = color;
			gl_Position = vec4(position, 0.0, 1.0);
		}
	)glsl";
	const char* fragmentSource = R"glsl(
		#version 150 core

		in vec3 Color;

		out vec4 outColor;

		void main()
		{
			outColor = vec4(Color, 1.0);
		}
	)glsl";

	void createShader(GLuint& shader, const char* shaderSource, GLenum type);
};

