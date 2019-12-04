#pragma once

#include <Windows.h>
#include <windowsx.h>

//类名
#define CLASS_MYBUTTON L"MYBUTTON"


#define MAX_TEXT_LEN 64


//注册类等操作
void buttonInit();

//控件的过程函数
LRESULT CALLBACK buttonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//窗口创建后，保存传递过来的参数
void buttonSaveParam(HWND hwnd, LPARAM lParam);

//绘制按钮
void buttonPaint(HWND hwnd);

//鼠标悬停在按钮上绘制的动画
void buttonOnMouseHover(HWND hwnd);

//鼠标离开按钮后要把按钮样子恢复
void buttonOnMouseLeave(HWND hwnd);

//鼠标点击的动画
void buttonOnClick(HWND hwnd);