#include "utility.h"
#pragma once

class Life
{
private:
	int row, col;
	int* grid;
	//移动
	int* dx;
	int* dy;
	int** history;
	int historySize;
	static int generation;
	int posToIdx(int i, int j); // 转坐标为数组中的下标，第i行第j列
	int rnd(int a, int b); // 获得[a, b]之间的随机数
	int cntNeighbour(int i, int j);
public:
	Life(int n, int m);
	~Life();
	void initialize(int flag); // flag=1: 随机生成 else 手动输入
	void print(int *arr=NULL);
	void update();
	void addHis(); // 添加历史
	int showHis(int i); // 显示当前往前第i个历史
};

