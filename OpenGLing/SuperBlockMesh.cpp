#include "SuperBlockMesh.h"



SuperBlockMesh::SuperBlockMesh(std::vector<BlockType>& _types) : types(_types) {
}


SuperBlockMesh::~SuperBlockMesh() {
}

void SuperBlockMesh::create(SuperBlockDB& db) {
	for (unsigned short x = 0; x < 16; x++) {
		for (unsigned short y = 0; y < 16; y++) {
			for (unsigned short z = 0; z < 16; z++) {
				Block blocktype_id = db[x][y][z];
				BlockType& type = types[blocktype_id];
				// TODO: unordered_map of type_id and opaqueness

				BlockFaces checkedFaces = checkFaces(db, blocktype_id, x, y, z);

				faces[x][y][z] = checkedFaces;

				if (checkedFaces.shouldRender) {
					createBlockElements(checkedFaces, x, y, z);
				}

			}
		}
	}
}

BlockFaces SuperBlockMesh::checkFaces(SuperBlockDB& db, unsigned blocktype_id, unsigned short x, unsigned short y, unsigned short z) {
	BlockFaces checkedFaces;

	// front
	if (z != 0) {
		checkedFaces.front = getOpaqueness(db, x, y, z - 1);
	}
	// back
	if (z != 15) {
		checkedFaces.back = getOpaqueness(db, x, y, z + 1);
	}
	// left
	if (x != 0) {
		checkedFaces.left = getOpaqueness(db, x - 1, y, z);
	}
	// right
	if (x != 15) {
		checkedFaces.right = getOpaqueness(db, x + 1, y, z);
	}
	// top
	if (y != 15) {
		checkedFaces.top = getOpaqueness(db, x, y + 1, z);
	}
	// bottom
	if (y != 0) {
		checkedFaces.bottom = getOpaqueness(db, x, y - 1, z);
	}

	if (
		checkedFaces.front &&
		checkedFaces.back &&
		checkedFaces.left &&
		checkedFaces.right &&
		checkedFaces.top &&
		checkedFaces.bottom
		)
	{
		checkedFaces.shouldRender = false;
	}

	return checkedFaces;
}

bool SuperBlockMesh::getOpaqueness(SuperBlockDB& db, unsigned short x, unsigned short y, unsigned short z) {
	Block blocktype_id = db[x][y][z];
	BlockType& type = types[blocktype_id];
	return type.getOpaque();
}

void SuperBlockMesh::createBlockElements(BlockFaces & checkedFaces, unsigned short x, unsigned short y, unsigned short z) {
	const unsigned short num = 16;
	const unsigned short num_q = 16 * 16;

	unsigned tmp1 = z * num_q + x;
	unsigned Pos = tmp1 + y * num;
	unsigned TopPos = z * num_q + (y + 1) * num + x;

	unsigned tmp2 = (z + 1) * num_q + x;
	unsigned PosBack = tmp2 + y * num;
	unsigned TopPosBack = tmp2 + (y + 1) * num;

	unsigned front_bottom_left = Pos + y;
	unsigned front_bottom_right = front_bottom_left + 1;
	unsigned front_top_left = TopPos + y + 1;
	unsigned front_top_right = front_top_left + 1;
	unsigned back_bottom_left = PosBack + y;
	unsigned back_bottom_right = back_bottom_left + 1;
	unsigned back_top_left = TopPosBack + y + 1;
	unsigned back_top_right = back_top_left + 1;


	if (!checkedFaces.front) {
		elements.insert(elements.end(), { front_bottom_left, front_top_right, front_top_left, front_bottom_left, front_bottom_right, front_top_right });
	}
	if (!checkedFaces.back) {
		elements.insert(elements.end(), { back_bottom_left, back_top_right, back_top_left, back_bottom_left, back_bottom_right, back_top_right });
	}
	if (!checkedFaces.left) {
		elements.insert(elements.end(), { back_bottom_left, front_top_left, back_top_left, back_bottom_left, front_bottom_left, front_top_left });
	}
	if (!checkedFaces.right) {
		elements.insert(elements.end(), { back_bottom_right, front_top_right, back_top_right, back_bottom_right, front_bottom_right, front_top_right });
	}
	if (!checkedFaces.top) {
		elements.insert(elements.end(), { back_top_left, front_top_left, back_top_right, back_top_right, front_top_left, front_top_right });
	}
	if (!checkedFaces.bottom) {
		elements.insert(elements.end(), { back_bottom_left, front_bottom_left, back_bottom_right, back_bottom_right, front_bottom_left, front_bottom_right });
	}
}
