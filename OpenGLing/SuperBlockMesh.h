#pragma once

#ifndef SUPERBLOCKMESH_H
#define SUPERBLOCKMESH_H

#include <array>
#include <vector>

#include <GL/glew.h>

#include "Coordinates.h"
#include "BlockType.h"

struct BlockFaces {
	bool front;
	bool back;
	bool left;
	bool right;
	bool top;
	bool bottom;
	bool shouldRender;
	bool todo;
};

using Block = unsigned;
using SuperBlockDB = std::array<std::array<std::array<Block, 16>, 16>, 16>; // xyz
//using BlockFaces = std::array<bool, 8>; // front, back, left, right, top, bottom
using SuperBlockMeshFaces = std::array<std::array<std::array<BlockFaces, 16>, 16>, 16>; // xyz

class SuperBlockMesh
{
public:
	SuperBlockMesh(std::vector<BlockType>& _types);
	~SuperBlockMesh();

	void create(SuperBlockDB& db);
private:
	std::vector<BlockType>& types;

	SuperBlockMeshFaces faces;
	std::vector<unsigned> elements;

	BlockFaces checkFaces(SuperBlockDB& db, unsigned blocktype_id, unsigned short x, unsigned short y, unsigned short z);
	bool getOpaqueness(SuperBlockDB& db, unsigned short x, unsigned short y, unsigned short z);
	void createBlockElements(BlockFaces& checkedFaces, unsigned short x, unsigned short y, unsigned short z);
};

#endif // !SUPERBLOCKMESH_H