#pragma once

#include <Windows.h>

/*
该模块负责窗口的初始化以及画面的显示
*/

//窗口类名
#define CLASS_NAME L"CMusicPlayer"

//窗口标题
#define WINDOW_TITLE L"CMusicPlayer"

//初始化窗口
void initWin(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow);
