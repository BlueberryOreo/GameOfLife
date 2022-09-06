#include "utility.h"
#pragma once

class Life
{
private:
	int row, col;
	int* grid;
	//�ƶ�
	int* dx;
	int* dy;
	int** history;
	int historySize;
	static int generation;
	int posToIdx(int i, int j); // ת����Ϊ�����е��±꣬��i�е�j��
	int rnd(int a, int b); // ���[a, b]֮��������
	int cntNeighbour(int i, int j);
public:
	Life(int n, int m);
	~Life();
	void initialize(int flag); // flag=1: ������� else �ֶ�����
	void print(int *arr=NULL);
	void update();
	void addHis(); // �����ʷ
	int showHis(int i); // ��ʾ��ǰ��ǰ��i����ʷ
};

