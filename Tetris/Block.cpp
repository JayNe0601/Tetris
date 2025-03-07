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
void Block::drop() { for (auto &i : smallBlocks) i.row++; }// ��������
void Block::moveLeftRight(int offset) {
	// �����ƶ�
	for (auto& i : smallBlocks) i.col += offset;
}
void Block::rotate() {
	/*// 1. ��ת������������ת�ã�ֻ��Ҫ�������м��ɣ����������
	for (int i = 0; i < 4; i++) swap(smallBlocks[i].row, smallBlocks[i].col);*/
	//���ʵ���ת���Եڶ���С����Ϊ������ת
	Point p = smallBlocks[1];// ��ȡ�ڶ���С����
	/*��ѧ��ʽ��
	��ĳ����ת����p��ʱ����ת90�ȵĹ�ʽΪ��
	tmp = x;
	x.row = p.row - (tmp.col - p.col);
	x.col = p.col + (tmp.row - p.row);
	*/
	for (int i = 0; i < 4; i++) {
		Point tmp = smallBlocks[i];
		smallBlocks[i].row = p.row - (tmp.col - p.col);
		smallBlocks[i].col = p.col + (tmp.row - p.row);// ���ù�ʽ������ת
	}
}
void Block::draw(int leftMargin, int topMargin) {
	for (int i = 0; i < 4; i++) {// ����4��С����
		int x = smallBlocks[i].col * size + leftMargin;// ����x����
		int y = smallBlocks[i].row * size + topMargin;// ����y����
		putimage(x, y, img);// ����С����
	}
}
IMAGE** Block::getImgs() { return imgs; }
Block& Block::operator=(const Block& other) {
	if (this == &other) return *this;
	this->blockType = other.blockType;
	for (int i = 0; i < 4; i++) this->smallBlocks[i] = other.smallBlocks[i];
	return *this;
}// ��ֵ���������
bool Block::blockInMap(const vector<vector<int>>& map) {
	int rows = map.size();// ����
	int cols = map[0].size();// ����
	for (int i = 0; i < 4; i++) if (smallBlocks[i].col < 0 || smallBlocks[i].col >= cols || smallBlocks[i].row < 0 || smallBlocks[i].row >= rows || map[smallBlocks[i].row][smallBlocks[i].col]) return false;
	// �жϷ����Ƿ��ڵ�ͼ�� 1.С�����ڵ�ͼ�� 2.С�����ڵ�ͼ���з��� ����false
	return true;
}
void Block::solidify(vector<vector<int>>& map) {
	// �̻�λ��
	for (int i = 0; i < 4; i++) map[smallBlocks[i].row][smallBlocks[i].col] = blockType;
}

int Block::getBlockType() { return blockType; }
