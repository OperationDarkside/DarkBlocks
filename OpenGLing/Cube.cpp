#include "Cube.h"

#include <iostream>

#include <SFML/Graphics.hpp>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>


Cube::Cube(Input& input) :
	input(input),
	vShader(GL_VERTEX_SHADER),
	fShader(GL_FRAGMENT_SHADER),
	attrPosition("position"),
	attrColor("color"),
	attrTexCoord("texcoord")
{
}


Cube::~Cube() {
	/*glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	*/

	glDeleteBuffers(1, &vertexBufferObj);
}

void Cube::init() {
	// VBO
	glGenBuffers(1, &vertexBufferObj); // Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	std::vector<float>& meshdata = world.getSuperblock().getMesh().getMeshData();
	vertices_num = meshdata.size();
	glBufferData(GL_ARRAY_BUFFER, meshdata.size() * sizeof(float), &meshdata.front(), GL_STATIC_DRAW);

	// Shader
	//createShader(vertexShader, vertexSource, GL_VERTEX_SHADER);
	//createShader(fragmentShader, fragmentSource, GL_FRAGMENT_SHADER);
	vShader.init("cube.vert");
	fShader.init("cube.frag");

	// Shader Program
	/*shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	*/
	program.init();
	program.addShader(vShader);
	program.addShader(fShader);
	program.bindFragDataLocation("outColor", 0);
	program.use();


	// Bind position
	/*posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	*/
	attrPosition.init(program);
	attrPosition.bind(3, 5, 0);

	// Bind color
	/*colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	*/
	//attrColor.init(program);
	//attrColor.bind(3, 8, 3);

	// Bind texcoord
	/*texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	*/
	attrTexCoord.init(program);
	attrTexCoord.bind(2, 5, 3);

	// Load Mine
	glGenTextures(2, tx);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tx[0]);

	sf::Image imgMine;
	if (!imgMine.loadFromFile("minepun.jpg")) {
		throw "Image not loadable!";
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgMine.getSize().x, imgMine.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgMine.getPixelsPtr());
	glUniform1i(glGetUniformLocation(program.getId(), "texKitten"), 0);

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
	glUniform1i(glGetUniformLocation(program.getId(), "texMine"), 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)700, 0.1f, 100.0f);

	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	/*glm::mat4 View = glm::lookAt(
		glm::vec3(2, 1, 1), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);*/

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	mvp = input.ProjectionMatrix * input.ViewMatrix * Model;

	mvp_handle = glGetUniformLocation(program.getId(), "mvp");
	glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, glm::value_ptr(mvp));
}

void Cube::draw(std::chrono::microseconds ms_elapsed) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	input.compute(ms_elapsed);
	glm::mat4 Model = glm::mat4(1.0f);
	mvp = input.ProjectionMatrix * input.ViewMatrix * Model;
	glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, glm::value_ptr(mvp));

	// Draw a rectangle from the 2 triangles using 6 indices
	glDrawArrays(GL_TRIANGLES, 0, vertices_num * sizeof(GLfloat));
}

void Cube::createShader(GLuint & shader, const char * shaderSource, GLenum type) {
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
