#pragma once
#include <vector>
#include <graphics.h>
using namespace std;
class Tetris {
public:
	Tetris(int rows, int cols, int left, int top, int blockSize);//���캯������ʼ������˹����Ϸ����������������߽硢�ϱ߽硢�����С
	void init(); //��ʼ��
	void play(); //��ʼ��Ϸ
private:
	void keyEvent();//�����¼�
	void updateWindow();// ��Ⱦ��Ϸ����
	int getDelay();//���ؾ�����һ�ε��øú���������˶���ʱ�䣨ms������һ�ε��÷���0
	void drop();//��������
	void clearLine();//����
private:
	int delay;// ��ʱ
	bool update;// �Ƿ����
	vector<vector<int>> map;// ��Ϸ��ͼ��0��ʾû�з��飬1��ʾ��һ�ַ��飬2��ʾ�ڶ��ַ��飬�Դ�����
	int rows;// ����
	int cols;// ����
	int leftMargin;// ��߽�
	int topMargin;// �ϱ߽�
	int blockSize;// �����С
	IMAGE imgBg;// ����ͼ
};

