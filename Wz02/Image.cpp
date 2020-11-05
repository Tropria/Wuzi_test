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
	mHeight = file.getUnsignedInt(12);//DDS图片格式 先高 
	mWidth = file.getUnsignedInt(16);//后宽度
	mData = new unsigned[mWidth * mHeight];
	for (int i = 0; i < mWidth * mHeight; ++i) {
		mData[i] = file.getUnsignedInt(128 + i*4);
	}
}

Image::~Image() {
	delete[] mData;
	mData = 0;
}

int Image::getHeight() const {
	return mHeight;
}

int Image::getWidth() const {
	return mWidth;
}

void Image::draw(int dstX, int dstY, int srcX,
	int srcY, int width, int height) const {
	//获取Framework的 videoMemory实例；
	unsigned* vram = Framework::instance().videoMemory();
	//获取Framework的 窗口宽度
	unsigned windowWidth = Framework::instance().width();
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			unsigned int* dst = &vram[(y+dstY) * windowWidth + (x+dstX)];
			*dst = mData[(y+srcY) * mWidth + (x+srcX)];
		}
	}
}