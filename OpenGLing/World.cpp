#include "World.h"



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
	sb.updateMesh();
	superblocks.push_back(std::move(sb));
}


World::~World()
{
}
