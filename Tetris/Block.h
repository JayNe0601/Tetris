#pragma once
#include <graphics.h> //图形库
struct Point {
	int row, col;
};
class Block {
public:
	Block();//构造函数
	void drop();//下落
	void moveLeftRight(int offset);//左右移，根据offset的正负来判断左移还是右移
	void retate();//旋转
	void draw(int leftMargin, int topMargin);//绘制左边界和上边界
private:
	int blockType;//方块类型
	Point smallBlocks[4];//方块的4个点的坐标
	IMAGE* img;//图像，指针用于指向相应的图像
	//静态成员变量，所有对象共享，用于存储7种方块的图像
	static IMAGE* imgs[7];//7种方块的图像，静态成员变量，指针用于内存分配
	static int size;//方块的大小
};