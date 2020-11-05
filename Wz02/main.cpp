#include "File.h"
#include "State.h"

#include <iostream>
#include "GameLib/Framework.h"

using namespace GameLib;

//����ԭ�� in Update
void mainLoop();

//ȫ�ֱ���state
State* gState = 0;


namespace GameLib {
	void Framework::update() {
		mainLoop();
	}
}

void mainLoop() {
	//����Ƿ����
	bool cleared = false;
	//����ť����������
	if (Framework::instance().isEndRequested()) {
		if (gState) {
			delete gState;
			gState = 0;
		}
		return;
	}
	//��ʼ����һ֡�����Ƶ�һ��״̬����ɡ�
	if (!gState) {
		//File file("stageData.txt");
		//if (!(file.data())) { //û�����ݣ�
		//	cout << "stage file could not be read." << endl;
		//	return;
		//}
		gState = new State();
		//��һ����
		gState->draw();
		return; //����
	}
	
	//��ȡ����
	cout << "a:left d:right w:up s:down. command?" << endl; //����˵��
	char input;
	cin >> input;
	//�����ж�
	if (input == 'q') {
		delete gState;
		gState = 0;
		Framework::instance().requestEnd();
		return;
	}
	//����
	gState->update(input);
	//����
	gState->draw();

	if (gState->isOver()) {
		cleared = true;
	}
	if (cleared) {
		cout << "Congratulation! you win. Input any char to continue" << endl;
		char temp;
		cin >> temp;
		delete gState;
		gState = 0;
	}
}