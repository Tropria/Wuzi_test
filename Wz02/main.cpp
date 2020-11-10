#include "File.h"
#include "State.h"

#include <iostream>
#include "GameLib/Framework.h"

using namespace GameLib;

//����ԭ�� in Update
void mainLoop();

//ȫ�ֱ���state
State* gState = 0;
bool gPrevInputS = false;
bool gPrevInputA = false;
bool gPrevInputW = false;
bool gPrevInputD = false;
bool gPrevInputC = false;


//����Ƿ����
bool cleared = false;

unsigned gPreviousTime[10]; //10��¼���ʱ��

namespace GameLib {
	void Framework::update() {
		sleep(1);
		unsigned curTime = time();
		unsigned frameTime = curTime - gPreviousTime[0]; //ע���������10֡
		for (int i = 0; i < 10-1; ++i) {
			gPreviousTime[i] = gPreviousTime[i + 1];
		}
		gPreviousTime[10-1] = curTime;
		unsigned frameRate = 1000*10 / frameTime;
		cout << "Current frame rate: " << frameRate << endl;

		mainLoop();
		
	}
}

void mainLoop() {
	Framework f = Framework::instance();

	

	if (f.isKeyOn('r')) {
		delete gState;
		gState = 0;
		cleared = false;
	}
	if(cleared) {
		cout << "Congratulation! you win. Input r to continue" << endl;
		return;
	}
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
	//cout << "a:left d:right w:up s:down. command?" << endl; //����˵��
	//��ȡ����
	int dx = 0;
	int dy = 0;
	bool inputA = f.isKeyOn('a');
	bool inputS = f.isKeyOn('s');
	bool inputW = f.isKeyOn('w');
	bool inputD = f.isKeyOn('d');
	bool inputC = f.isKeyOn('c');
	if (inputA && (!gPrevInputA)) {
		dx -= 1;
	}
	else if (inputD && (!gPrevInputD)) {
		dx += 1;
	}
	else if (inputW && (!gPrevInputW)) {
		dy -= 1;
	}
	else if (inputS && (!gPrevInputS)) {
		dy += 1;
	}
	gPrevInputA = inputA;
	gPrevInputS = inputS;
	gPrevInputW = inputW;
	gPrevInputD = inputD;
	gPrevInputC = inputC;

	//�����ж�
	if (f.isKeyOn('q')) {
		delete gState;
		gState = 0;
		Framework::instance().requestEnd();
		return;
	}

	//����
	gState->update(dx, dy, inputC);
	//cout << "Current mMoveCount " << gState->mMoveCount <<"dx, dy =("<<gState->mMoveX<<","<<gState->mMoveY<<")" <<endl;
	
	//����
	gState->draw();


	if (gState->isOver()) {
		cleared = true;
	}
	
}