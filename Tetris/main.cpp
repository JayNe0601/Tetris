#include "Tetris.h"


int main(void) {
	Tetris game(20, 10, 263, 133, 36);// 创建一个俄罗斯方块游戏对象，20行，10列，左边界263，上边界133，方块大小36
	game.play();// 开始游戏
	return 0;
}