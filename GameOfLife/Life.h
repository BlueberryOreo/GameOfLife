#include "utility.h"
#pragma once

class Life
{
private:
	int row, col;
	int* grid;
	int* dx;
	int* dy;
	int posToIdx(int i, int j); // 转坐标为数组中的下标，第i行第j列
	int rnd(int a, int b); // 获得[a, b]之间的随机数
	int cntNeighbour(int i, int j);
public:
	Life(int n, int m);
	~Life();
	void initialize(int flag); // flag=1: 随机生成 else 手动输入
	void print();
	void update();
};

