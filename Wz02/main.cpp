#include "Image.h"
#include "Array2D.h"

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

			Array2D<int> a2d;
			const int& a = a2d(0, 0);
		}
		im->draw(0,0,im->getWidth(), im->getHeight());
	}
}