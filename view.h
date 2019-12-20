#pragma once

#include <Windows.h>
#include "control.h"
#include "MyButton.h"

/*
��ģ�鸺�𴰿ڵĳ�ʼ���Լ��������ʾ
*/

extern ButtonBmp* g_playBtnBmp;
extern ButtonBmp* g_nextBtnBmp;
extern ButtonBmp* g_prevBtnBmp;


//----------------
//�����ڵĴ�С
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


//-----------------------------------
//�ؼ��õ�ͼƬ·����λ�ã���С
//������ͣ��ť δ����ʱ������ʱ��δ����������Ϸ�ʱ������������Ϸ�ʱ����갴��ʱ
#define BMP_PAUSE_STATIC_PLAY_BUTTON L"images\\playButton\\1-1.bmp" 
#define BMP_PLAY_STATIC_PLAY_BUTTON L"images\\playButton\\1-2.bmp" 
#define BMP_PAUSE_HOVER_PLAY_BUTTON L"images\\playButton\\2-1.bmp"
#define BMP_PLAY_HOVER_PLAY_BUTTON L"images\\playButton\\2-2.bmp"
#define BMP_MOUSE_DOWN_PLAY_BUTTON L"images\\playButton\\3.bmp" 
#define POS_X_PLAY_BUTTON 200
#define POS_Y_PLAY_BUTTON 520
#define WIDTH_PLAY_BUTTON 64
#define HEIGHT_PLAY_BUTTON 64

//��һ�װ�ť
#define BMP_STATIC_NEXT_BUTTON L"images\\nextButton\\1.bmp"
#define BMP_HOVER_NEXT_BUTTON L"images\\nextButton\\2.bmp"
#define BMP_DOWN_NEXT_BUTTON L"images\\nextButton\\3.bmp"
#define POS_X_NEXT_BUTTON 300
#define POS_Y_NEXT_BUTTON 520
#define WIDTH_NEXT_BUTTON 64
#define HEIGHT_NEXT_BUTTON 64

//��һ�װ�ť
#define BMP_STATIC_PREV_BUTTON L"images\\prevButton\\1.bmp"
#define BMP_HOVER_PREV_BUTTON L"images\\prevButton\\2.bmp"
#define BMP_DOWN_PREV_BUTTON L"images\\prevButton\\3.bmp"
#define POS_X_PREV_BUTTON 100
#define POS_Y_PREV_BUTTON 520
#define WIDTH_PREV_BUTTON 64
#define HEIGHT_PREV_BUTTON 64
//--------------------------


//��������
#define CLASS_NAME L"CMusicPlayer"

//���ڱ���
#define WINDOW_TITLE L"CMusicPlayer"

//��ʼ������
void initWin(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow);

//�������Ű�ť
void playButtonInit(HWND hParent, HINSTANCE hInstance);

//����next��ť
void nextButtonInit(HWND hParent, HINSTANCE hInstance);

//����prev��ť
void prevButtonInit(HWND hParent, HINSTANCE hInstance);