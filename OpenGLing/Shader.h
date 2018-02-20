#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/glew.h>

class Shader
{
public:
	Shader(GLenum _type);
	~Shader();

	void init(std::string filename);

	GLuint& getId();

private:
	GLuint shader;
	GLenum type;

	std::string source;
};

#endif // !SHADER_H