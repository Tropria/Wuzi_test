#include "State.h"
#include "Image.h"
#include <iostream>
#include "alphabeta.h"

//���ɿ�����
State::State() {
	//������ʼ���λ�á����̴�С��
	x_cursor = 7;
	y_cursor = 7;
	mWidth = 15;
	mHeight = 15;
	mObjects.setSize(mWidth, mHeight);
	//��ʼ������
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			mObjects(x, y) = OBJ_SPACE;
		}
	}
	//ͼƬ����
	mImage = new Image("nimotsuKunImage2_16bit.dds");
	curColor = OBJ_BLACK;
}

State::~State() {
	delete mImage;
	mImage = 0;
	//ע�������Զ������� Array<Object> �������ֶ�����
}

//����
//working
void State::draw() const {
	std::cout << "mHeight " << mHeight << " mWidth " << mWidth << std::endl;
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			//���Ȼ���space
			drawCell(x, y, IMG_ID_SPACE);

			//Ȼ�󻭺���������
			Object o = mObjects(x, y);
			ImageID id = IMG_ID_SPACE;
			switch (o) {
			case OBJ_WHITE: id = IMG_ID_WHITE; break;
			case OBJ_BLACK: id = IMG_ID_BLACK; break;
			}
			if(id!=IMG_ID_SPACE) drawCell(x, y, id);
		}
	}

	//������ǻ��ù��.���ܻḲ�ǵ���ǰͼƬ
	drawCell(x_cursor, y_cursor, IMG_ID_CURSOR);
}

//�ڣ�x, y��������һ��ͼƬ
void State::drawCell(int x, int y, ImageID id) const {
	static int h = 16;
	mImage->draw(x * 16, y * 16, id * 16, 0, 16, 16);
}

//�����ж�˳��
void State::changeColor() {
	curColor = (curColor+1)%2;
}

//���߼�
//TODO
void State::update(int moveX, int moveY, bool isSet) {
	if (curColor == 1) {
		//�����ǰ�ֵ����壨AI����

		//�Ƚ�mObjectsת����int a[15][15]�����̣���Ϊ��������TreeNode
		int board[15][15];
		for (int j = 0; j < mHeight; ++j) {
			for (int i = 0; i < mWidth; ++i) {
				if (mObjects(i, j) == OBJ_SPACE) board[j][i] = 0;
				if (mObjects(i, j) == OBJ_WHITE) board[j][i] = 1;
				if (mObjects(i, j) == OBJ_BLACK) board[j][i] = 2;
			}
		}
		TreeNode* root = new TreeNode(board, BLACK);
		//����һ����ҵ���ɫ������ɫ��ΪcurColor
		//ʹ���ϴ�������ӵ�λ�ã���x_cursor, y_cursor�޸�TreeNode���������λ�� x_last, y_last
		root->x_last = x_cursor;
		root->y_last = y_cursor;

		changeColor();
		return;
	}
	//�ƶ���ֱ任
	int dx = moveX;
	int dy = moveY;
	bool isSetChess = isSet;

	//ʹ�ü�̵ı�������
	int w = mWidth;
	int h = mHeight;
	Array2D< Object >& o = mObjects;
	//����cursor����
	int x = x_cursor;
	int y = y_cursor;

	//�ƶ�
	//�˶�������
	int tx = x + dx;
	int ty = y + dy;
	//���������С���ꡣ������߽���ֱ��ֹͣ��ǰѭ��
	if (tx < 0 || ty < 0 || tx >= w || ty >= h) {
		return;
	}
	x_cursor = tx; y_cursor = ty;
	//����
	if (isSetChess) {
		//��鵱ǰ�Ƿ��������
		if (o(x_cursor, y_cursor) == OBJ_SPACE) {
			o(x_cursor, y_cursor) = static_cast<Object>(curColor);
			changeColor();
		}
	}
}


//�ж��Ƿ��Ѿ����� 
//TODO
bool State::isOver() const {
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			if (state_checkIsFive(x, y)) return true;
		}
	}
	return false;
}

//��stageData��ȡ���� 
//TODO
State::State(const char* stageData) {
	//������ʼ���λ�á����̴�С��
	x_cursor = 2;
	y_cursor = 2;
	mWidth = 5;
	mHeight = 5;
	mObjects.setSize(mWidth, mHeight);
	//��ʼ������
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			mObjects(x, y) = OBJ_SPACE;
		}
	}
	//��stageData��ȡ����
}

bool State::state_checkIsFive(int x, int y) const {
	Object o = mObjects(x, y);
	//����Ƿ��Ǻ�or��
	if (o != OBJ_BLACK && o != OBJ_WHITE) return false;
	int j = y, i = x;
	//���Ҽ��
	j = y; i = x + 1;
	for (; i < x + 5 && j < mHeight && i < mWidth;) {
		if (mObjects(i,j) != o) break;
		++i;
	}
	if (i == x + 5) return true;
	//����
	j = y + 1; i = x;
	for (; j < y + 5 && j < mHeight && i < mWidth;) {
		if (mObjects(i, j) != o) break;
		++j;
	}
	if (j == y + 5) return true;
	//�����¼��
	j = y + 1; i = x + 1;
	for (; i < x + 5 && j < y + 5 && j < mHeight && i < mWidth;) {
		if (mObjects(i, j) != o) break;
		++j; ++i;
	}
	if (i == x + 5) return true;
	//�����¼��
	j = y + 1; i = x - 1;
	for (; i > x - 5 && j < y + 5 && i >= 0 && j < mHeight; ) {
		if (mObjects(i, j) != o) break;
		++j; --i;
	}
	if (j == y + 5) return true;
	return false;
}