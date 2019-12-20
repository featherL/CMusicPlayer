#pragma once

#include <Windows.h>
#include "control.h"
#include "MyButton.h"

/*
该模块负责窗口的初始化以及画面的显示
*/

extern ButtonBmp* g_playBtnBmp;
extern ButtonBmp* g_nextBtnBmp;
extern ButtonBmp* g_prevBtnBmp;


//----------------
//主窗口的大小
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


//-----------------------------------
//控件用的图片路径，位置，大小
//播放暂停按钮 未播放时，播放时，未播放鼠标在上方时，播放鼠标在上方时，鼠标按下时
#define BMP_PAUSE_STATIC_PLAY_BUTTON L"images\\playButton\\1-1.bmp" 
#define BMP_PLAY_STATIC_PLAY_BUTTON L"images\\playButton\\1-2.bmp" 
#define BMP_PAUSE_HOVER_PLAY_BUTTON L"images\\playButton\\2-1.bmp"
#define BMP_PLAY_HOVER_PLAY_BUTTON L"images\\playButton\\2-2.bmp"
#define BMP_MOUSE_DOWN_PLAY_BUTTON L"images\\playButton\\3.bmp" 
#define POS_X_PLAY_BUTTON 200
#define POS_Y_PLAY_BUTTON 520
#define WIDTH_PLAY_BUTTON 64
#define HEIGHT_PLAY_BUTTON 64

//下一首按钮
#define BMP_STATIC_NEXT_BUTTON L"images\\nextButton\\1.bmp"
#define BMP_HOVER_NEXT_BUTTON L"images\\nextButton\\2.bmp"
#define BMP_DOWN_NEXT_BUTTON L"images\\nextButton\\3.bmp"
#define POS_X_NEXT_BUTTON 300
#define POS_Y_NEXT_BUTTON 520
#define WIDTH_NEXT_BUTTON 64
#define HEIGHT_NEXT_BUTTON 64

//上一首按钮
#define BMP_STATIC_PREV_BUTTON L"images\\prevButton\\1.bmp"
#define BMP_HOVER_PREV_BUTTON L"images\\prevButton\\2.bmp"
#define BMP_DOWN_PREV_BUTTON L"images\\prevButton\\3.bmp"
#define POS_X_PREV_BUTTON 100
#define POS_Y_PREV_BUTTON 520
#define WIDTH_PREV_BUTTON 64
#define HEIGHT_PREV_BUTTON 64
//--------------------------


//窗口类名
#define CLASS_NAME L"CMusicPlayer"

//窗口标题
#define WINDOW_TITLE L"CMusicPlayer"

//初始化窗口
void initWin(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow);

//创建播放按钮
void playButtonInit(HWND hParent, HINSTANCE hInstance);

//创建next按钮
void nextButtonInit(HWND hParent, HINSTANCE hInstance);

//创建prev按钮
void prevButtonInit(HWND hParent, HINSTANCE hInstance);