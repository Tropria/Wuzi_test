#include "Image.h"
#include "File.h"

#include "GameLib/Framework.h"
using namespace GameLib;//注意这里要使用vram 调用draw

Image::Image(const char* fileName) :
mWidth(0),
mHeight(0),
mData(0)
{
	File file(fileName);
	mWidth = file.getUnsignedInt(12);//DDS图片格式
	mHeight = file.getUnsignedInt(16);
	mData = new unsigned[mWidth * mHeight];
	for (int i = 0; i < mWidth * mHeight; ++i) {
		mData[i] = file.getUnsignedInt(128 + i*4);
	}
}
