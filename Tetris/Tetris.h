#pragma once
#include <vector>
#include <graphics.h>
#include "Block.h"
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
	void moveLeftRight(int offset);// 左右移动
	void rorate();//旋转
	void drawScore();// 绘制分数
	void drawLevel();// 绘制关卡
	void drawLineCount();// 绘制消行数
	void drawHighestScore();// 绘制最高分
	void checkOver();//检查游戏是否结束
	void saveHighestScore();//保存最高分
	void displayGameOver();//绘制显示游戏结束界面
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
	Block* curBlock;// 当前方块
	Block* nextBlock;// 预告方块
	Block bakBlock;// 当前方块降落过程中，用来备用上一个方块的最后的合法位置
	int score;// 当前的分数
	int HighestScore;// 最高分
	int level;// 当前关卡
	int lineCount; // 当前消行数
	bool gameOver;// 游戏是否结束
	IMAGE gameOverImg;// 游戏结束图片
};

