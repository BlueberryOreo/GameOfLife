#include "utility.h"
#include "Life.h"

void instructions(int &n, int &m, int &flag1, int &flag2) {
	cout << "请输入行数：" << endl;
	cin >> n;
	cout << "请输入列数：" << endl;
	cin >> m;
	cout << "是否随机初始化？(Y/N)" << endl;
	char choice;
	cin >> choice;
	if (choice == 'Y' || choice - 'a' + 'A' == 'Y') flag1 = 1;
	else flag1 = 0;
	cout << "是否自动播放？(Y/N)[播放后按Ctrl+C退出]" << endl;
	cin >> choice;
	if (choice == 'Y' || choice - 'a' + 'A' == 'Y') flag2 = 1;
	else flag2 = 0;
}

bool userSaysYes() {
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

	// ========
	DoubleBuffer db;
	db.inputMode();
	// ========

	int n, m, flag1, flag2; // flag1: 随机初始化， flag2: 自动播放
	instructions(n, m, flag1, flag2);
	Life configuration(n, m);
	configuration.initialize(flag1);
	system("cls");
	configuration.print();

	// ===========
	// ===========
	
	//while (userSaysYes()) {
	if (flag2) {
		db.reset();
		while (true) {
			configuration.update();
			Sleep(50);
			//db.clear();
			configuration.print();
			db.show();
		}
	}
	else {
		db.close();
		while (userSaysYes()) {
			system("cls");
			configuration.update();
			configuration.print();
		}
	}

	return 0;
}