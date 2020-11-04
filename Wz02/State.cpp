#include "State.h"
#include "Image.h"

//���ɿ�����
State::State() {
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
	//ͼƬ����
	mImage = new Image("wz_material.dds");
}

State::~State() {
	delete mImage;
	mImage = 0;
	//ע�������Զ������� Array<Object> �������ֶ�����
}

//����
//working
void State::draw() const {
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			//���Ȼ���space
			drawCell(x, y, IMG_ID_WHITE);
			//Ȼ�󻭺���������
			/*Object o = mObjects(x, y);
			ImageID id = IMG_ID_SPACE;
			switch (o) {
			case OBJ_WHITE: id = IMG_ID_WHITE; break;
			case OBJ_BLACK: id = IMG_ID_BLACK; break;
			}*/
			//drawCell(x, y, id);
		}
	}
	//������ǻ��ù��
	//drawCell(x_cursor, y_cursor, IMG_ID_CURSOR);
}

//�ڣ�x, y��������һ��ͼƬ
void State::drawCell(int x, int y, ImageID id) const {
	static int p = 32;
	mImage->draw(x * 32, y * 32, id * 32, 0, 32, 32);
}

//���߼�
//TODO
void State::update(char input) {
	//�ƶ���ֱ任
	int dx = 0;
	int dy = 0;
	switch (input) {
	case 'a': dx = -1; break; //����
	case 'd': dx = 1; break; //��
	case 'w': dy = -1; break; //�ϡ�Y����Ϊ��
	case 's': dy = 1; break; //�¡�
	}
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
	//���������С���ꡣ
	if (tx < 0 || ty < 0 || tx >= w || ty >= h) {
		return;
	}
	x_cursor = tx; y_cursor = ty;
	//A.�÷������ǿհ׻����յ㡣��С���ƶ�

	//if (o(tx, ty) == OBJ_SPACE) {
	//	o(tx, ty) = OBJ_MAN;
	//	o(x, y) = OBJ_SPACE;
	//	//B.�÷��������ӡ�����÷����ϵ���һ������Ϊ�հ׻�Ŀ�꣬���ƶ���
	//}
	//else if (o(tx, ty) == OBJ_BLOCK) {
	//	//2��鷽���Ƿ��ڷ�Χ��
	//	int tx2 = tx + dx;
	//	int ty2 = ty + dy;
	//	if (tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h) { //���ܰ�
	//		return;
	//	}
	//	if (o(tx2, ty2) == OBJ_SPACE) {
	//		//��˳�򽻻�
	//		o(tx2, ty2) = OBJ_BLOCK;
	//		o(tx, ty) = OBJ_MAN;
	//		o(x, y) = OBJ_SPACE;
	//	}
	//}
}


//�ж��Ƿ��Ѿ����� 
//TODO
bool State::hasCleared() const {
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			
		}
	}
	return true;
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