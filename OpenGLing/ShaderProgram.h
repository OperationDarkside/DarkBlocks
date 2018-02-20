#pragma once

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>

#include <GL/glew.h>

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void init();

	void addShader(Shader& shader);

	void bindFragDataLocation(std::string name, unsigned colorNumber);

	void use();

	GLuint& getId();

private:
	GLuint program;
};

#endif // !SHADERPROGRAM_H