#pragma once

#include <Windows.h>
#include "view.h"
#include "MyButton.h"
#include <stdlib.h>

/*
该模块负责代码逻辑
*/

//最大可绑定回调函数的事件数
#define MAX_LEN_FOR_HANDLER 64

//窗口过程函数
LRESULT CALLBACK windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam); 

//事件消息处理循环
void eventLoop();  

//--------------------------
//控件事件函数的绑定相关
//回调函数的类型
typedef LRESULT(*CallBackFunc)(HWND hwnd, int code);

typedef struct Handler  //存储控件句柄与其回调函数
{
	HWND hwnd;  //控件的句柄
	CallBackFunc func;  //回调函数
} Handler;

//根据控件句柄hwnd，获取回调函数，若没有返回NULL
CallBackFunc getCallBackFunc(HWND hwnd); 

//给控件hwnd绑定func回调函数
void bindCallBackFunc(HWND hwnd, CallBackFunc func); 

//---------------------
//主窗口过程函数各个事件的操作相关

//窗口销毁事件
void winOnDestroy();

//释放按钮的位图资源
	//btnBmp 存放了要释放的图片资源的结构体的指针
void releaseBmpResource(ButtonBmp* btnBmp);

//鼠标点击测试事件，当点击按住在顶部一定的区域，让窗口拖动
	//hWin 主窗口的句柄
	//lParam 主窗口过程函数中的lParam参数
LRESULT winOnNcHitTest(HWND hWin, LPARAM lParam);


//命令事件，处理控件发来的消息
	//hWin 主窗口的句柄
	//message 主窗口过程函数中的message参数
	//wParam 主窗口过程函数中的wParam参数
	//lParam 主窗口过程函数中的lParam参数
LRESULT winOnCommand(HWND hWin, UINT message, WPARAM wParam, LPARAM lParam);

//窗口创建事件,获取设备句柄等操作
	//hWin 主窗口的句柄
void winOnCreate(HWND hWin);

//---------------------
//控件的处理函数

//退出按钮的事件处理函数
LRESULT quitBtnHandler(HWND hwnd, int code);

//------------------------

//没有消息时的逻辑，循环获取音乐的进度，更新进度条，及时播放下一首
void progressWhenNoMessage();