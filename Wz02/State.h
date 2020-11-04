#ifndef INCLUDE_STATE_H
#define INCLUDE_STATE_H
#include "Array2D.h"

class Image;// member image

class State {
public:
	State();//默认构造空棋盘
	State(const char* stageData);//从文件读取棋谱
	~State();
	void update(char input);
	void draw() const;
	bool hasCleared() const;
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
		IMG_ID_BLUE,
		IMG_ID_SPACE
	};

	void drawCell(int x, int y, ImageID) const;

	int mWidth;
	int mHeight;
	Array2D< Object > mObjects;
	int x_cursor;
	int y_cursor;

	Image* mImage;
};

#endif