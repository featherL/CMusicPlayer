#pragma once

#include <Windows.h>
#include "control.h"
#include "MyButton.h"

/*
该模块负责窗口的初始化以及画面的显示
*/

extern ButtonBmp* g_playBtnBmp;


//-----------------------------------
//控件用的图片路径，位置，大小
//播放暂停按钮 未播放时，播放时，未播放鼠标在上方时，播放鼠标在上方时，鼠标按下时
#define BMP_PAUSE_STATIC_PLAY_BUTTON L"images\\playButton\\1-1.bmp" 
#define BMP_PLAY_STATIC_PLAY_BUTTON L"images\\playButton\\1-2.bmp" 
#define BMP_PAUSE_HOVER_PLAY_BUTTON L"images\\playButton\\2-1.bmp"
#define BMP_PLAY_HOVER_PLAY_BUTTON L"images\\playButton\\2-2.bmp"
#define BMP_MOUSE_DOWN_PLAY_BUTTON L"images\\playButton\\3.bmp" 
#define POS_X_PLAY_BUTTON 0
#define POS_Y_PLAY_BUTTON 0
#define WIDTH_PLAY_BUTTON 64
#define HEIGHT_PLAY_BUTTON 64


//--------------------------


//窗口类名
#define CLASS_NAME L"CMusicPlayer"

//窗口标题
#define WINDOW_TITLE L"CMusicPlayer"

//初始化窗口
void initWin(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow);

//创建播放按钮
void playButtonInit(HWND hParent, HINSTANCE hInstance);