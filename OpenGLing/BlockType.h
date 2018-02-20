#pragma once

#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <string>

//#include <GL/glew.h>
#include <glm.hpp>

class BlockType
{
public:
	BlockType();
	~BlockType();

	// ID
	unsigned getId();
	void setId(unsigned _id);
	// Name
	std::string& getName();
	void setName(std::string _name);
	// Opaque
	bool getOpaque();
	void setOpaque(bool _opaque);

private:
	unsigned id;
	std::string name;
	bool opaque = true;
};

#endif // !BLOCKTYPE_H