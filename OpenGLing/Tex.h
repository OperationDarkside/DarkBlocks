#pragma once

#include <GL/glew.h>

class Tex
{
public:
	Tex();
	~Tex();

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
	GLint texAttrib;
	GLuint tx[2];

	float vertices[28] = {
		//  Position      Color             Texcoords
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
		0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
	};
	GLuint elements[6] = {
		0, 1, 2,
		2, 3, 0
	};
	const GLchar* vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    in vec3 color;
    in vec2 texcoord;
    out vec3 Color;
    out vec2 Texcoord;
    void main()
    {
        Color = color;
        Texcoord = texcoord;
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";
	const GLchar* fragmentSource = R"glsl(
    #version 150 core
    in vec3 Color;
    in vec2 Texcoord;
    out vec4 outColor;
    uniform sampler2D texMine;
	uniform sampler2D texKitten;
    void main()
    {
		vec4 colMine = texture(texMine, Texcoord);
		vec4 colKitten = texture(texKitten, Texcoord);

        outColor = mix(colMine, colKitten, 0.5) * vec4(Color, 1.0);
    }
)glsl";

	void createShader(GLuint& shader, const char* shaderSource, GLenum type);
};

