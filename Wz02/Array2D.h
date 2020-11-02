#ifndef INCLUDE_ARRAY_2D_H
#define INCLUDE_ARRAY_2D_H
#include <iostream>
//2D 模板类
//考虑到模板函数定义需要与调用共存，故模板类的定义在相同头文件下完成
template<typename T> class Array2D {
public:
	Array2D() :
		mArray(0),
		mSize0(0),
		mSize1(0)
	{}
	~Array2D() {
		delete[] mArray;//无判断直接delete 正确
		mArray = 0;
	}
	void setSize(int size0, int size1) {
		if (mArray) delete[] mArray;//先判断为空再delete 也正确
		mArray = 0;
		mSize0 = size0;
		mSize1 = size1;
		mArray = new T[mSize0 * mSize1];
	}
	T& operator()(int index0, int index1) {
		//std::cout << "non-const" << std::endl;
		return mArray[index1 * mSize0 + index0];
	}
	const T& operator()(int index0, int index1) const{
		//std::cout << "const" << std::endl;
		return mArray[index1 * mSize0 + index0];
	}

private:
	T* mArray;
	int mSize0;
	int mSize1;
};

#endif
