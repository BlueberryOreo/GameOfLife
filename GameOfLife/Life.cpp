#include "Life.h"

// private
int Life::generation = 0;

int Life::posToIdx(int i, int j)
{
	if (i < 1 || i > row || j < 1 || j > col) {
		//越界
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
		if (idx == -1) continue; //边界，直接当成0
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
	history = new int* [10];
	historySize = 0;
	dx = new int[8] {1, -1, 0, 0, 1, 1, -1, -1};
	dy = new int[8] {0, 0, 1, -1, 1, -1, 1, -1};
}

Life::~Life() {
	if(grid) delete grid;
	for (int i = 0; i < historySize; i++) {
		//cout << i << " ";
		delete history[i];
	}
	//if(history) delete history;
	if(dx) delete dx;
	if(dy) delete dy;
}

void Life::initialize(int flag=1)
{
	if (flag == -2) {
		// 从文件读入
		ifstream ifs;
		string path;
		cout << "请输入要导入的文件的绝对路径（文件中死细胞用空格\' \'表示，活细胞请用ASCII码除空格以外的可见字符表示）\n" 
			<< "（一行全部死亡请用一个空格表示，行数不得超过51，列数不得超过88）：" << endl;
		cin >> path;
		ifs.open(path);
		if (!ifs) {
			cout << "未能成功打开文件！请检查路径输入是否正确" << endl;
			system("pause");
			exit(0);
		}
		int l_row = 0;
		int l_col = 0;
		int max_col = 0;
		char tmp;
		bool isOutOfBound = false;
		// 找出输入文件的行数和列数，并判断是否合法
		while ((tmp = ifs.get()) != EOF) {
			if (tmp == '\n') {
				//cout << endl;
				if (l_col == 0) {
					break;
				}
				max_col = max(max_col, l_col);
				//cout << col << " " << l_col << endl;
				l_row++;
				l_col = 0;
				continue;
			}
			if (l_col >= 88 || l_row >= 51) {
				isOutOfBound = true;
				break;
			}
			l_col++;
		}
		row = l_row + (l_col == 0 ? 0 : 1);
		col = max_col;
		//cout << row << " " << col << endl;
		if (isOutOfBound) {
			cout << "输入越界！row=" << row << " col=" << col << endl;
			system("pause");
			ifs.close();
			exit(0);
		}
		ifs.close();
		ifs.open(path);
		//cout << ifs.tellg() << endl;
		l_col = 0;
		l_row = 0;
		while ((tmp = ifs.get()) != EOF) {
			if (tmp == '\n') {
				l_col = 0;
				l_row++;
				continue;
			}
			int idx = posToIdx(l_row + 1, l_col + 1);
			grid[idx] = (tmp == ' ' ? 0 : 1);
			l_col++;
		}
		//cout << row << " " << col << endl;
		ifs.close();
		//print();
		//exit(0);
		return;
	}
	if (flag == -1) flag = 0;
	for (int i = 1; i <= row; i ++) {
		int n;
		if (!flag) {
			cout << "请输入第" << i << "(/" << row << ")行活着的细胞的个数，输入-1结束输入" << endl;
			cin >> n;
			while ((n < 0 && n != -1) || n > col) {
				cout << "输入越界，请重新输入：" << endl;
				cin >> n;
			}
			if (n == 0) continue;
			if (n == -1) return;
			cout << "请输入这些细胞的列数：" << endl;
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
				cout << "下标越界，请重新输入：" << endl;
				cin >> j;
				idx = posToIdx(i, j);
			}
			grid[idx] = 1;
		}
	}
}

void Life::print(int *arr)
{
	//system("cls");
	//clear();
	//cout << row << " " << col << endl;
	for (int i = 1; i <= row; i ++) {
		for (int j = 1; j <= col; j ++) {
			int idx = posToIdx(i, j);
			if (arr) {
				cout << (arr[idx] ? "■" : "□");
				//cout << (arr[idx] ? "x" : " ");
			}
			else {
				cout << (grid[idx] ? "■" : "□");
				//cout << (grid[idx] ? "x" : " ");
			}
			//cout << grid[idx];
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
			//二进制的两位，第一位记录当前状态，第二位记录下一次的状态
			if (grid[idx] & 1) {
				//当前是活着的
				if (neighbours == 2 || neighbours == 3) {
					grid[idx] += (1 << 1); //下一个状态还是活着的
				}
				else {
					grid[idx] += (0 << 1); //下一个状态死了
				}
			}
			else {
				if (neighbours == 3) {
					grid[idx] += (1 << 1); //下一个状态可以活
				}
			}
		}
	}
	for (int i = 1; i <= row; i ++) {
		for (int j = 1; j <= col; j ++) {
			//更新，下一次的状态覆盖当前状态
			grid[posToIdx(i, j)] >>= 1;
		}
	}
	generation++;
}

void Life::addHis() {
	// 存到10个历史记录，将最早的去除（用最新的覆盖）
	if (historySize == 10) {
		int i = 1, j = 9;
		while (i < j) {
			swap(history[i], history[j]);
			i++, j--;
		}
		i = 0, j = 9;
		while (i < j) {
			swap(history[i], history[j]);
			i++, j--;
		}
	}
	//cout << historySize << " " << generation << endl;
	//for (int i = 0; i < historySize; i++) cout << history[i] << " ";
	//cout << endl;
	if(historySize == generation) history[historySize] = new int[(row + 2) * (col + 2)];
	int nowHis = historySize - (historySize == 10);
	for (int i = 0; i < (row + 2) * (col + 2); i++) {
		history[nowHis][i] = grid[i];
	}
	if (historySize < 10) historySize++;
}

int Life::showHis(int i) {
	int l_generation = generation - i + 1;
	//cout << generation << " " << i << endl;
	if (l_generation < 0 || i > 9) return -1; // 前面没有了
	if (i <= 0) return -2; // 后面没有了
	int flag = l_generation % 10;
	if (l_generation >= 11 && l_generation <= 13) flag = 0;
	if (flag != 1 && flag != 2 && flag != 3) flag = 0;
	cout << "The " << l_generation
		<< (flag != 0 ? (flag != 1 ? (flag != 2 ? "rd" : "nd") : "st") : "th")
		<< " generation" << endl;
	//cout << i << endl;
	print(history[historySize - i]);
	return 1;
}