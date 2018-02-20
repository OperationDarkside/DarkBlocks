#pragma once
#ifndef VERTEXATTRIBUTE_H
#define VERTEXATTRIBUTE_H

#include <string>
#include <GL/glew.h>

#include "ShaderProgram.h"

class VertexAttribute
{
public:
	VertexAttribute(std::string _name);
	~VertexAttribute();

	void init(ShaderProgram& program);

	void bind(unsigned size, unsigned buffer_size, unsigned buffer_offset);

private:
	GLint attribute;
	std::string name;
};

#endif // !VERTEXATTRIBUTE_H