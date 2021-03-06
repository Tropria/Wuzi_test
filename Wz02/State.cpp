#include "State.h"
#include "Image.h"
#include <iostream>
#include "alphabeta.h"

//生成空棋盘
State::State() {
	//设置起始光标位置、棋盘大小等
	x_cursor = 7;
	y_cursor = 7;
	mWidth = 15;
	mHeight = 15;
	mObjects.setSize(mWidth, mHeight);
	//初始化棋盘
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			mObjects(x, y) = OBJ_SPACE;
		}
	}
	//图片载入
	mImage = new Image("nimotsuKunImage2_16bit.dds");
	curColor = OBJ_BLACK;

	mMoveCount = 0;
	mMoveX = 0;
	mMoveY = 0;
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
			drawCell(x, y, IMG_ID_SPACE);

			//然后画好其它物体
			Object o = mObjects(x, y);
			ImageID id = IMG_ID_SPACE;
			switch (o) {
			case OBJ_WHITE: id = IMG_ID_WHITE; break;
			case OBJ_BLACK: id = IMG_ID_BLACK; break;
			}
			if(id!=IMG_ID_SPACE) drawCell(x, y, id);
		}
	}

	//最后我们画好光标.可能会覆盖掉当前图片
	//drawCell(x_cursor, y_cursor, IMG_ID_CURSOR);
	drawCursor(x_cursor, y_cursor, mMoveCount);
}

void State::drawCursor(int x, int y, int moveCount) const {
	//只有cursor移动
	int dx = mMoveX * (16 - moveCount);
	int dy = mMoveY * (16 - moveCount);
	mImage->draw(x * 16 - dx, y * 16 - dy, IMG_ID_CURSOR * 16, 0, 16, 16);
}


//在（x, y）处画好一个图片
void State::drawCell(int x, int y, ImageID id) const {
	static int h = 16;
	mImage->draw(x * 16, y * 16, id * 16, 0, 16, 16);
}

//交换行动顺序
void State::changeColor() {
	curColor = (curColor+1)%2;
}

//主逻辑
//TODO
void State::update(int moveX, int moveY, bool isSet) {
	if (mMoveCount == 16) {
		mMoveCount = 0;
		mMoveX = 0;
		mMoveY = 0;
	}
	//移动时请勿更新
	if (mMoveCount > 0) {
		++mMoveCount;
		return;
	}

	if (curColor == OBJ_WHITE) {
		//如果当前轮到白棋（AI）走

		//先将mObjects转化成int a[15][15]的棋盘，作为参数传入TreeNode
		int board[15][15];
		for (int j = 0; j < mHeight; ++j) {
			for (int i = 0; i < mWidth; ++i) {
				if (mObjects(i, j) == OBJ_SPACE) board[j][i] = 0;
				if (mObjects(i, j) == OBJ_WHITE) board[j][i] = 1;
				if (mObjects(i, j) == OBJ_BLACK) board[j][i] = 2;
			}
		}
		TreeNode* root = new TreeNode(board, BLACK);
		//将上一次玩家的颜色，即黑色作为curColor
		//使用上次最后落子的位置，即x_cursor, y_cursor修改TreeNode的最后落子位置 x_last, y_last
		root->x_last = x_cursor;
		root->y_last = y_cursor;
		int eva = alphabeta(root, DEPTH, INT_MIN, INT_MAX, WHITE);
		//在root->x_next, root->y_next处落白子
		//std::cout << "I want to set " << root->x_next << "," << root->y_next << std::endl;
		mObjects(root->x_next, root->y_next) = OBJ_WHITE;

		changeColor();
		return;
	}
	
	
	//移动差分变换
	int dx = moveX;
	int dy = moveY;
	bool isSetChess = isSet;

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
	//检查最大和最小坐标。若到达边界则直接停止当前循环
	if (tx < 0 || ty < 0 || tx >= w || ty >= h) {
		return;
	}
	x_cursor = tx; y_cursor = ty;
	mMoveX = dx; mMoveY = dy;
	if(dx!=0 || dy!=0){	
		mMoveCount = 1; //开始移动
	}
	//落子
	if (isSetChess) {
		//检查当前是否可以落子
		if (o(x_cursor, y_cursor) == OBJ_SPACE) {
			o(x_cursor, y_cursor) = static_cast<Object>(curColor);
			changeColor();
		}
	}
}


//判断是否已经结束 
//TODO
bool State::isOver() const {
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			if (state_checkIsFive(x, y)) return true;
		}
	}
	return false;
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

bool State::state_checkIsFive(int x, int y) const {
	Object o = mObjects(x, y);
	//检查是否是黑or白
	if (o != OBJ_BLACK && o != OBJ_WHITE) return false;
	int j = y, i = x;
	//向右检查
	j = y; i = x + 1;
	for (; i < x + 5 && j < mHeight && i < mWidth;) {
		if (mObjects(i,j) != o) break;
		++i;
	}
	if (i == x + 5) return true;
	//向下
	j = y + 1; i = x;
	for (; j < y + 5 && j < mHeight && i < mWidth;) {
		if (mObjects(i, j) != o) break;
		++j;
	}
	if (j == y + 5) return true;
	//向右下检查
	j = y + 1; i = x + 1;
	for (; i < x + 5 && j < y + 5 && j < mHeight && i < mWidth;) {
		if (mObjects(i, j) != o) break;
		++j; ++i;
	}
	if (i == x + 5) return true;
	//向左下检查
	j = y + 1; i = x - 1;
	for (; i > x - 5 && j < y + 5 && i >= 0 && j < mHeight; ) {
		if (mObjects(i, j) != o) break;
		++j; --i;
	}
	if (j == y + 5) return true;
	return false;
}