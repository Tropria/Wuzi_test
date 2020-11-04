#include "State.h"
#include "Image.h"

//生成空棋盘
State::State() {
	//设置起始光标位置、棋盘大小等
	x_cursor = 2;
	y_cursor = 2;
	mWidth = 5;
	mHeight = 5;
	mObjects.setSize(mWidth, mHeight);
	//初始化棋盘
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			mObjects(x, y) = OBJ_SPACE;
		}
	}
	//图片载入
	mImage = new Image("wz_material.dds");
}

State::~State() {
	delete mImage;
	mImage = 0;
	//注意这里自动析构了 Array<Object> ，无需手动析构
}

//绘制
//working
void State::draw() const {
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			//首先画好space
			drawCell(x, y, IMG_ID_WHITE);
			//然后画好其它物体
			/*Object o = mObjects(x, y);
			ImageID id = IMG_ID_SPACE;
			switch (o) {
			case OBJ_WHITE: id = IMG_ID_WHITE; break;
			case OBJ_BLACK: id = IMG_ID_BLACK; break;
			}*/
			//drawCell(x, y, id);
		}
	}
	//最后我们画好光标
	//drawCell(x_cursor, y_cursor, IMG_ID_CURSOR);
}

//在（x, y）处画好一个图片
void State::drawCell(int x, int y, ImageID id) const {
	static int p = 32;
	mImage->draw(x * 32, y * 32, id * 32, 0, 32, 32);
}

//主逻辑
//TODO
void State::update(char input) {
	//移动差分变换
	int dx = 0;
	int dy = 0;
	switch (input) {
	case 'a': dx = -1; break; //向左
	case 'd': dx = 1; break; //右
	case 'w': dy = -1; break; //上。Y朝下为正
	case 's': dy = 1; break; //下。
	}
	//使用简短的变量名。
	int w = mWidth;
	int h = mHeight;
	Array2D< Object >& o = mObjects;
	//查找cursor坐标
	int x = x_cursor;
	int y = y_cursor;

	//移动
	//运动后坐标
	int tx = x + dx;
	int ty = y + dy;
	//检查最大和最小坐标。
	if (tx < 0 || ty < 0 || tx >= w || ty >= h) {
		return;
	}
	x_cursor = tx; y_cursor = ty;
	//A.该方向上是空白或者终点。则小人移动

	//if (o(tx, ty) == OBJ_SPACE) {
	//	o(tx, ty) = OBJ_MAN;
	//	o(x, y) = OBJ_SPACE;
	//	//B.该方向是箱子。如果该方向上的下一个格子为空白或目标，则移动。
	//}
	//else if (o(tx, ty) == OBJ_BLOCK) {
	//	//2检查方格是否在范围内
	//	int tx2 = tx + dx;
	//	int ty2 = ty + dy;
	//	if (tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h) { //不能按
	//		return;
	//	}
	//	if (o(tx2, ty2) == OBJ_SPACE) {
	//		//按顺序交换
	//		o(tx2, ty2) = OBJ_BLOCK;
	//		o(tx, ty) = OBJ_MAN;
	//		o(x, y) = OBJ_SPACE;
	//	}
	//}
}


//判断是否已经结束 
//TODO
bool State::hasCleared() const {
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			
		}
	}
	return true;
}

//从stageData读取棋谱 
//TODO
State::State(const char* stageData) {
	//设置起始光标位置、棋盘大小等
	x_cursor = 2;
	y_cursor = 2;
	mWidth = 5;
	mHeight = 5;
	mObjects.setSize(mWidth, mHeight);
	//初始化棋盘
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			mObjects(x, y) = OBJ_SPACE;
		}
	}
	//从stageData读取棋谱
}