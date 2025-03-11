# 俄罗斯方块
## 项目介绍
> 俄罗斯方块是一款经典的益智游戏，玩家通过控制不同形状的方块，使其在游戏区域内堆叠并消除完整的行。
>
> 游戏的目标是尽可能多地消除行并获得高分，该项目由纯C++语言编写，采用面向对象的思想。
## 项目框架
> 该项目使用C++编写，主要包括以下几个模块：
> 1. Tetris：游戏的核心逻辑，包括初始化、游戏循环、键盘事件处理、方块下落、消行、绘制界面等。
> 2. Block：方块的定义和操作，包括方块的生成、旋转、移动、绘制等。
> 3. main：程序的入口，启动游戏。
## 主要特性
> 1. 方块的随机生成和控制（旋转、左右移动、快速下落）
> 2. 行消除和得分计算
> 3. 多关卡支持，不同关卡有不同的下落速度
> 4. 游戏结束检测和最高分记录
> 5. 简单的图形界面和音效支持
## 技术栈
> 1. 编程语言：C++
> 2. 图形库：EasyX
> 3. 音效库：winmm.lib
## 功能说明
> 1. 初始化游戏窗口和资源
> 2. 生成和控制方块
> 3. 检测和处理行消除
> 4. 更新和绘制游戏界面
> 5. 记录和显示最高分
> 6. 支持多关卡和不同下落速度
## 目录结构
```
Tetris/
├── Block.cpp          // 方块的实现文件
├── Block.h            // 方块的头文件
├── Tetris.cpp         // 游戏核心逻辑实现文件
├── Tetris.h           // 游戏核心逻辑头文件
├── main.cpp           // 程序入口文件
├── photos/            // 存放游戏图片和音效的目录
│   ├── bg.png         // 背景图片
│   ├── over.png       // 游戏结束图片
│   ├── xiaohang.mp3   // 消行音效
│   ├── over.mp3       // 游戏结束音效
└── data/
    └── highestScore.txt // 最高分记录文件
```
