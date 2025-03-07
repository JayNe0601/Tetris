#include "Tetris.h"
#include <time.h>
#include <stdlib.h>
#include"Block.h"
#include <conio.h>
#include <fstream>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")// 链接winmm.lib库，用于播放音乐
#define MAX_LEVEL 5 //最大关卡
#define RECORDER_FILE "data/highestScore.txt" // 最高分记录文件
const int SPEED_NORMAL[MAX_LEVEL] = { 500, 450, 350, 250, 100 }; // 根据关卡设置下降速度
const int SPEED_QUICK = 30; //下降快的速度
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
	srand(time(NULL));// 配置随机种子
	gameOver = false;// 游戏未结束
	score = 0;// 重置分数
	level = 1;// 重置关卡
	lineCount = 0;// 重置消行数
	delay = SPEED_NORMAL[0];// 设置延时
	initgraph(938, 896);// 初始化游戏窗口
	loadimage(&imgBg, "photos/bg.png");// 加载背景图片
	loadimage(&gameOverImg, "photos/over.png");// 加载游戏结束图片
	for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) map[i][j] = 0;// 游戏重新开始时，重置游戏，所有方块都没有
	//从文件中读取最高分
	ifstream file(RECORDER_FILE);// 打开文件
	if (!file.is_open()) HighestScore = 0;// 如果文件打开失败，最高分为0
	else file >> HighestScore; // 读取最高分，将最高分赋值给HighestScore
	file.close();// 关闭文件
}
void Tetris::play() {
	init();// 初始化
	nextBlock = new Block();// 生成预告方块
	curBlock = nextBlock;// 当前方块等于预告方块
	nextBlock = new Block();// 生成新的预告方块
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
		if (gameOver) {
			saveHighestScore();// 保存最高分
			displayGameOver();// 显示游戏结束界面
			system("pause");// 暂停
			init();// 重新初始化，重新开始游戏
		}
	}// 游戏的循环结构
}
void Tetris::keyEvent() {
	unsigned char ch;// char 范围为-128 ~ 127， unsigned char 范围为0 ~ 255
	bool rotateFlag = false;// 旋转标志
	int dx = 0;// 水平移动偏移量
	if (_kbhit()) {// 如果有按键按下，接受用户的输入
		ch = _getch();// 获取按下的键
		//如果按下向上按键，先后返回：224 72，旋转
		//如果按下向下按键，先后返回：224 80，快速下降
		//如果按下向左按键，先后返回：224 75，向左移动
		//如果按下向右按键，先后返回：224 77，向右移动
		if (ch == 224) {
			ch = _getch();
			switch(ch) {
			case 72: 
				rotateFlag = true;
				break;// 旋转
			case 80: 
				delay = SPEED_QUICK;
				break;// 快速下降
			case 75:
				dx = -1;// 左移
				break;
			case 77:
				dx = 1;// 右移
				break;
			default: break;
			}
		}
	}
	if (rotateFlag) {
		rorate();// 旋转
		update = true;// 设置更新标志，使游戏画面得以更新
	}// 旋转
	if (dx != 0) {
		moveLeftRight(dx);// 左右移动
		update = true;// 设置更新标志，使游戏画面得以更新
	}
}
void Tetris::updateWindow() {
	putimage(0, 0, &imgBg);// 绘制背景
	/*// 测试方块
	Block block;
	block.draw(leftMargin, topMargin);*/
	//使用BeginBatchDraw()和EndBatchDraw()函数可以减少闪烁，提高绘图速度
	BeginBatchDraw();// 开始批量绘制
	IMAGE** imgs = Block::getImgs();// 获取方块的图像
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j] == 0) continue;
			int x = j * blockSize + leftMargin;// 计算x坐标
			int y = i * blockSize + topMargin;// 计算y坐标
			putimage(x, y, imgs[map[i][j] - 1]);// 绘制方块，方块种类为map[i][j]
		}
	}
	curBlock->draw(leftMargin, topMargin);// 绘制当前方块
	nextBlock->draw(leftMargin + 10 * blockSize + 25, topMargin - 20);// 绘制预告方块，位置在右上方
	drawScore();// 绘制分数
	drawLevel();// 绘制关卡数
	drawLineCount();// 绘制消行数
	drawHighestScore();// 绘制最高分
	EndBatchDraw();// 结束批量绘制
}
int Tetris::getDelay() {// 第一次调用直接返回0，之后每次调用返回上一次调用到这一次调用的时间间隔
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
	bakBlock = *curBlock;// 保存当前方块的位置
	curBlock->drop();// 方块下降
	if (!curBlock->blockInMap(map)) {// 方块不能下降，方块进行固化
		bakBlock.solidify(map);// 固化方块
		delete curBlock;// 删除当前方块，释放内存
		curBlock = nextBlock;// 当前方块等于预告方块
		nextBlock = new Block();// 生成新的预告方块
		checkOver();// 检查游戏是否结束
		delay = SPEED_NORMAL[level - 1];// 设置快速下降的速度，防止按下键一直加速下降
	}
}
void Tetris::clearLine() {
	int lines = 0;// 计数器，记录消行的行数
	int k = rows - 1;// 从下往上遍历，k表示存储数据的行数
	for (int i = rows - 1; i >= 0; i--) {
		bool flag = true;// 标志位，表示是否满行
		for (int j = 0; j < cols; j++) {// 检查是否满行
			if (!map[i][j]) {
				flag = false;// 该行不满行
				break;
			}
		}
		if (!flag) {// 表示不满行
			for (int j = 0; j < cols; j++) map[k][j] = map[i][j];
			k--;
		}
		else lines++;
	}
	/*也可以使用一边扫描一边存储
	for (int i = rows - 1; i >= 0; i--) {
		int count = 0;// 计数器
		for (int j = 0; j < cols; j++) {// 检查是否满行
			if (map[i][j]) count++;
			map[k][j] = map[i][j]; // 一边扫描一边存储
		}
		if(count < cols) k-- // 不是满行，k减1
		else lines++;// 满行，消行数加1
	*/
	if (lines > 0) {
		lineCount += lines;// 更新消行数
		score += pow(2, lines - 1);// 计算得分，分数为消行数的2次方减1
		mciSendString("play photos/xiaohang.mp3", 0, 0, 0);// 播放消行音效, 0表示不需要回调函数, play表示播放
		update = true;// 设置更新标志，使游戏画面得以更新
		// 每30分为一个关卡，关卡越高，下落速度越快
		level = min((score + 29) / 30, MAX_LEVEL);// 更新关卡, 且关卡数不超过最大关卡数
	}
}
void Tetris::moveLeftRight(int offset) {
	bakBlock = *curBlock;// 保存当前方块的位置
	curBlock->moveLeftRight(offset);// 左右移动
	if (!curBlock->blockInMap(map)) *curBlock = bakBlock;// 恢复当前方块的位置
}
void Tetris::rorate() {
	if (curBlock->getBlockType() == 7) return;// 田字方块不能旋转
	bakBlock = *curBlock;// 保存当前方块的位置
	curBlock->rotate();// 旋转
	if (!curBlock->blockInMap(map)) *curBlock = bakBlock;// 恢复当前方块的位置
}
void Tetris::drawScore() {
	LOGFONT f;// 定义字体
	gettextstyle(&f);// 获取当前字体
	f.lfHeight = 40;// 设置字体宽度
	f.lfWeight = 25;//	设置字体粗细
	f.lfQuality = ANTIALIASED_QUALITY; // 设置字体质量，“抗锯齿”效果
	settextstyle(&f);// 设置字体
	settextcolor(WHITE);// 设置字体颜色
	char scoreText[32];// 分数字符串
	sprintf_s(scoreText, sizeof(scoreText), "%d", score);// 格式化字符串
	outtextxy(670, 730, scoreText);// 输出分数
}
void Tetris::drawLevel() {
	LOGFONT f;// 定义字体
	gettextstyle(&f);// 获取当前字体
	f.lfHeight = 40;// 设置字体宽度
	f.lfWeight = 25;//	设置字体粗细
	f.lfQuality = ANTIALIASED_QUALITY; // 设置字体质量，“抗锯齿”效果
	settextstyle(&f);// 设置字体
	settextcolor(WHITE);// 设置字体颜色
	char levelText[32];// 分数字符串
	sprintf_s(levelText, sizeof(levelText), "%d", level);// 格式化字符串
	outtextxy(210 - f.lfWidth * strlen(levelText), 730, levelText);// 输出关卡数
}
void Tetris::drawLineCount() {
	LOGFONT f;// 定义字体
	gettextstyle(&f);// 获取当前字体
	f.lfHeight = 40;// 设置字体宽度
	f.lfWeight = 25;//	设置字体粗细
	f.lfQuality = ANTIALIASED_QUALITY; // 设置字体质量，“抗锯齿”效果
	settextstyle(&f);// 设置字体
	settextcolor(WHITE);// 设置字体颜色
	char lineCountText[32];// 分数字符串
	sprintf_s(lineCountText, sizeof(lineCountText), "%d", lineCount);// 格式化字符串
	outtextxy(210 - f.lfWidth * strlen(lineCountText), 820, lineCountText);// 输出消行数
}
void Tetris::drawHighestScore() {
	LOGFONT f;// 定义字体
	gettextstyle(&f);// 获取当前字体
	f.lfHeight = 40;// 设置字体宽度
	f.lfWeight = 25;//	设置字体粗细
	f.lfQuality = ANTIALIASED_QUALITY; // 设置字体质量，“抗锯齿”效果
	settextstyle(&f);// 设置字体
	settextcolor(WHITE);// 设置字体颜色
	char highestScoreText[32];// 分数字符串
	sprintf_s(highestScoreText, sizeof(highestScoreText), "%d", HighestScore);// 格式化字符串
	outtextxy(670, 820, highestScoreText);// 输出最高分
}
void Tetris::checkOver() {
	// 检查游戏是否结束
	if (curBlock->blockInMap(map) == false) gameOver = true;// 游戏结束
}
void Tetris::saveHighestScore() {
	if (score > HighestScore) HighestScore = score;// 更新最高分
	ofstream file(RECORDER_FILE);// 打开文件
	file << HighestScore;// 写入最高分
	file.close();// 关闭文件
}
void Tetris::displayGameOver() {
	putimage(260, 360, &gameOverImg);// 绘制游戏结束图片
	mciSendString("play photos/over.mp3", 0, 0, 0);// 播放游戏结束音效)	
}
