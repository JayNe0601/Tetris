#pragma once
#include <graphics.h> //ͼ�ο�
struct Point {
	int row, col;
};
class Block {
public:
	Block();//���캯��
	void drop();//����
	void moveLeftRight(int offset);//�����ƣ�����offset���������ж����ƻ�������
	void retate();//��ת
	void draw(int leftMargin, int topMargin);//������߽���ϱ߽�
private:
	int blockType;//��������
	Point smallBlocks[4];//�����4���������
	IMAGE* img;//ͼ��ָ������ָ����Ӧ��ͼ��
	//��̬��Ա���������ж��������ڴ洢7�ַ����ͼ��
	static IMAGE* imgs[7];//7�ַ����ͼ�񣬾�̬��Ա������ָ�������ڴ����
	static int size;//����Ĵ�С
};