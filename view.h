#pragma once

#include <Windows.h>
#include "control.h"
#include "MyButton.h"

/*
��ģ�鸺�𴰿ڵĳ�ʼ���Լ��������ʾ
*/

extern ButtonBmp* g_playBtnBmp;


//-----------------------------------
//�ؼ��õ�ͼƬ·����λ�ã���С
//������ͣ��ť δ����ʱ������ʱ��δ����������Ϸ�ʱ������������Ϸ�ʱ����갴��ʱ
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


//��������
#define CLASS_NAME L"CMusicPlayer"

//���ڱ���
#define WINDOW_TITLE L"CMusicPlayer"

//��ʼ������
void initWin(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow);

//�������Ű�ť
void playButtonInit(HWND hParent, HINSTANCE hInstance);