#pragma once
#include <vector>
#include <graphics.h>
#include "Block.h"
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
	void moveLeftRight(int offset);// �����ƶ�
	void rorate();//��ת
	void drawScore();// ���Ʒ���
	void drawLevel();// ���ƹؿ�
	void drawLineCount();// ����������
	void drawHighestScore();// ������߷�
	void checkOver();//�����Ϸ�Ƿ����
	void saveHighestScore();//������߷�
	void displayGameOver();//������ʾ��Ϸ��������
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
	Block* curBlock;// ��ǰ����
	Block* nextBlock;// Ԥ�淽��
	Block bakBlock;// ��ǰ���齵������У�����������һ����������ĺϷ�λ��
	int score;// ��ǰ�ķ���
	int HighestScore;// ��߷�
	int level;// ��ǰ�ؿ�
	int lineCount; // ��ǰ������
	bool gameOver;// ��Ϸ�Ƿ����
	IMAGE gameOverImg;// ��Ϸ����ͼƬ
};

