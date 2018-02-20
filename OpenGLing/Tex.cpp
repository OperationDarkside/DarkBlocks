#include "Tex.h"

#include <iostream>

#include <SFML/Graphics.hpp>



Tex::Tex() {
}


Tex::~Tex() {
	glDeleteTextures(2, tx);

	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vertexBufferObj);
	
}

void Tex::init() {
	// VBO
	glGenBuffers(1, &vertexBufferObj); // Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// EBO
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Shader
	createShader(vertexShader, vertexSource, GL_VERTEX_SHADER);
	createShader(fragmentShader, fragmentSource, GL_FRAGMENT_SHADER);

	// Shader Program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Bind position
	posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

	// Bind color
	colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	// Bind texcoord
	texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

	// Load Mine
	glGenTextures(2, tx);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tx[0]);

	sf::Image imgMine;
	if (!imgMine.loadFromFile("minepun.jpg")) {
		throw "Image not loadable!";
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgMine.getSize().x, imgMine.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgMine.getPixelsPtr());
	glUniform1i(glGetUniformLocation(shaderProgram, "texKitten"), 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load Kitten
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tx[1]);

	sf::Image imgKitten;
	if (!imgKitten.loadFromFile("sample.png")) {
		throw "Image not loadable!";
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgKitten.getSize().x, imgKitten.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgKitten.getPixelsPtr());
	glUniform1i(glGetUniformLocation(shaderProgram, "texMine"), 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Tex::draw() {
	// Clear the screen to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw a rectangle from the 2 triangles using 6 indices
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Tex::createShader(GLuint & shader, const char * shaderSource, GLenum type) {
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSource, 0);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		throw "Shader compile error!";
	}
	char buffer[512];
	glGetShaderInfoLog(shader, 512, 0, buffer);
	std::cout << buffer;
}
