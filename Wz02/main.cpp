#include "Image.h"
#include <iostream>
#include "GameLib/Framework.h"

using namespace GameLib;

//����ԭ�� in Update
//void mainLoop();
//void draw();
Image *im;

namespace GameLib {
	void Framework::update() {
		if (!im) {//���image������
			im = new Image("bar.dds");
		}
	}
}