#include "SuperBlockMesh.h"



SuperBlockMesh::SuperBlockMesh(std::vector<BlockType>& _types) : types(_types) {
	data.reserve(400000);
}


SuperBlockMesh::~SuperBlockMesh() {
}

void SuperBlockMesh::create(SuperBlockDB& db) {
	for (unsigned short x = 0; x < 16; x++) {
		for (unsigned short y = 0; y < 16; y++) {
			for (unsigned short z = 0; z < 16; z++) {
				Block blocktype_id = db[x][y][z];
				BlockType& type = types[blocktype_id];
				if (!type.getOpaque()) {
					continue;
				}
				// TODO: unordered_map of type_id and opaqueness

				BlockFaces checkedFaces = checkFaces(db, blocktype_id, x, y, z);

				//BlockFaces checkedFaces;

				//faces[x][y][z] = checkedFaces;

				if (checkedFaces.shouldRender) {
					createBlockElements(checkedFaces, x, y, z);
				}

			}
		}
	}
}

std::vector<float>& SuperBlockMesh::getMeshData()
{
	return data;
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
	//return type_opaque_index[blocktype_id];
}

void SuperBlockMesh::createBlockElements(BlockFaces & checkedFaces, unsigned short x, unsigned short y, unsigned short z) {
	float xf = static_cast<float>(x);
	float yf = static_cast<float>(y);
	float zf = static_cast<float>(z);

	float front_bottom_left[] { xf, yf, zf };
	float front_bottom_right[] { xf + 1, yf, zf };
	float front_top_left[] { xf, yf + 1, zf };
	float front_top_right[] { xf + 1, yf + 1, zf };
	float back_bottom_left[] { xf, yf, zf + 1 };
	float back_bottom_right[] { xf + 1, yf, zf + 1 };
	float back_top_left[] { xf, yf + 1, zf + 1 };
	float back_top_right[] { xf + 1, yf + 1, zf + 1 };
	
	
	if (!checkedFaces.front) {
		data.insert(data.end(), {
				front_bottom_left[0],
				front_bottom_left[1],
				front_bottom_left[2],
				1,
				1,
				front_bottom_right[0],
				front_bottom_right[1],
				front_bottom_right[2],
				0,
				1,
				front_top_right[0],
				front_top_right[1],
				front_top_right[2],
				0,
				0,
				front_top_right[0],
				front_top_right[1],
				front_top_right[2],
				0,
				0,
				front_top_left[0],
				front_top_left[1],
				front_top_left[2],
				1,
				0,
				front_bottom_left[0],
				front_bottom_left[1],
				front_bottom_left[2],
				1,
				1
			});
		//for (size_t i = 0; i < 6; i++) {
			/*data.push_back(frontFace[i].vert.x + xf);
			data.push_back(frontFace[i].vert.y + yf);
			data.push_back(frontFace[i].vert.z + zf);
			data.push_back(frontFace[i].coord.u);
			data.push_back(frontFace[i].coord.v);*/
			/*unsigned char tmp = i * 5;
			data.insert(data.end(), {
				frontFace[tmp] + xf,
				frontFace[tmp + 1] + yf,
				frontFace[tmp + 2] + zf,
				frontFace[tmp + 3],
				frontFace[tmp + 4]
				});*/

			/*data.insert(data.end(), {
				frontFace[i].vert.x + xf,
				frontFace[i].vert.y + yf,
				frontFace[i].vert.z + zf,
				frontFace[i].coord.u,
				frontFace[i].coord.v
				});*/
		//}

	}
	if (!checkedFaces.back) {
		//for (size_t i = 0; i < 6; i++) {
			/*data.push_back(backFace[i].vert.x + xf);
			data.push_back(backFace[i].vert.y + yf);
			data.push_back(backFace[i].vert.z + zf);
			data.push_back(backFace[i].coord.u);
			data.push_back(backFace[i].coord.v);*/
			/*data.insert(data.end(), {
				backFace[i].vert.x + xf,
				backFace[i].vert.y + yf,
				backFace[i].vert.z + zf,
				backFace[i].coord.u,
				backFace[i].coord.v
				});*/
			/*unsigned char tmp = i * 5;
			data.insert(data.end(), {
				backFace[tmp] + xf,
				backFace[tmp + 1] + yf,
				backFace[tmp + 2] + zf,
				backFace[tmp + 3],
				backFace[tmp + 4]
				});*/
		//}
		data.insert(data.end(), {
			back_bottom_left[0],
			back_bottom_left[1],
			back_bottom_left[2],
			0,
			1,
			back_top_left[0],
			back_top_left[1],
			back_top_left[2],
			0,
			0,
			back_top_right[0],
			back_top_right[1],
			back_top_right[2],
			1,
			0,
			back_top_right[0],
			back_top_right[1],
			back_top_right[2],
			1,
			0,
			back_bottom_right[0],
			back_bottom_right[1],
			back_bottom_right[2],
			1,
			1,
			back_bottom_left[0],
			back_bottom_left[1],
			back_bottom_left[2],
			0,
			1
			});
	}
	if (!checkedFaces.left) {
		//for (size_t i = 0; i < 6; i++) {
			/*data.insert(data.end(), {
				leftFace[i].vert.x + xf,
				leftFace[i].vert.y + yf,
				leftFace[i].vert.z + zf,
				leftFace[i].coord.u,
				leftFace[i].coord.v
				});*/
			/*unsigned char tmp = i * 5;
			data.insert(data.end(), {
				leftFace[tmp] + xf,
				leftFace[tmp + 1] + yf,
				leftFace[tmp + 2] + zf,
				leftFace[tmp + 3],
				leftFace[tmp + 4]
				});*/
		//}
		data.insert(data.end(), {
			back_bottom_left[0],
			back_bottom_left[1],
			back_bottom_left[2],
			1,
			1,
			front_bottom_left[0],
			front_bottom_left[1],
			front_bottom_left[2],
			0,
			1,
			front_top_left[0],
			front_top_left[1],
			front_top_left[2],
			0,
			0,
			front_top_left[0],
			front_top_left[1],
			front_top_left[2],
			0,
			0,
			back_top_left[0],
			back_top_left[1],
			back_top_left[2],
			1,
			0,
			back_bottom_left[0],
			back_bottom_left[1],
			back_bottom_left[2],
			1,
			1
			});
	}
	if (!checkedFaces.right) {
		//for (size_t i = 0; i < 6; i++) {
			/*data.insert(data.end(), {
				rightFace[i].vert.x + xf,
				rightFace[i].vert.y + yf,
				rightFace[i].vert.z + zf,
				rightFace[i].coord.u,
				rightFace[i].coord.v
				});*/
			/*unsigned char tmp = i * 5;
			data.insert(data.end(), {
				rightFace[tmp] + xf,
				rightFace[tmp + 1] + yf,
				rightFace[tmp + 2] + zf,
				rightFace[tmp + 3],
				rightFace[tmp + 4]
				});*/
		//}
		data.insert(data.end(), {
			back_bottom_right[0],
			back_bottom_right[1],
			back_bottom_right[2],
			0,
			0,
			back_top_right[0],
			back_top_right[1],
			back_top_right[2],
			1,
			0,
			front_top_right[0],
			front_top_right[1],
			front_top_right[2],
			1,
			1,
			front_top_right[0],
			front_top_right[1],
			front_top_right[2],
			1,
			1,
			front_bottom_right[0],
			front_bottom_right[1],
			front_bottom_right[2],
			0,
			1,
			back_bottom_right[0],
			back_bottom_right[1],
			back_bottom_right[2],
			0,
			0
			});
	}
	//if (!checkedFaces.top) {
		//for (size_t i = 0; i < 6; i++) {
			/*data.insert(data.end(), {
				topFace[i].vert.x + xf,
				topFace[i].vert.y + yf,
				topFace[i].vert.z + zf,
				topFace[i].coord.u,
				topFace[i].coord.v
				});*/
			/*unsigned char tmp = i * 5;
			data.insert(data.end(), {
				topFace[tmp] + xf,
				topFace[tmp + 1] + yf,
				topFace[tmp + 2] + zf,
				topFace[tmp + 3],
				topFace[tmp + 4]
				});*/
		//}
		/*data.insert(data.end(), {
			back_top_right[0],
			back_top_right[1],
			back_top_right[2],
			0,
			0,
			back_top_left[0],
			back_top_left[1],
			back_top_left[2],
			1,
			0,
			front_top_left[0],
			front_top_left[1],
			front_top_left[2],
			1,
			1,
			front_top_left[0],
			front_top_left[1],
			front_top_left[2],
			1,
			1,
			front_top_right[0],
			front_top_right[1],
			front_top_right[2],
			0,
			1,
			back_top_right[0],
			back_top_right[1],
			back_top_right[2],
			0,
			0
			});
	}*/
	if (!checkedFaces.bottom) {
		//for (size_t i = 0; i < 6; i++) {
			/*data.insert(data.end(), {
				bottomFace[i].vert.x + xf,
				bottomFace[i].vert.y + yf,
				bottomFace[i].vert.z + zf,
				bottomFace[i].coord.u,
				bottomFace[i].coord.v
				});*/
			/*unsigned char tmp = i * 5;
			data.insert(data.end(), {
				bottomFace[tmp] + xf,
				bottomFace[tmp + 1] + yf,
				bottomFace[tmp + 2] + zf,
				bottomFace[tmp + 3],
				bottomFace[tmp + 4]
				});*/
		//}
		data.insert(data.end(), {
			front_bottom_left[0],
			front_bottom_left[1],
			front_bottom_left[2],
			0,
			0,
			back_bottom_left[0],
			back_bottom_left[1],
			back_bottom_left[2],
			1,
			0,
			back_bottom_right[0],
			back_bottom_right[1],
			back_bottom_right[2],
			1,
			1,
			back_bottom_right[0],
			back_bottom_right[1],
			back_bottom_right[2],
			1,
			1,
			front_bottom_right[0],
			front_bottom_right[1],
			front_bottom_right[2],
			0,
			1,
			front_bottom_left[0],
			front_bottom_left[1],
			front_bottom_left[2],
			0,
			0
			});
	}

	/*const unsigned short num = 16;
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
	}*/
}
