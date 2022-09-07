#include <iostream>
#include <windows.h>
using namespace std;

// 双缓冲类
class DoubleBuffer{
private:
    HANDLE l_buffer1; // 缓冲区1
    HANDLE l_buffer2; // 缓冲区2
    HANDLE l_stdBuffer; // 原控制台缓冲区
    TCHAR *_data = NULL; // 输出的数据
    int nowActive; // 当前处于显示状态的缓冲区

    void bufferSwitch(); // 切换当前显示的缓冲区

public:
    DoubleBuffer(); // 初始化
    void show(); // 显示
    void inputMode(); // 输入模式
    void reset(); // 关闭输入模式
    void close(); // 关闭双缓冲
    void clear(); // 清除缓冲区
    void setConsoleWindowSize(int width, int height); // 设置控制台大小 Deprecated
    void maxScreen(); // Deprecated
};