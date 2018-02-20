#pragma once

#include <iostream>
#include <GL/glew.h>

class Rectangle
{
public:
	Rectangle();
	~Rectangle();

	void init();

	void draw();

private:
	GLuint vertexBufferObj;
	GLuint ebo;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	GLint posAttrib;
	GLint colAttrib;

	GLuint elements[6] = {
		0, 1, 2,
		2, 3, 0
	};
	float vertices[20] = {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
		0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
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

