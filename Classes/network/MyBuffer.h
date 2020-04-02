#pragma once
#include <vector>
#include <string>

class MyBuffer
{
private:
	std::vector<char> buffer;
public:
	inline int size() { return buffer.size(); }
	inline char* data() { return buffer.data(); }
	inline void remove(int len) { buffer.erase(buffer.begin(), buffer.begin() + len); }

	int readInt();
	int readIntEx();
	
	void writeInt(int val);
	void writeString(const char* dat, int len);
	void append(std::vector<char>& dat);
	void append(std::vector<char>& dat, int len);
};

