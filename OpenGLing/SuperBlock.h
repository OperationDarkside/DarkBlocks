#pragma once

#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H

#include "SuperBlockMesh.h"

//using Block = unsigned;
//using SuperBlockDB = std::array<std::array<std::array<Block, 16>, 16>, 16>;

class SuperBlock
{
public:
	SuperBlock(std::vector<BlockType>& _types);
	~SuperBlock();

	Coordinates& getCoords();
	SuperBlockDB& getContent();
	SuperBlockMesh& getMesh();

	void createMesh();
	void updateMesh();

private:
	Coordinates coods;
	SuperBlockMesh mesh;
	SuperBlockDB blocks;
	std::vector<BlockType>& types;
};

#endif // !SUPERBLOCK_H