#pragma once

#include <Windows.h>
#include "control.h"
#include "MyButton.h"
#include "MusicControl.h"

//windows提供控件的库
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

/*
该模块负责窗口的初始化以及画面的显示
*/

//各种位图资源
extern ButtonBmp * g_playBtnBmpCur;		//播放按钮的当前使用的一套图片
extern ButtonBmp* g_playBtnBmp1;		//播放按钮的没有播放时的一套图片
extern ButtonBmp* g_playBtnBmp2;		//播放按钮播放时的一套图片
extern ButtonBmp* g_nextBtnBmp;			//下一首按钮的相关图片
extern ButtonBmp* g_prevBtnBmp;			//上一首按钮的相关图片
extern ButtonBmp* g_xBtnBmp;			//退出按钮的相关图片
extern ButtonBmp* g_modeBtnBmpCur;		//模式按钮的当前使用的一套相关图片
extern ButtonBmp* g_modeBtnBmp1;		//模式按钮顺序播放使用的相关图片
extern ButtonBmp* g_modeBtnBmp2;		//模式按钮循环播放使用的相关图片
extern ButtonBmp* g_modeBtnBmp3;		//模式按钮随机播放使用的相关图片

extern HDC g_hdcOfMainWin;			//主窗口的设备句柄
extern HDC g_hBuffOfMainWin;		//用来缓冲的设备环境
extern HBITMAP g_hBitmap;			//用来贴图的内存区域
extern HWND g_hWin;					//主窗口句柄


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
#define BMP_STATIC_MODE_1_BUTTON L"images\\modeButton\\1-1.bmp"
#define BMP_HOVER_MODE_1_BUTTON L"images\\modeButton\\1-2.bmp"
#define BMP_DOWN_MODE_1_BUTTON L"images\\modeButton\\1-3.bmp"
#define BMP_STATIC_MODE_2_BUTTON L"images\\modeButton\\2-1.bmp"
#define BMP_HOVER_MODE_2_BUTTON L"images\\modeButton\\2-2.bmp"
#define BMP_DOWN_MODE_2_BUTTON L"images\\modeButton\\2-3.bmp"
#define BMP_STATIC_MODE_3_BUTTON L"images\\modeButton\\3-1.bmp"
#define BMP_HOVER_MODE_3_BUTTON L"images\\modeButton\\3-2.bmp"
#define BMP_DOWN_MODE_3_BUTTON L"images\\modeButton\\3-3.bmp"
#define POS_X_MODE_BUTTON 20
#define POS_Y_MODE_BUTTON 520
#define WIDTH_MODE_BUTTON 64
#define HEIGHT_MODE_BUTTON 64

//歌曲列表
#define POS_X_SONG_LIST 20
#define POS_Y_SONG_LIST 64
#define WIDTH_SONG_LIST 950
#define HEIGHT_SONG_LIST 400

//歌曲列表的表头的文字（只有一列）
#define TEXT_OF_LIST_COLUMN L"歌曲名"

//进度条（画成一个矩形）
#define WIDTH_PROGRESS_BAR 950
#define HEIGHT_PROGRESS_BAR 10
#define POS_X_PROGRESS_BAR 20
#define POS_Y_PROGRESS_BAR 480

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

//绘制进度条
	//persent 进度条的百分比  persent为98则表示98%
void drawProgressBar(double persent);


//切换播放按钮的图片
	//hwnd 按钮句柄
	//status 按钮的状态
void switchPlayBtnBmp(HWND hwnd, int status);

//切换模式按钮的图片
	//hwnd 按钮句柄
	//status 按钮的状态
void switchModeBtnBmp(HWND hwnd, int status);

