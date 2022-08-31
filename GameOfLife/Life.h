#include "utility.h"
#pragma once

class Life
{
private:
	int row, col;
	int* grid;
	int* dx;
	int* dy;
	int posToIdx(int i, int j); // ת����Ϊ�����е��±꣬��i�е�j��
	int rnd(int a, int b); // ���[a, b]֮��������
	int cntNeighbour(int i, int j);
public:
	Life(int n, int m);
	~Life();
	void initialize(int flag); // flag=1: ������� else �ֶ�����
	void print();
	void update();
};

