#include "SuperBlock.h"



SuperBlock::SuperBlock(std::vector<BlockType>& _types) : types (_types), mesh(_types) {
}


SuperBlock::~SuperBlock()
{
}

SuperBlockMesh & SuperBlock::getMesh() {
	return mesh;
}

Coordinates & SuperBlock::getCoords() {
	return coods;
}

SuperBlockDB & SuperBlock::getContent() {
	return blocks;
}

void SuperBlock::createMesh() {
	mesh.create(blocks);
}

void SuperBlock::updateMesh() {
	//mesh.update();
}
