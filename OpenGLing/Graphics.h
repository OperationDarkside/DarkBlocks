#pragma once

#include <chrono>

#define GLEW_STATIC
#include <GL/glew.h>
#include "Triangle.h"
#include "Rectangle.h"
#include "Tex.h"
#include "Cube.h"
#include "Input.h"

class Graphics
{
public:
	Graphics(Input& input);
	~Graphics();

	void draw(std::chrono::microseconds ms_elapsed);

private:
	GLuint vertexArrayObj;
	//Triangle triangle;
	//Rectangle rectangle;
	//Tex tx;
	Cube cube;
	Input& input;

	void initGlew();
	void initVertexArrayObject();
	void init();
};

