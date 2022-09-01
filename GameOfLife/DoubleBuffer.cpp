#include "DoubleBuffer.h"

//private
void DoubleBuffer::bufferSwitch(){
    nowActive = nowActive == 1 ? 2 : 1;
}

//public
DoubleBuffer::DoubleBuffer(){
    //width *= 3;
    //height *= 3;
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 1;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    l_stdBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
    //setConsoleWindowSize(width, height);

    l_buffer1 = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, 
		CONSOLE_TEXTMODE_BUFFER, NULL);
    l_buffer2 = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, 
		CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(l_buffer1);
    GetConsoleScreenBufferInfo(l_stdBuffer, &consoleInfo); // 获取控制台行列等属性
    //cout << consoleInfo.dwSize.X << endl;
    //exit(0);
    _data = new TCHAR[consoleInfo.dwSize.X * consoleInfo.dwSize.Y]; // 分配_data缓冲区
    nowActive = 1;

    // 关闭光标
    SetConsoleCursorInfo(l_stdBuffer, &info);
    SetConsoleCursorInfo(l_buffer1, &info);
    SetConsoleCursorInfo(l_buffer2, &info);
}

void DoubleBuffer::show(){
    static COORD coord = {0, 0};
    static DWORD b;
    //cout << nowActive << endl;
    ReadConsoleOutputCharacter(l_stdBuffer, _data, 10000, coord, &b);
    if(nowActive == 1){
        WriteConsoleOutputCharacter(l_buffer2, _data, wcslen(_data), coord, &b);
        SetConsoleActiveScreenBuffer(l_buffer2);
    }else{
        WriteConsoleOutputCharacter(l_buffer1, _data, wcslen(_data), coord, &b);
        SetConsoleActiveScreenBuffer(l_buffer1);
    }
    clear();
    bufferSwitch();
}

void DoubleBuffer::clear()
{
    static COORD coord = { 0, 0 };
    static DWORD b;
    FillConsoleOutputCharacter(l_stdBuffer, ' ', 10000, coord, &b);
    SetConsoleCursorPosition(l_stdBuffer, coord);
}

void DoubleBuffer::inputMode()
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;
	info.bVisible = true;
	SetConsoleActiveScreenBuffer(l_stdBuffer);
	SetConsoleCursorInfo(l_stdBuffer, &info);
	system("cls");
}

void DoubleBuffer::reset()
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;
	info.bVisible = false;
	SetConsoleActiveScreenBuffer(l_buffer1);
    nowActive = 1; 
	SetConsoleCursorInfo(l_stdBuffer, &info);
}

void DoubleBuffer::close()
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = true;
    SetConsoleActiveScreenBuffer(l_stdBuffer);
    SetConsoleCursorInfo(l_stdBuffer, &info);
	CloseHandle(l_buffer1);
    CloseHandle(l_buffer2);
	delete[] _data;
}

void DoubleBuffer::setConsoleWindowSize(int width, int height) {
    SMALL_RECT wrt = {0, 0, width - 1, height - 1};
    SetConsoleWindowInfo(l_stdBuffer, TRUE, &wrt);
    COORD coord = {width, height};
    SetConsoleScreenBufferSize(l_stdBuffer, coord);
}