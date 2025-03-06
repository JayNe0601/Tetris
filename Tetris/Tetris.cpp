#include "Tetris.h"
#include <time.h>
#include <stdlib.h>
const int SPEED_NORMAL = 500; //�½������ٶ�
const int SPEED_QUICK = 50; //�½�����ٶ�
Tetris::Tetris(int rows, int cols, int left, int top, int blockSize) {
	this->rows = rows;// ��ʼ������
	this->cols = cols;// ��ʼ������
	this->leftMargin = left;// ��ʼ����߽�
	this->blockSize = blockSize;// ��ʼ�������С
	this->topMargin = top;// ��ʼ���ϱ߽�
	map.resize(rows);// ��ʼ����ͼ
	for (int i = 0; i < rows; i++) {
		vector<int> rowt;// ��ʼ��ÿһ��
		for (int j = 0; j < cols; j++) rowt.push_back(0);// ��ʼ��ÿһ�У�0��ʾû�з���
		map[i] = rowt;// ��ÿһ�м��뵽��ͼ��
	}
}
void Tetris::init() {
	delay = SPEED_NORMAL;// ������ʱ
	srand(time(NULL));// �����������
	initgraph(938, 896);// ��ʼ����Ϸ����
	// ���ر���ͼƬ
	loadimage(&imgBg, "photos/bg.png");
	for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) map[i][j] = 0;// ��Ϸ���¿�ʼʱ��������Ϸ�����з��鶼û��
}
void Tetris::play() {
	init();// ��ʼ��
	int timer = 0;// ��ʱ����Ϊ��ֹ��ȾCPU��ת�������������һ����ʱ��ʹ��Ϸ������Ⱦ�ڶ�������Ⱦ1��
	while (1) {
		keyEvent();// �����û�������
		timer += getDelay();// ��ȡ������һ�ε��øú���������˶���ʱ�䣨ms��
		if (timer > delay) {
			timer = 0;// ���ü�ʱ��
			drop();// ��������
			update = true;// ���ø��±�־��ʹ��Ϸ������Ը���
		}
		if (update) {
			update = false;// ���ø��±�־
			updateWindow();// ��Ⱦ��Ϸ���棬������Ϸ����
			clearLine();//���У�������Ϸ�������
		}
	}// ��Ϸ��ѭ���ṹ
}

void Tetris::keyEvent() {
	update = true;// ���ø��±�־��ʹ��Ϸ������Ը���
}
void Tetris::updateWindow() {
	putimage(0, 0, &imgBg);// ���Ʊ���
}
// ��һ�ε���ֱ�ӷ���0��֮��ÿ�ε��÷�����һ�ε��õ���һ�ε��õ�ʱ����
int Tetris::getDelay() {
	static unsigned long long lastTime = 0;// ��ȡϵͳʱ��
	unsigned long long currenTime = GetTickCount();// ��ȡϵͳʱ��
	if (lastTime == 0) {// ��һ�ε���
		lastTime = currenTime;// ��ʼ����һ�ε�ʱ��
		return 0;// ��һ�ε���ֱ�ӷ���0
	}
	else {// ֮��ĵ���
		int ret = currenTime - lastTime;// ��ȡʱ����
		lastTime = currenTime;// ������һ�ε�ʱ��
		return ret;// ����ʱ����
	}
}

void Tetris::drop() {
}

void Tetris::clearLine() {
}
