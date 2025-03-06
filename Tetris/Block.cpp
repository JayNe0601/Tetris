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
void Block::drop() {
}
void Block::moveLeftRight(int offset) {
}
void Block::retate() {
}
void Block::draw(int leftMargin, int topMargin) {
	for (int i = 0; i < 4; i++) {// 绘制4个小方块
		int x = smallBlocks[i].col * size + leftMargin;// 计算x坐标
		int y = smallBlocks[i].row * size + topMargin;// 计算y坐标
		putimage(x, y, img);// 绘制小方块
	}
}
