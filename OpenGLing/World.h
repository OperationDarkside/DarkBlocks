#pragma once

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Coordinates.h"
#include "BlockType.h"
#include "SuperBlockMesh.h"
#include "SuperBlock.h"

class World
{
public:
	World();
	~World();

	void render();

	SuperBlock& getSuperblock();

	std::vector<SuperBlock> superblocks;
	std::vector<BlockType> types;
};

#endif // !WORLD_H