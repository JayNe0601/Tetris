#include "Tetris.h"
#include <time.h>
#include <stdlib.h>
const int SPEED_NORMAL = 500; //下降慢的速度
const int SPEED_QUICK = 50; //下降快的速度
Tetris::Tetris(int rows, int cols, int left, int top, int blockSize) {
	this->rows = rows;// 初始化行数
	this->cols = cols;// 初始化列数
	this->leftMargin = left;// 初始化左边界
	this->blockSize = blockSize;// 初始化方块大小
	this->topMargin = top;// 初始化上边界
	map.resize(rows);// 初始化地图
	for (int i = 0; i < rows; i++) {
		vector<int> rowt;// 初始化每一行
		for (int j = 0; j < cols; j++) rowt.push_back(0);// 初始化每一列，0表示没有方块
		map[i] = rowt;// 将每一行加入到地图中
	}
}
void Tetris::init() {
	delay = SPEED_NORMAL;// 设置延时
	srand(time(NULL));// 配置随机种子
	initgraph(938, 896);// 初始化游戏窗口
	// 加载背景图片
	loadimage(&imgBg, "photos/bg.png");
	for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) map[i][j] = 0;// 游戏重新开始时，重置游戏，所有方块都没有
}
void Tetris::play() {
	init();// 初始化
	int timer = 0;// 计时器，为防止渲染CPU空转，可以在这里加一个延时，使游戏画面渲染在多少秒渲染1次
	while (1) {
		keyEvent();// 接受用户的输入
		timer += getDelay();// 获取距离上一次调用该函数，间隔了多少时间（ms）
		if (timer > delay) {
			timer = 0;// 重置计时器
			drop();// 方块下落
			update = true;// 设置更新标志，使游戏画面得以更新
		}
		if (update) {
			update = false;// 重置更新标志
			updateWindow();// 渲染游戏画面，更新游戏画面
			clearLine();//清行，更新游戏相关数据
		}
	}// 游戏的循环结构
}

void Tetris::keyEvent() {
	update = true;// 设置更新标志，使游戏画面得以更新
}
void Tetris::updateWindow() {
	putimage(0, 0, &imgBg);// 绘制背景
}
// 第一次调用直接返回0，之后每次调用返回上一次调用到这一次调用的时间间隔
int Tetris::getDelay() {
	static unsigned long long lastTime = 0;// 获取系统时间
	unsigned long long currenTime = GetTickCount();// 获取系统时间
	if (lastTime == 0) {// 第一次调用
		lastTime = currenTime;// 初始化上一次的时间
		return 0;// 第一次调用直接返回0
	}
	else {// 之后的调用
		int ret = currenTime - lastTime;// 获取时间间隔
		lastTime = currenTime;// 更新上一次的时间
		return ret;// 返回时间间隔
	}
}

void Tetris::drop() {
}

void Tetris::clearLine() {
}
