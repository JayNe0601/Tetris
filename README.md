# 俄罗斯方块
## 项目介绍
> 俄罗斯方块游戏，由纯C++语言编写。
## 模块设计
> 方块类（block） <--关联--> 游戏类（tetris） ；
1. Block类 表示方块；
2. Tetris类 表示俄罗斯方块游戏。
## 创建项目
> 添加类Block和Tetris
## 设计Block和Tetris主要接口
Block类
```
class Block {
public:
	Block();
	void drop();
	void moveLeftRight(int offset);
	void retate(); //旋转
	void draw(int leftMargin, int topMargin);
};
```

Tetris类
```
class Tetris {
public:
	Tetris(int rows, int cols, int left, int top, int blockSize);
	void init();
	void play();
};
```
## 启动游戏
main.cpp
```
#include "Tetris.h"
int main(void) {
	Tetris game(20, 10, 163, 133, 36);// 创建一个俄罗斯方块游戏对象，20行，10列，左边界163，上边界133，方块大小36
	game.play();// 开始游戏
	return 0;
}
```
## 实现游戏的主体架构
###  游戏主体架构
Tetris.cpp
```
void Tetris::play() {
	init();// 初始化
	int timer = 0;// 计时器，为防止渲染CPU空转，可以在这里加一个延时，使游戏画面渲染在多少秒渲染1次
	while (1) {
		keyEvent();// 待定义，接受用户的输入
		timer += getDelay();//待定义，获取距离上一次调用该函数，间隔了多少时间（ms）
		if (timer > delay) {
			timer = 0;// 重置计时器
			drop();//待定义，方块下落
			update = true;// 待定义，设置更新标志，使游戏画面得以更新
		}
		if (update) {
			update = false;// 重置更新标志
			updateWindow();// 待定义，渲染游戏画面，更新游戏画面
			clearLine();//待定义，清行，更新游戏相关数据
		}
	}// 游戏的循环结构
}
```
### 补充私有数据成员
Tetris.h
```
private:
	int delay;// 延时
	bool update;// 是否更新
```
### 补充私有成员函数
Tetris.h
```
private:
	void keyEvent();//键盘事件
	void updateWindow();// 渲染游戏画面
	int getDelay();//返回距离上一次调用该函数，间隔了多少时间（ms），第一次调用返回0
	void drop();//方块下落
	void clearLine();//消行
```
### 完善游戏主体架构

## 创建新方块
> 在调用 new Block 时，会自动调用Block的默认构造函数，所以我们需要在这个构造函数里面完成新方块的创建。

> 俄罗斯方块的表示方法有很多，最常见的是使用一个二维数组，表示一种俄罗斯方块的某种形态，也就是说，一个俄罗斯方块，需要使用4个二维数组来表示各个形态（4个方向）。
```
|01|
|23|
|45|  
|67|
```
```
int blocks[7][4] = {
		1,3,5,7, // I
		2,4,5,7, // Z 1型
		3,5,4,6, // Z 2型
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // 田
};
```
> 此方案只需建立一个二维数组建立方块的最初形态，后续变化的形态用算法解决。
