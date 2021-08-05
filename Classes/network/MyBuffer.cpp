#include "MyBuffer.h"
#include <iterator>

int MyBuffer::readInt(bool isRemove) {
	if (buffer.size() < 4) throw std::exception("mybyffer read int error");
	int c1 = buffer[0];
	int c2 = buffer[1];
	int c3 = buffer[2];
	int c4 = buffer[3];
	if (isRemove) buffer.erase(buffer.begin(), buffer.begin() + 4);
	return c1 << 24 | c2 << 16 | c3 << 8 | c4;
}

void MyBuffer::writeInt(int val) {
	for (int i = 0; i < 4; i++) {
		unsigned char ch = (unsigned char)(val >> (24 - 8 * i));
		buffer.push_back(ch);
	}
}

void MyBuffer::writeString(const char* dat, int len) {
	std::copy(dat, dat + len, std::back_inserter(buffer));
}

void MyBuffer::append(std::vector<char>& dat) {
	std::copy(dat.begin(), dat.end(), std::back_inserter(buffer));
}

void MyBuffer::append(std::vector<char>& dat, int len) {
	std::copy(dat.begin(), dat.begin() + len, std::back_inserter(buffer));
}