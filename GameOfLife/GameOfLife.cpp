#include "utility.h"
#include "Life.h"

void instructions(int &n, int &m, int &flag1, int &flag2, int &interval) {
	cout << "□■□\n■□■\n■■□" << endl;
	cout << "欢迎来到生命游戏。" << endl;
	cout << "这是一个无人操作的游戏，在输入了场地的大小之后，你只需要像小的时候观察蚂蚁那样看它运行就可以了。" << endl;
	cout << "生命游戏的规则是：\n" << 
		"1、我们称一个格子为一个细胞；\n" << 
		"2、细胞害怕孤独，当一个细胞的周围8个格子中存活的细胞数量小于或等于1个，那么这个细胞在下一代会死亡；\n" <<
		"3、细胞也不喜欢拥挤，当一个细胞的周围8个格子中存活的细胞数量大于或等于4个，那么这个细胞在下一代会死亡；\n" << 
		"4、当一个细胞的周围8个格子中存活的细胞数量为2个或3个的时候，这个细胞在下一代才能继续存活；\n" <<
		"5、细胞可以重生。当一个死亡的细胞的周围8个格子中恰好有3个存活的细胞，那么这个细胞在下一代可以复活。" << endl;
	cout << endl;
	cout << "你需要做的是：\n" << 
		"1、输入一定的行数和列数（行数不超过51，列数不超过88）；\n" << 
		"2、决定是否需要自动随机初始化还是手动输入；\n" << 
		"3、决定是否需要自动播放还是手动控制\n" << 
		"4、观察它的变化。" << endl;
	cout << "请输入行数（最大51）：" << endl;
	cin >> n;
	if (n > 51) n = 51;
	if (n <= 0) n = 10;
	cout << "请输入列数（最大88）：" << endl;
	cin >> m;
	if (m > 88) m = 88;
	if (m <= 0) m = 10;
	cout << "是否随机初始化？(Y/N)" << endl;
	char choice;
	cin >> choice;
	if (choice == 'Y' || choice - 'a' + 'A' == 'Y') {
		flag1 = 1;
	}
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