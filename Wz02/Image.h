#ifndef INCLUDE_IMAGE_H
#define INCLUDE_IMAGE_H

class Image {
public:
	Image(const char* fileName); //Í¨¹ýfilename¶ÁÈ¡Í¼Æ¬
	~Image();
	int getWidth() const;
	int getHeight() const;
	void draw(
		int dstX,
		int dstY,
		int width,
		int height
	)const;

private:
	int mWidth; // member width
	int mHeight; // member height
	unsigned* mData; //unsigned int* 
};



#endif