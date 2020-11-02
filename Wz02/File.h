#ifndef INCLUDE_FILE_H
#define INCLUDE_FILE_H

class File {
public:
	File(const char* fileName);
	~File();
	int getSize() const;
	const char* getData() const;
	unsigned int getUnsignedInt(int p) const;
private:
	int mSize;
	char* mData;
};


#endif
