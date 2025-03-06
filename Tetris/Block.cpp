#include "Block.h"
#include <stdlib.h>
IMAGE* Block::imgs[7] = { NULL, };// 7�ַ����ͼ��
int Block::size = 36;// ����Ĵ�С
Block::Block() {
	if (imgs[0] == NULL) {
		IMAGE imgTmp;// ��ʱͼ��
		loadimage(&imgTmp, "photos/blocks.png");// ����ͼƬ
		SetWorkingImage(&imgTmp);// ���ù���Ⱥ
		for (int i = 0; i < 7; i++) {// �и�ͼƬ
			imgs[i] = new IMAGE;// Ϊÿ����������ڴ�
			getimage(imgs[i], i * size, 0, size, size);// �и�ͼƬ
		}
		SetWorkingImage();// �ָ�����Ⱥ
	}// ����ͼƬ
	int blocks[7][4] = {
		1,3,5,7, // I
		2,4,5,7, // Z 1��
		3,5,4,6, // Z 2��
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // ��
	};// 7�ַ������״
	blockType = 1 + rand() % 7;// �������һ������ 1 ~ 7
	for (int i = 0; i < 4; i++) {//��ʼ��smallBlocks�ڵڼ��еڼ���
		int value = blocks[blockType - 1][i];
		smallBlocks[i].row = value / 2;
		smallBlocks[i].col = value % 2;
	}
	img = imgs[blockType - 1];// ����ÿ��С����ͼ��
}
void Block::drop() {
}
void Block::moveLeftRight(int offset) {
}
void Block::retate() {
}
void Block::draw(int leftMargin, int topMargin) {
	for (int i = 0; i < 4; i++) {// ����4��С����
		int x = smallBlocks[i].col * size + leftMargin;// ����x����
		int y = smallBlocks[i].row * size + topMargin;// ����y����
		putimage(x, y, img);// ����С����
	}
}
