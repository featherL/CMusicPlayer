#pragma once

#include <Windows.h>
#include "control.h"
#include "MyButton.h"

//windows提供控件的库
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

/*
该模块负责窗口的初始化以及画面的显示
*/

extern ButtonBmp* g_playBtnBmp;
extern ButtonBmp* g_playBtnBmp2;
extern ButtonBmp* g_nextBtnBmp;
extern ButtonBmp* g_prevBtnBmp;
extern ButtonBmp* g_xBtnBmp;
extern ButtonBmp* g_modeBtnBmp;


//----------------
//主窗口的大小
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

//用于拖动窗口的顶部区域的高度
#define MOVE_WINDOW_HEIGHT 64


//-----------------------------------
//控件用的图片路径，位置，大小

//播放暂停按钮 未播放时，播放时，未播放鼠标在上方时，播放鼠标在上方时，鼠标按下时
#define BMP_PAUSE_STATIC_PLAY_BUTTON L"images\\playButton\\1-1.bmp"
#define BMP_PLAY_STATIC_PLAY_BUTTON L"images\\playButton\\1-2.bmp" 
#define BMP_PAUSE_HOVER_PLAY_BUTTON L"images\\playButton\\2-1.bmp"
#define BMP_PLAY_HOVER_PLAY_BUTTON L"images\\playButton\\2-2.bmp"
#define BMP_MOUSE_DOWN_PLAY_BUTTON L"images\\playButton\\3.bmp" 
#define POS_X_PLAY_BUTTON 180
#define POS_Y_PLAY_BUTTON 520
#define WIDTH_PLAY_BUTTON 64
#define HEIGHT_PLAY_BUTTON 64

//下一首按钮
#define BMP_STATIC_NEXT_BUTTON L"images\\nextButton\\1.bmp"
#define BMP_HOVER_NEXT_BUTTON L"images\\nextButton\\2.bmp"
#define BMP_DOWN_NEXT_BUTTON L"images\\nextButton\\3.bmp"
#define POS_X_NEXT_BUTTON 260
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

//退出按钮
#define BMP_STATIC_X_BUTTON L"images\\xButton\\1.bmp"
#define BMP_HOVER_X_BUTTON L"images\\xButton\\2.bmp"
#define BMP_DOWN_X_BUTTON L"images\\xButton\\3.bmp"
#define WIDTH_X_BUTTON 40
#define HEIGHT_X_BUTTON 40
#define POS_X_X_BUTTON (WINDOW_WIDTH-WIDTH_X_BUTTON)
#define POS_Y_X_BUTTON 0

//模式按钮
#define BMP_STATIC_MODE_BUTTON L"images\\modeButton\\1-1.bmp"
#define BMP_HOVER_MODE_BUTTON L"images\\modeButton\\1-2.bmp"
#define BMP_DOWN_MODE_BUTTON L"images\\modeButton\\1-3.bmp"
#define POS_X_MODE_BUTTON 20
#define POS_Y_MODE_BUTTON 520
#define WIDTH_MODE_BUTTON 64
#define HEIGHT_MODE_BUTTON 64

//歌曲列表
#define POS_X_SONG_LIST 20
#define POS_Y_SONG_LIST 32
#define WIDTH_SONG_LIST 800
#define HEIGHT_SONG_LIST 480

//歌曲列表的表头的文字（只有一列）
#define TEXT_OF_LIST_COLUMN L"歌曲名"


//--------------------------


//窗口类名
#define CLASS_NAME L"CMusicPlayer"

//窗口标题
#define WINDOW_TITLE L"CMusicPlayer"

//初始化窗口
	//hInstance 程序句柄
void initWin(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow);

//创建播放按钮
	//hParent 父窗口句柄
	//hInstance 程序句柄
void playButtonInit(HWND hParent, HINSTANCE hInstance);

//创建next按钮
	//hParent 父窗口句柄
	//hInstance 程序句柄
void nextButtonInit(HWND hParent, HINSTANCE hInstance);

//创建prev按钮
	//hParent 父窗口句柄
	//hInstance 程序句柄
void prevButtonInit(HWND hParent, HINSTANCE hInstance);

//创建x按钮
	//hParent 父窗口句柄
	//hInstance 程序句柄
void xButtonInit(HWND hParent, HINSTANCE hInstance);

//创建模式按钮
	//hParent 父窗口句柄
	//hInstance 程序句柄
void modeButtonInit(HWND hParent, HINSTANCE hInstance);

//创建歌曲列表
	//hParent 父窗口句柄
	//hInstance 程序句柄
void songListInit(HWND hParent, HINSTANCE hInstance);

