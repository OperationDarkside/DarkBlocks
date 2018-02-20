#include "BlockType.h"



BlockType::BlockType() {

}


BlockType::~BlockType() {

}

unsigned BlockType::getId() {
	return id;
}

void BlockType::setId(unsigned _id) {
	id = _id;
}

std::string & BlockType::getName() {
	return name;
}

void BlockType::setName(std::string _name) {
	name = _name;
}

bool BlockType::getOpaque() {
	return opaque;
}

void BlockType::setOpaque(bool _opaque) {
	opaque = _opaque;
}
