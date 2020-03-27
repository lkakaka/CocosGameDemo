#pragma once
#include <vector>
#include <string>

class MyBuffer
{
private:
	std::vector<char> buffer;
public:
	int readInt();
	int readIntEx();
	
	void writeInt(int val);
	void writeString(const char* dat, int len);
};

