#include "ShaderProgram.h"



ShaderProgram::ShaderProgram() {
	
}


ShaderProgram::~ShaderProgram() {
	glDeleteProgram(program);
}

void ShaderProgram::init() {
	program = glCreateProgram();
}

void ShaderProgram::use() {
	glLinkProgram(program);
	glUseProgram(program);
}

void ShaderProgram::addShader(Shader & shader) {
	glAttachShader(program, shader.getId());
}

void ShaderProgram::bindFragDataLocation(std::string name, unsigned colorNumber) {
	glBindFragDataLocation(program, colorNumber, name.data());
}

GLuint & ShaderProgram::getId()
{
	return program;
}
