#include "GenBindBuff.h"

void GenBindBuff(unsigned int numBuffers, unsigned int* buffer, float attributes[]) {
	glGenBuffers(numBuffers, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(attributes), &attributes, GL_STATIC_DRAW);

}