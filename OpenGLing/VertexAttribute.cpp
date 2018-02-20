#include "VertexAttribute.h"



VertexAttribute::VertexAttribute(std::string _name) : name(std::move(_name)) {
	
}


VertexAttribute::~VertexAttribute() {

}

void VertexAttribute::init(ShaderProgram & program) {
	attribute = glGetAttribLocation(program.getId(), name.data());
	glEnableVertexAttribArray(attribute);
}

void VertexAttribute::bind(unsigned size, unsigned buffer_size, unsigned buffer_offset) {
	glVertexAttribPointer(
		attribute,
		size,
		GL_FLOAT,
		GL_FALSE,
		buffer_size * sizeof(GLfloat),
		(void*)(buffer_offset * sizeof(GLfloat))
	);
}
