#include <iostream>
#include <windows.h>
using namespace std;

class DoubleBuffer{
private:
    HANDLE l_buffer1;
    HANDLE l_buffer2;
    HANDLE l_stdBuffer;
    TCHAR *_data = NULL;
    int nowActive;

    void bufferSwitch();

public:
    DoubleBuffer();
    void show();
    void inputMode();
    void reset();
    void close();
    void clear();
};