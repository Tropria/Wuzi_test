#include "File.h"
#include "State.h"

#include <iostream>
#include "GameLib/Framework.h"

using namespace GameLib;

//函数原型 in Update
void mainLoop();

//全局变量state
State* gState = 0;
bool gPrevInputS = false;
bool gPrevInputA = false;
bool gPrevInputW = false;
bool gPrevInputD = false;
bool gPrevInputC = false;


//检查是否结束
bool cleared = false;

namespace GameLib {
	void Framework::update() {
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
	//×按钮被按下了吗？
	if (Framework::instance().isEndRequested()) {
		if (gState) {
			delete gState;
			gState = 0;
		}
		return;
	}
	//初始化第一帧。绘制第一个状态并完成。
	if (!gState) {
		//File file("stageData.txt");
		//if (!(file.data())) { //没有数据！
		//	cout << "stage file could not be read." << endl;
		//	return;
		//}
		gState = new State();
		//第一绘制
		gState->draw();
		return; //结束
	}
	
	//获取输入
	//cout << "a:left d:right w:up s:down. command?" << endl; //操作说明
	//获取输入
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
	//结束判断
	if (f.isKeyOn('q')) {
		delete gState;
		gState = 0;
		Framework::instance().requestEnd();
		return;
	}
	//更新
	gState->update(dx, dy, inputC);
	//绘制
	gState->draw();

	if (gState->isOver()) {
		cleared = true;
	}
	
}