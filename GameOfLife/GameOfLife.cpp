#include "utility.h"
#include "Life.h"

void instructions(int &n, int &m, int &flag) {
	cout << "请输入行数：" << endl;
	cin >> n;
	cout << "请输入列数：" << endl;
	cin >> m;
	cout << "是否随机初始化？(Y/N)" << endl;
	char choice;
	cin >> choice;
	if (choice == 'Y' || choice - 'a' + 'A' == 'Y') flag = 1;
	else flag = 0;
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

	int n, m, flag;
	instructions(n, m, flag);
	Life configuration(n, m);
	configuration.initialize(flag);
	configuration.print();
	while (userSaysYes()) {
		configuration.update();
		configuration.print();
	}

	return 0;
}