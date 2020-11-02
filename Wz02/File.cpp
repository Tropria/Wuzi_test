#include "File.h"
#include <iostream>
#include <fstream>

using namespace std;

File::File(const char* fileName) :
mSize(0),
mData(0)
{
	//�Զ�ȡdds�ļ�Ϊ��
	ifstream in(fileName, ifstream::binary);
	if (in) {
		in.seekg(0, ifstream::end); // in.end
		mSize = static_cast<int>(in.tellg());//set length
		mData = new char[mSize];

		in.seekg(0, ifstream::beg); // in.begin
		in.read(mData, mSize);
		//in.close();
	}

	
}

File::~File() {
	delete[] mData;
	mData = 0;
}

int File::getSize() const {
	return mSize;
}

const char* File::getData() const {
	return mData;
}

unsigned File::getUnsignedInt(int p) const {

	const unsigned char* ucharp; //��mDataָ��ת��Ϊunsigned char*
	ucharp = reinterpret_cast<const unsigned char*>(mData);
	unsigned r = ucharp[p];//��ucharp[0] [1] [2] [3]����Ϊunsigned int
	r |= ucharp[p + 1] << 8; //small-endian
	r |= ucharp[p + 2] << 16;
	r |= ucharp[p + 3] << 24;
	return r;
}