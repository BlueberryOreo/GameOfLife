#include "Life.h"

// private
int Life::posToIdx(int i, int j)
{
	if (i < 1 || i > row || j < 1 || j > col) {
		//Խ��
		//cout << "Out of bound: i=" << i << " j=" << j << endl;
		return -1;
	}
	return i * (col + 2) + 1 + j;
}

int Life::rnd(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

int Life::cntNeighbour(int i, int j) {
	int ret = 0;
	for (int k = 0; k < 8; k ++) {
		int x = i + dx[k];
		int y = j + dy[k];
		int idx = posToIdx(x, y);
		if (idx == -1) continue; //�߽磬ֱ�ӵ���0
		if (grid[idx] & 1) {
			ret++;
		}
	}
	return ret;
}

// public
Life::Life(int n = 51, int m = 88) {
	if (n <= 0 || m <= 0) {
		n = 51;
		m = 88;
	}
	row = n;
	col = m;
	grid = new int[(row + 2) * (col + 2)] {0};
	dx = new int[8] {1, -1, 0, 0, 1, 1, -1, -1};
	dy = new int[8] {0, 0, 1, -1, 1, -1, 1, -1};
}

Life::~Life() {
	if(grid) delete grid;
	if(dx) delete dx;
	if(dy) delete dy;
}

void Life::initialize(int flag = 1)
{
	for (int i = 1; i <= row; i ++) {
		int n;
		if (!flag) {
			cout << "�������" << i << "(/" << row << ")�л��ŵ�ϸ���ĸ���������-1��������" << endl;
			cin >> n;
			while ((n < 0 && n != -1) || n > col) {
				cout << "����Խ�磬���������룺" << endl;
				cin >> n;
			}
			if (n == 0) continue;
			if (n == -1) return;
			cout << "��������Щϸ����������" << endl;
		}
		else { 
			n = rnd(0, col);
		}

		int j, idx;
		for (int k = 0; k < n; k ++) {
			if (!flag) {
				cin >> j;
			}
			else { 
				j = rnd(1, col);
			}

			idx = posToIdx(i, j);
			while (idx < 0) {
				cout << "�±�Խ�磬���������룺" << endl;
				cin >> j;
				idx = posToIdx(i, j);
			}
			grid[idx] = 1;
		}
	}
}

void Life::print()
{
	//system("cls");
	//clear();
	//cout << row << " " << col << endl;
	for (int i = 1; i <= row; i ++) {
		for (int j = 1; j <= col; j ++) {
			int idx = posToIdx(i, j);
			cout << (grid[idx] ? "��" : "��");
			//cout << (grid[idx] ? 'x' : ' ');
			//cout << j << " ";
			//cout << idx << " ";
		}
		//cout << "done";
		cout << endl;
	}
}

void Life::update()
{
	for (int i = 1; i <= row; i ++) {
		for (int j = 1; j <= col; j++) {
			int neighbours = cntNeighbour(i, j);
			int idx = posToIdx(i, j);
			//�����Ƶ���λ����һλ��¼��ǰ״̬���ڶ�λ��¼��һ�ε�״̬
			if (grid[idx] & 1) {
				//��ǰ�ǻ��ŵ�
				if (neighbours == 2 || neighbours == 3) {
					grid[idx] += (1 << 1); //��һ��״̬���ǻ��ŵ�
				}
				else {
					grid[idx] += (0 << 1); //��һ��״̬����
				}
			}
			else {
				if (neighbours == 3) {
					grid[idx] += (1 << 1); //��һ��״̬���Ի�
				}
			}
		}
	}
	for (int i = 1; i <= row; i ++) {
		for (int j = 1; j <= col; j ++) {
			//���£���һ�ε�״̬���ǵ�ǰ״̬
			grid[posToIdx(i, j)] >>= 1;
		}
	}
}
