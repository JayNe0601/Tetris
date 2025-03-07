#pragma once
#include <graphics.h> //图形库
#include <vector>
using namespace std;
struct Point {
	int row, col;
};
class Block {
public:
	Block();//构造函数
	void drop();//下落
	void moveLeftRight(int offset);//左右移，根据offset的正负来判断左移还是右移
	void rotate();//旋转
	void draw(int leftMargin, int topMargin);//绘制左边界和上边界
	static IMAGE** getImgs();// 获取方块的图像
	Block& operator=(const Block& other);//赋值运算符重载
	bool blockInMap(const vector<vector<int>>& map);// 判断方块是否在地图中
	void solidify(vector<vector<int>>& map);// 方块固化
	int getBlockType();// 获取方块类型
private:
	int blockType;//方块类型
	Point smallBlocks[4];//方块的4个点的坐标
	IMAGE* img;//图像，指针用于指向相应的图像
	//静态成员变量，所有对象共享，用于存储7种方块的图像
	static IMAGE* imgs[7];//7种方块的图像，静态成员变量，指针用于内存分配
	static int size;//方块的大小
};