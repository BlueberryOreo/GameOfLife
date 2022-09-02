#include "utility.h"
#include "Life.h"

void instructions(int &n, int &m, int &flag1, int &flag2, int &interval) {
	cout << "请输入行数（最大51）：" << endl;
	cin >> n;
	if (n > 51) n = 51;
	cout << "请输入列数（最大88）：" << endl;
	cin >> m;
	if (m > 88) m = 88;
	cout << "是否随机初始化？(Y/N)" << endl;
	char choice;
	cin >> choice;
	if (choice == 'Y' || choice - 'a' + 'A' == 'Y') flag1 = 1;
	else flag1 = 0;
	cout << "是否自动播放？(Y/N)[播放后按Ctrl+C退出]" << endl;
	cin >> choice;
	if (choice == 'Y' || choice - 'a' + 'A' == 'Y') {
		flag2 = 1;
		cout << "请输入每一代的间隔时间(ms)：" << endl;
		cin >> interval;
		if (interval <= 0) interval = 1000;
	}
	else flag2 = 0;
}

bool userSaysYes(DoubleBuffer &d) {
	cout << "是否继续下一代？(Y/N)" << endl;
	char choice;
	cin >> choice;
	if (choice == 'Y' || choice - 'a' + 'A' == 'Y') return true;
	return false;
}

int main() {
	
	//===============随机数种子==============
	srand((unsigned)time(NULL));
	//======================================

	int n, m, flag1, flag2; // flag1: 随机初始化， flag2: 自动播放
	int interval = 1000;
	instructions(n, m, flag1, flag2, interval);
	Life configuration(n, m);
	configuration.initialize(flag1);
	system("cls");
	// ========
	DoubleBuffer db;
	// ========
	configuration.print();
	
	if (flag2) {
		while (true) {
			configuration.update();
			Sleep(interval);
			//db.clear();
			configuration.print();
			db.show();
		}
		db.close();
	}
	else {
		db.close();
		while (userSaysYes(db)) {
			system("cls");
			configuration.update();
			configuration.print();
		}
	}

	return 0;
}