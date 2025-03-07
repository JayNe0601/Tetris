#pragma once
#include <graphics.h> //ͼ�ο�
#include <vector>
using namespace std;
struct Point {
	int row, col;
};
class Block {
public:
	Block();//���캯��
	void drop();//����
	void moveLeftRight(int offset);//�����ƣ�����offset���������ж����ƻ�������
	void rotate();//��ת
	void draw(int leftMargin, int topMargin);//������߽���ϱ߽�
	static IMAGE** getImgs();// ��ȡ�����ͼ��
	Block& operator=(const Block& other);//��ֵ���������
	bool blockInMap(const vector<vector<int>>& map);// �жϷ����Ƿ��ڵ�ͼ��
	void solidify(vector<vector<int>>& map);// ����̻�
	int getBlockType();// ��ȡ��������
private:
	int blockType;//��������
	Point smallBlocks[4];//�����4���������
	IMAGE* img;//ͼ��ָ������ָ����Ӧ��ͼ��
	//��̬��Ա���������ж��������ڴ洢7�ַ����ͼ��
	static IMAGE* imgs[7];//7�ַ����ͼ�񣬾�̬��Ա������ָ�������ڴ����
	static int size;//����Ĵ�С
};