#include "Tetris.h"
#include <time.h>
#include <stdlib.h>
#include"Block.h"
#include <conio.h>
#include <fstream>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")// ����winmm.lib�⣬���ڲ�������
#define MAX_LEVEL 5 //���ؿ�
#define RECORDER_FILE "data/highestScore.txt" // ��߷ּ�¼�ļ�
const int SPEED_NORMAL[MAX_LEVEL] = { 500, 450, 350, 250, 100 }; // ���ݹؿ������½��ٶ�
const int SPEED_QUICK = 30; //�½�����ٶ�
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
	srand(time(NULL));// �����������
	gameOver = false;// ��Ϸδ����
	score = 0;// ���÷���
	level = 1;// ���ùؿ�
	lineCount = 0;// ����������
	delay = SPEED_NORMAL[0];// ������ʱ
	initgraph(938, 896);// ��ʼ����Ϸ����
	loadimage(&imgBg, "photos/bg.png");// ���ر���ͼƬ
	loadimage(&gameOverImg, "photos/over.png");// ������Ϸ����ͼƬ
	for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) map[i][j] = 0;// ��Ϸ���¿�ʼʱ��������Ϸ�����з��鶼û��
	//���ļ��ж�ȡ��߷�
	ifstream file(RECORDER_FILE);// ���ļ�
	if (!file.is_open()) HighestScore = 0;// ����ļ���ʧ�ܣ���߷�Ϊ0
	else file >> HighestScore; // ��ȡ��߷֣�����߷ָ�ֵ��HighestScore
	file.close();// �ر��ļ�
}
void Tetris::play() {
	init();// ��ʼ��
	nextBlock = new Block();// ����Ԥ�淽��
	curBlock = nextBlock;// ��ǰ�������Ԥ�淽��
	nextBlock = new Block();// �����µ�Ԥ�淽��
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
		if (gameOver) {
			saveHighestScore();// ������߷�
			displayGameOver();// ��ʾ��Ϸ��������
			system("pause");// ��ͣ
			init();// ���³�ʼ�������¿�ʼ��Ϸ
		}
	}// ��Ϸ��ѭ���ṹ
}
void Tetris::keyEvent() {
	unsigned char ch;// char ��ΧΪ-128 ~ 127�� unsigned char ��ΧΪ0 ~ 255
	bool rotateFlag = false;// ��ת��־
	int dx = 0;// ˮƽ�ƶ�ƫ����
	if (_kbhit()) {// ����а������£������û�������
		ch = _getch();// ��ȡ���µļ�
		//����������ϰ������Ⱥ󷵻أ�224 72����ת
		//����������°������Ⱥ󷵻أ�224 80�������½�
		//����������󰴼����Ⱥ󷵻أ�224 75�������ƶ�
		//����������Ұ������Ⱥ󷵻أ�224 77�������ƶ�
		if (ch == 224) {
			ch = _getch();
			switch(ch) {
			case 72: 
				rotateFlag = true;
				break;// ��ת
			case 80: 
				delay = SPEED_QUICK;
				break;// �����½�
			case 75:
				dx = -1;// ����
				break;
			case 77:
				dx = 1;// ����
				break;
			default: break;
			}
		}
	}
	if (rotateFlag) {
		rorate();// ��ת
		update = true;// ���ø��±�־��ʹ��Ϸ������Ը���
	}// ��ת
	if (dx != 0) {
		moveLeftRight(dx);// �����ƶ�
		update = true;// ���ø��±�־��ʹ��Ϸ������Ը���
	}
}
void Tetris::updateWindow() {
	putimage(0, 0, &imgBg);// ���Ʊ���
	/*// ���Է���
	Block block;
	block.draw(leftMargin, topMargin);*/
	//ʹ��BeginBatchDraw()��EndBatchDraw()�������Լ�����˸����߻�ͼ�ٶ�
	BeginBatchDraw();// ��ʼ��������
	IMAGE** imgs = Block::getImgs();// ��ȡ�����ͼ��
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j] == 0) continue;
			int x = j * blockSize + leftMargin;// ����x����
			int y = i * blockSize + topMargin;// ����y����
			putimage(x, y, imgs[map[i][j] - 1]);// ���Ʒ��飬��������Ϊmap[i][j]
		}
	}
	curBlock->draw(leftMargin, topMargin);// ���Ƶ�ǰ����
	nextBlock->draw(leftMargin + 10 * blockSize + 25, topMargin - 20);// ����Ԥ�淽�飬λ�������Ϸ�
	drawScore();// ���Ʒ���
	drawLevel();// ���ƹؿ���
	drawLineCount();// ����������
	drawHighestScore();// ������߷�
	EndBatchDraw();// ������������
}
int Tetris::getDelay() {// ��һ�ε���ֱ�ӷ���0��֮��ÿ�ε��÷�����һ�ε��õ���һ�ε��õ�ʱ����
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
	bakBlock = *curBlock;// ���浱ǰ�����λ��
	curBlock->drop();// �����½�
	if (!curBlock->blockInMap(map)) {// ���鲻���½���������й̻�
		bakBlock.solidify(map);// �̻�����
		delete curBlock;// ɾ����ǰ���飬�ͷ��ڴ�
		curBlock = nextBlock;// ��ǰ�������Ԥ�淽��
		nextBlock = new Block();// �����µ�Ԥ�淽��
		checkOver();// �����Ϸ�Ƿ����
		delay = SPEED_NORMAL[level - 1];// ���ÿ����½����ٶȣ���ֹ���¼�һֱ�����½�
	}
}
void Tetris::clearLine() {
	int lines = 0;// ����������¼���е�����
	int k = rows - 1;// �������ϱ�����k��ʾ�洢���ݵ�����
	for (int i = rows - 1; i >= 0; i--) {
		bool flag = true;// ��־λ����ʾ�Ƿ�����
		for (int j = 0; j < cols; j++) {// ����Ƿ�����
			if (!map[i][j]) {
				flag = false;// ���в�����
				break;
			}
		}
		if (!flag) {// ��ʾ������
			for (int j = 0; j < cols; j++) map[k][j] = map[i][j];
			k--;
		}
		else lines++;
	}
	/*Ҳ����ʹ��һ��ɨ��һ�ߴ洢
	for (int i = rows - 1; i >= 0; i--) {
		int count = 0;// ������
		for (int j = 0; j < cols; j++) {// ����Ƿ�����
			if (map[i][j]) count++;
			map[k][j] = map[i][j]; // һ��ɨ��һ�ߴ洢
		}
		if(count < cols) k-- // �������У�k��1
		else lines++;// ���У���������1
	*/
	if (lines > 0) {
		lineCount += lines;// ����������
		score += pow(2, lines - 1);// ����÷֣�����Ϊ��������2�η���1
		mciSendString("play photos/xiaohang.mp3", 0, 0, 0);// ����������Ч, 0��ʾ����Ҫ�ص�����, play��ʾ����
		update = true;// ���ø��±�־��ʹ��Ϸ������Ը���
		// ÿ30��Ϊһ���ؿ����ؿ�Խ�ߣ������ٶ�Խ��
		level = min((score + 29) / 30, MAX_LEVEL);// ���¹ؿ�, �ҹؿ������������ؿ���
	}
}
void Tetris::moveLeftRight(int offset) {
	bakBlock = *curBlock;// ���浱ǰ�����λ��
	curBlock->moveLeftRight(offset);// �����ƶ�
	if (!curBlock->blockInMap(map)) *curBlock = bakBlock;// �ָ���ǰ�����λ��
}
void Tetris::rorate() {
	if (curBlock->getBlockType() == 7) return;// ���ַ��鲻����ת
	bakBlock = *curBlock;// ���浱ǰ�����λ��
	curBlock->rotate();// ��ת
	if (!curBlock->blockInMap(map)) *curBlock = bakBlock;// �ָ���ǰ�����λ��
}
void Tetris::drawScore() {
	LOGFONT f;// ��������
	gettextstyle(&f);// ��ȡ��ǰ����
	f.lfHeight = 40;// ����������
	f.lfWeight = 25;//	���������ϸ
	f.lfQuality = ANTIALIASED_QUALITY; // ��������������������ݡ�Ч��
	settextstyle(&f);// ��������
	settextcolor(WHITE);// ����������ɫ
	char scoreText[32];// �����ַ���
	sprintf_s(scoreText, sizeof(scoreText), "%d", score);// ��ʽ���ַ���
	outtextxy(670, 730, scoreText);// �������
}
void Tetris::drawLevel() {
	LOGFONT f;// ��������
	gettextstyle(&f);// ��ȡ��ǰ����
	f.lfHeight = 40;// ����������
	f.lfWeight = 25;//	���������ϸ
	f.lfQuality = ANTIALIASED_QUALITY; // ��������������������ݡ�Ч��
	settextstyle(&f);// ��������
	settextcolor(WHITE);// ����������ɫ
	char levelText[32];// �����ַ���
	sprintf_s(levelText, sizeof(levelText), "%d", level);// ��ʽ���ַ���
	outtextxy(210 - f.lfWidth * strlen(levelText), 730, levelText);// ����ؿ���
}
void Tetris::drawLineCount() {
	LOGFONT f;// ��������
	gettextstyle(&f);// ��ȡ��ǰ����
	f.lfHeight = 40;// ����������
	f.lfWeight = 25;//	���������ϸ
	f.lfQuality = ANTIALIASED_QUALITY; // ��������������������ݡ�Ч��
	settextstyle(&f);// ��������
	settextcolor(WHITE);// ����������ɫ
	char lineCountText[32];// �����ַ���
	sprintf_s(lineCountText, sizeof(lineCountText), "%d", lineCount);// ��ʽ���ַ���
	outtextxy(210 - f.lfWidth * strlen(lineCountText), 820, lineCountText);// ���������
}
void Tetris::drawHighestScore() {
	LOGFONT f;// ��������
	gettextstyle(&f);// ��ȡ��ǰ����
	f.lfHeight = 40;// ����������
	f.lfWeight = 25;//	���������ϸ
	f.lfQuality = ANTIALIASED_QUALITY; // ��������������������ݡ�Ч��
	settextstyle(&f);// ��������
	settextcolor(WHITE);// ����������ɫ
	char highestScoreText[32];// �����ַ���
	sprintf_s(highestScoreText, sizeof(highestScoreText), "%d", HighestScore);// ��ʽ���ַ���
	outtextxy(670, 820, highestScoreText);// �����߷�
}
void Tetris::checkOver() {
	// �����Ϸ�Ƿ����
	if (curBlock->blockInMap(map) == false) gameOver = true;// ��Ϸ����
}
void Tetris::saveHighestScore() {
	if (score > HighestScore) HighestScore = score;// ������߷�
	ofstream file(RECORDER_FILE);// ���ļ�
	file << HighestScore;// д����߷�
	file.close();// �ر��ļ�
}
void Tetris::displayGameOver() {
	putimage(260, 360, &gameOverImg);// ������Ϸ����ͼƬ
	mciSendString("play photos/over.mp3", 0, 0, 0);// ������Ϸ������Ч)	
}
