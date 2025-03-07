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
	Tetris game(20, 10, 263, 133, 36);// 创建一个俄罗斯方块游戏对象，20行，10列，左边界263，上边界133，方块大小36
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
```
IMAGE *Block::imgs[7] = { NULL, };//待定义， 7种方块的图像
int Block::size = 36;//待定义， 方块的大小
Block::Block() {
	if (imgs[0] == NULL) {
		IMAGE imgTmp;// 临时图像
		loadimage(&imgTmp, "photo/blocks.png");// 加载图片
		SetWorkingImage(&imgTmp);// 设置工作群
		for (int i = 0; i < 7; i++) {// 切割图片
			imgs[i] = new IMAGE;// 为每个方块分配内存
			getimage(imgs[i], i * size, 0, size, size);// 切割图片
		}
		SetWorkingImage();// 恢复工作群
	}// 加载图片
	int blocks[7][4] = {
		1,3,5,7, // I
		2,4,5,7, // Z 1型
		3,5,4,6, // Z 2型
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // 田
	};// 7种方块的形状
	blockType = 1 + rand() % 7;//待定义， 随机产生一个方块 1 ~ 7
	for (int i = 0; i < 4; i++) {// 待定义，初始化smallBlocks在第几行第几列
		int value = blocks[blockType - 1][i];
		smallBlocks[i].row = value / 2;
		smallBlocks[i].col = value % 2;
	}
	img = imgs[blockType - 1];//待定义， 设置每个小方块图像
}
```
> 用结构体Point存每个小方块的坐标
```
struct Point {
	int row, col;
};
```

> 把所有的方块图像，定义为Block类的static数据成员

### 下载配置easyx图形库
> 通过官网下载，运行安装包，下载对应的版本

### 导入图片

> 将包含7种方块的图片导入，并切割成7个小的方块，修改字符集为使用多字节字符集

### 补充私有数据成员
block.h
```
private:
	int blockType;//方块类型
	Point smallBlocks[4];//方块的4个点的坐标
	IMAGE *img;//图像，指针用于指向相应的图像
	//静态成员变量，所有对象共享，用于存储7种方块的图像
	static IMAGE *imgs[7];//7种方块的图像，静态成员变量，指针用于内存分配
	static int size;//方块的大小
```
### 补充私有成员函数
block.cpp
```
public:
	Block();//构造函数
	void drop();//下落
	void moveLeftRight(int offset);//左右移，根据offset的正负来判断左移还是右移
	void retate();//旋转
	void draw(int leftMargin, int topMargin);//绘制左边界和上边界
```
## 绘制方块
> 绘制方块，补充draw函数
```
void Block::draw(int leftMargin, int topMargin) {
	for (int i = 0; i < 4; i++) {// 绘制4个小方块
		int x = smallBlocks[i].col * size + leftMargin;// 计算x坐标
		int y = smallBlocks[i].row * size + topMargin;// 计算y坐标
		putimage(x, y, img);// 绘制小方块
	}
}
```
## 实现游戏场景
### 游戏过程中数据的存储
> 更新私有数据成员
tetris.h
```
private:
	vector<vector<int>> map;// 游戏地图
	int rows;// 行数
	int cols;// 列数
	int leftMargin;// 左边界
	int topMargin;// 上边界
	int blockSize;// 方块大小
	IMAGE imgBg;// 背景图

```

### 数据的初始化
> 对游戏的数据通过构造函数进行初始化
```
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
```

### 初始化游戏场景
```
const int SPEED_NORMAL = 500; //下降慢的速度
const int SPEED_QUICK = 50; //下降快的速度
void Tetris::init() {
	delay = SPEED_NORMAL;// 设置延时
	srand(time(NULL));// 配置随机种子
	initgraph(938, 896);// 初始化游戏窗口
	// 加载背景图片
	loadimage(&imgBg, "photos/bg.png");
	for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) map[i][j] = 0;// 游戏重新开始时，重置游戏，所有方块都没有
}
```

## 测试方块
```
void Tetris::updateWindow() {
	putimage(0, 0, &imgBg);// 绘制背景
	// 测试方块
	Block block;
	block.draw(leftMargin, topMargin);// 绘制方块

}
```