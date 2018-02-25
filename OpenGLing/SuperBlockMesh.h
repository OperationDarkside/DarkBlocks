#pragma once

#ifndef SUPERBLOCKMESH_H
#define SUPERBLOCKMESH_H

#include <array>
#include <vector>

#include <GL/glew.h>

#include "Coordinates.h"
#include "BlockType.h"

class BlockFaces {
public:
	bool front = false;
	bool back = false;
	bool left = false;
	bool right = false;
	bool top = false;
	bool bottom = false;
	bool shouldRender = true;
	bool todo;
};
class Vertex {
public:
	float x = 0;
	float y = 0;
	float z = 0;
};
class TexCoord {
public:
	float u = 0;
	float v = 0;
};
class Element {
public:
	Vertex vert;
	TexCoord coord;
};

using Block = unsigned short;
using SuperBlockDB = std::array<std::array<std::array<Block, 16>, 16>, 16>; // xyz
//using BlockFaces = std::array<bool, 8>; // front, back, left, right, top, bottom
using SuperBlockMeshFaces = std::array<std::array<std::array<BlockFaces, 16>, 16>, 16>; // xyz

class SuperBlockMesh
{
public:
	SuperBlockMesh(std::vector<BlockType>& _types);
	~SuperBlockMesh();

	void create(SuperBlockDB& db);

	std::vector<float>& getMeshData();
private:
	std::vector<BlockType>& types;

	SuperBlockMeshFaces faces;
	//std::vector<unsigned> elements;
	std::vector<float> data;

	BlockFaces checkFaces(SuperBlockDB& db, unsigned blocktype_id, unsigned short x, unsigned short y, unsigned short z);
	bool getOpaqueness(SuperBlockDB& db, unsigned short x, unsigned short y, unsigned short z);
	void createBlockElements(BlockFaces& checkedFaces, unsigned short x, unsigned short y, unsigned short z);

	std::array<float, 30> frontFace{
		0,0,0,0,0,
		1,0,0,1,0,
		1,1,0,1,1,
		1,1,0,1,1,
		0,1,0,0,1,
		0,0,0,0,0
	};
	std::array<float, 30> backFace{
		0,0,1,0,0,
		0,1,1,1,0,
		1,1,1,1,1,
		1,1,1,1,1,
		1,0,1,0,1,
		0,0,1,0,0
	};
	std::array<float, 30> leftFace{
		0,0,1,0,0,
		0,0,0,1,0,
		0,1,0,1,1,
		0,1,0,1,1,
		0,1,1,0,1,
		0,0,1,0,0
	};
	std::array<float, 30> rightFace{
		1,0,1,0,0,
		1,1,1,1,0,
		1,1,0,1,1,
		1,1,0,1,1,
		1,0,0,0,1,
		1,0,1,0,0
	};
	std::array<float, 30> topFace{
		1,1,1,0,0,
		0,1,1,1,0,
		0,1,0,1,1,
		0,1,0,1,1,
		1,1,0,0,1,
		1,1,1,0,0
	};
	std::array<float, 30> bottomFace{
		0,0,0,0,0,
		0,0,1,1,0,
		1,0,1,1,1,
		1,0,1,1,1,
		1,0,0,0,1,
		0,0,0,0,0
	};
};

#endif // !SUPERBLOCKMESH_H