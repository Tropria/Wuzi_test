#ifndef INCLUDE_STATE_H
#define INCLUDE_STATE_H
#include "Array2D.h"

class Image;// member image

class State {
public:
	State();//默认构造空棋盘
	State(const char* stageData);//从文件读取棋谱
	~State();
	void update(int moveX, int moveY, bool isSet);
	void draw() const;
	bool isOver() const;//检查是否一方胜出
	int getCurColor();
private:
	enum Object {
		OBJ_WHITE,
		OBJ_BLACK,
		OBJ_CURSOR,
		OBJ_SPACE,

		OBJ_UNKNOWN
	};
	enum ImageID {
		IMG_ID_WHITE,
		IMG_ID_BLACK,
		IMG_ID_CURSOR,
		IMG_ID_LAST,
		
		IMG_ID_SPACE
	};
	
	void drawCell(int x, int y, ImageID) const;
	void changeColor();//交换行动顺序
	bool state_checkIsFive(int x, int y) const;//辅助函数：检查当前子是否满足5连
	

	int mWidth;
	int mHeight;
	Array2D< Object > mObjects;
	unsigned int curColor;//当前行动的一方的颜色 0 white 1 black
	int x_cursor;
	int y_cursor;

	Image* mImage;
};

#endif