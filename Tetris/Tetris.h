#pragma once
#include <vector>
#include <graphics.h>
using namespace std;
class Tetris {
public:
	Tetris(int rows, int cols, int left, int top, int blockSize);//构造函数，初始化俄罗斯方游戏的行数、列数、左边界、上边界、方块大小
	void init(); //初始化
	void play(); //开始游戏
private:
	void keyEvent();//键盘事件
	void updateWindow();// 渲染游戏画面
	int getDelay();//返回距离上一次调用该函数，间隔了多少时间（ms），第一次调用返回0
	void drop();//方块下落
	void clearLine();//消行
private:
	int delay;// 延时
	bool update;// 是否更新
	vector<vector<int>> map;// 游戏地图，0表示没有方块，1表示第一种方块，2表示第二种方块，以此类推
	int rows;// 行数
	int cols;// 列数
	int leftMargin;// 左边界
	int topMargin;// 上边界
	int blockSize;// 方块大小
	IMAGE imgBg;// 背景图
};

