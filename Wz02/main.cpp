#include "Image.h"
#include <iostream>
#include "GameLib/Framework.h"

using namespace GameLib;

//函数原型 in Update
//void mainLoop();
//void draw();
Image *im;

namespace GameLib {
	void Framework::update() {
		if (!im) {//如果image不存在
			im = new Image("bar.dds");
		}
	}
}