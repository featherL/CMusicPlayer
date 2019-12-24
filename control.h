#pragma once

//win32api
#include <Windows.h>

//view模块
#include "view.h"

//自定义的按钮控件
#include "MyButton.h"

//标准库，要使用malloc函数
#include <stdlib.h>

//管理音乐的播放
#include "MusicControl.h"

/*
该模块负责代码逻辑
*/

//最大可绑定回调函数的事件数
#define MAX_LEN_FOR_HANDLER 64

//主窗口过程函数
	//hwnd 窗口句柄
	//message 用来传入消息
	//wParam 保存附加信息
	//lParam 保存附加信息
	//操作系统要求一个返回值
LRESULT CALLBACK windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam); 

//事件消息处理循环
void eventLoop(); 

//添加歌曲到歌曲列表显示，该函数作为回调函数传入traverseAllMusic
	//node 歌曲节点
	//返回值，给traverseAllMusic函数用
int addSongToList(MusicNode* node);
//--------------------------
//控件事件函数的绑定相关
//回调函数的类型
	//hwnd 句柄
	//code 通知码
	//该函数返回值作为主窗口过程函数的返回值返回
typedef LRESULT(*CallBackFunc)(HWND hwnd, int code);

typedef struct Handler  //存储控件句柄与其回调函数
{
	HWND hwnd;  //控件的句柄
	CallBackFunc func;  //回调函数
} Handler;

//根据控件句柄，获取回调函
	//hwnd 控件的句柄
	//返回值为回调函数指针，若没有返回NULL
CallBackFunc getCallBackFunc(HWND hwnd); 

//给控件绑定回调函数
	//hwnd 控件的句柄
	//func 回调函数指针
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
	//该函数返回值作为主窗口过程函数的返回值返回
LRESULT winOnNcHitTest(HWND hWin, LPARAM lParam);


//命令事件，处理控件发来的消息
	//hWin 主窗口的句柄
	//message 主窗口过程函数中的message参数
	//wParam 主窗口过程函数中的wParam参数
	//lParam 主窗口过程函数中的lParam参数
	//该函数返回值作为主窗口过程函数的返回值返回
LRESULT winOnCommand(HWND hWin, UINT message, WPARAM wParam, LPARAM lParam);

//窗口创建事件,获取设备句柄等操作
	//hWin 主窗口的句柄
void winOnCreate(HWND hWin);

//WM_NOTIFY事件处理,这里处理列表的事件
	//hWin 主窗口句的柄
	//message 主窗口过程函数中的message参数
	//wParam 主窗口过程函数中的wParam参数
	//lParam 主窗口过程函数中的lParam参数
void winOnNotify(HWND hWin, UINT message, WPARAM wParam, LPARAM lParam);

//---------------------
//控件的处理函数

//退出按钮的事件处理函数
	//hwnd 按钮的句柄
	//code 通知码
LRESULT quitBtnHandler(HWND hwnd, int code);

//播放按钮的事件处理函数
	//hwnd 按钮的句柄
	//code 通知码 
LRESULT playBtnHandler(HWND hwnd, int code);

//模式按钮的事件处理函数
	//hwnd 按钮的句柄
	//code 通知码 
LRESULT modeBtnHandler(HWND hwnd, int code);

//切换下一首按钮的事件处理函数
	//hwnd 按钮的句柄
	//code 通知码 
LRESULT nextBtnHandler(HWND hwnd, int code);

//切换上一首按钮的事件处理函数
	//hwnd 按钮的句柄
	//code 通知码 
LRESULT prevBtnHandler(HWND hwnd, int code);
//------------------------

//没有消息时的逻辑，循环获取音乐的进度，更新进度条，及时播放下一首
void progressWhenNoMessage();