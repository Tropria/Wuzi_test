#include "File.h"
#include "State.h"

#include <iostream>
#include "GameLib/Framework.h"

using namespace GameLib;

//函数原型 in Update
void mainLoop();

//全局变量state
State* gState = 0;


namespace GameLib {
	void Framework::update() {
		mainLoop();
	}
}

void mainLoop() {
	//检查是否结束
	bool cleared = false;
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
	cout << "a:left d:right w:up s:down. command?" << endl; //操作说明
	char input;
	cin >> input;
	//结束判断
	if (input == 'q') {
		delete gState;
		gState = 0;
		Framework::instance().requestEnd();
		return;
	}
	//更新
	gState->update(input);
	//绘制
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