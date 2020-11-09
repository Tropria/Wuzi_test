#ifndef INCLUDE_STATE_H
#define INCLUDE_STATE_H
#include "Array2D.h"

class Image;// member image

class State {
public:
	State();//Ĭ�Ϲ��������
	State(const char* stageData);//���ļ���ȡ����
	~State();
	void update(int moveX, int moveY, bool isSet);
	void draw() const;
	bool isOver() const;//����Ƿ�һ��ʤ��
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
	void changeColor();//�����ж�˳��
	bool state_checkIsFive(int x, int y) const;//������������鵱ǰ���Ƿ�����5��
	

	int mWidth;
	int mHeight;
	Array2D< Object > mObjects;
	unsigned int curColor;//��ǰ�ж���һ������ɫ 0 white 1 black
	int x_cursor;
	int y_cursor;

	Image* mImage;
};

#endif