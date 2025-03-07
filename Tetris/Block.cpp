#include "Block.h"
#include <stdlib.h>
IMAGE* Block::imgs[7] = { NULL, };// 7种方块的图像
int Block::size = 36;// 方块的大小
Block::Block() {
	if (imgs[0] == NULL) {
		IMAGE imgTmp;// 临时图像
		loadimage(&imgTmp, "photos/blocks.png");// 加载图片
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
	blockType = 1 + rand() % 7;// 随机产生一个方块 1 ~ 7
	for (int i = 0; i < 4; i++) {//初始化smallBlocks在第几行第几列
		int value = blocks[blockType - 1][i];
		smallBlocks[i].row = value / 2;
		smallBlocks[i].col = value % 2;
	}
	img = imgs[blockType - 1];// 设置每个小方块图像
}
void Block::drop() { for (auto &i : smallBlocks) i.row++; }// 方块下落
void Block::moveLeftRight(int offset) {
	// 左右移动
	for (auto& i : smallBlocks) i.col += offset;
}
void Block::rotate() {
	/*// 1. 旋转，类似与矩阵的转置，只需要交换行列即可，会出现问题
	for (int i = 0; i < 4; i++) swap(smallBlocks[i].row, smallBlocks[i].col);*/
	//合适的旋转，以第二个小方块为中心旋转
	Point p = smallBlocks[1];// 获取第二个小方块
	/*数学公式：
	按某个旋转中心p逆时针旋转90度的公式为：
	tmp = x;
	x.row = p.row - (tmp.col - p.col);
	x.col = p.col + (tmp.row - p.row);
	*/
	for (int i = 0; i < 4; i++) {
		Point tmp = smallBlocks[i];
		smallBlocks[i].row = p.row - (tmp.col - p.col);
		smallBlocks[i].col = p.col + (tmp.row - p.row);// 利用公式进行旋转
	}
}
void Block::draw(int leftMargin, int topMargin) {
	for (int i = 0; i < 4; i++) {// 绘制4个小方块
		int x = smallBlocks[i].col * size + leftMargin;// 计算x坐标
		int y = smallBlocks[i].row * size + topMargin;// 计算y坐标
		putimage(x, y, img);// 绘制小方块
	}
}
IMAGE** Block::getImgs() { return imgs; }
Block& Block::operator=(const Block& other) {
	if (this == &other) return *this;
	this->blockType = other.blockType;
	for (int i = 0; i < 4; i++) this->smallBlocks[i] = other.smallBlocks[i];
	return *this;
}// 赋值运算符重载
bool Block::blockInMap(const vector<vector<int>>& map) {
	int rows = map.size();// 行数
	int cols = map[0].size();// 列数
	for (int i = 0; i < 4; i++) if (smallBlocks[i].col < 0 || smallBlocks[i].col >= cols || smallBlocks[i].row < 0 || smallBlocks[i].row >= rows || map[smallBlocks[i].row][smallBlocks[i].col]) return false;
	// 判断方块是否在地图中 1.小方块在地图外 2.小方块在地图中有方块 返回false
	return true;
}
void Block::solidify(vector<vector<int>>& map) {
	// 固化位置
	for (int i = 0; i < 4; i++) map[smallBlocks[i].row][smallBlocks[i].col] = blockType;
}

int Block::getBlockType() { return blockType; }
