#include "World.h"
#include <chrono>
#include <iostream>


World::World() {
	

	BlockType airBlock;
	airBlock.setId(0);
	airBlock.setName("Air");
	airBlock.setOpaque(false);
	types.push_back(std::move(airBlock));

	BlockType stoneBlock;
	stoneBlock.setId(1);
	stoneBlock.setName("Stone");
	stoneBlock.setOpaque(true);
	types.push_back(std::move(stoneBlock));

	SuperBlock sb(types);

	SuperBlockDB& db = sb.getContent();
	for (unsigned i = 0; i < 16; i++) {
		for (unsigned g = 0; g < 16; g++) {
			for (unsigned h = 0; h < 16; h++) {
				db[i][g][h] = rand() % 2;
			}
		}
	}
	auto ts1 = std::chrono::system_clock::now();

	sb.createMesh();
	superblocks.push_back(std::move(sb));

	auto ts2 = std::chrono::system_clock::now();

	std::chrono::microseconds exec_time = std::chrono::duration_cast<std::chrono::microseconds>(ts2 - ts1);
	std::cout << exec_time.count() << '\n';
}


World::~World()
{
}

void World::render() {
	SuperBlock& sb = superblocks[0];


}

SuperBlock & World::getSuperblock() {
	return superblocks[0];
}
