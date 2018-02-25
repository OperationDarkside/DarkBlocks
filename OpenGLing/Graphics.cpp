#include "Graphics.h"



Graphics::Graphics(Input& input) : input (input), cube(input) {
	initGlew();

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);

	initVertexArrayObject();
	init();
}


Graphics::~Graphics() {
	glDeleteVertexArrays(1, &vertexArrayObj);
}

void Graphics::init() {
	//rectangle.init();
	cube.init();
}

void Graphics::draw(std::chrono::microseconds ms_elapsed) {
	//rectangle.draw();
	cube.draw(ms_elapsed);
}

void Graphics::initGlew() {
	glewExperimental = GL_TRUE;
	glewInit();
}

void Graphics::initVertexArrayObject() {
	glGenVertexArrays(1, &vertexArrayObj);
	glBindVertexArray(vertexArrayObj);
}
