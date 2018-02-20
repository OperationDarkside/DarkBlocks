#include "Shader.h"

#include <fstream>


Shader::Shader(GLenum _type) : type(_type) {
}


Shader::~Shader() {
	glDeleteShader(shader);
}

void Shader::init(std::string filename) {
	std::ifstream fs(filename);
	std::string line;
	while (std::getline(fs, line)) {
		source += line + '\n';
	}
	fs.close();

	const char* c_source = source.data();

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &c_source, 0);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		char buffer[512];
		glGetShaderInfoLog(shader, 512, 0, buffer);
		throw buffer;
	}
}

GLuint & Shader::getId() {
	return shader;
}
