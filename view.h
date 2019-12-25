#pragma once

//win32api
#include <Windows.h>

//controlģ��
#include "control.h"

//�Զ���İ�ť�ؼ�
#include "MyButton.h"

//�������ֵĲ���
#include "MusicControl.h"

//��׼�⣬Ҫʹ��malloc����
#include <stdlib.h>

//windows�ṩ�ؼ��Ŀ⣬��Ҫʹ���б�ؼ�
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

/*
��ģ�鸺�𴰿ڵĳ�ʼ���Լ��������ʾ
*/

//����λͼ��Դ
extern ButtonBmp * g_playBtnBmpCur;		//���Ű�ť�ĵ�ǰʹ�õ�һ��ͼƬ
extern ButtonBmp* g_playBtnBmp1;		//���Ű�ť��û�в���ʱ��һ��ͼƬ
extern ButtonBmp* g_playBtnBmp2;		//���Ű�ť����ʱ��һ��ͼƬ
extern ButtonBmp* g_nextBtnBmp;			//��һ�װ�ť�����ͼƬ
extern ButtonBmp* g_prevBtnBmp;			//��һ�װ�ť�����ͼƬ
extern ButtonBmp* g_xBtnBmp;			//�˳���ť�����ͼƬ
extern ButtonBmp* g_modeBtnBmpCur;		//ģʽ��ť�ĵ�ǰʹ�õ�һ�����ͼƬ
extern ButtonBmp* g_modeBtnBmp1;		//ģʽ��ť˳�򲥷�ʹ�õ����ͼƬ
extern ButtonBmp* g_modeBtnBmp2;		//ģʽ��ťѭ������ʹ�õ����ͼƬ
extern ButtonBmp* g_modeBtnBmp3;		//ģʽ��ť�������ʹ�õ����ͼƬ

extern HDC g_hdcOfMainWin;			//�����ڵ��豸���
extern HDC g_hBuffOfMainWin;		//����������豸����
extern HBITMAP g_hBitmap;			//������ͼ���ڴ�����
extern HWND g_hWin;					//�����ھ��
extern HWND g_hPlayBtn;            //���Ű�ť�ľ��
extern HWND g_hSongList;			//�����б�ľ��


//----------------
//�����ڵĴ�С
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

//������ͼ��

//�����϶����ڵĶ�������ĸ߶�
#define MOVE_WINDOW_HEIGHT 64


//-----------------------------------
//�ؼ��õ�ͼƬ·����λ�ã���С

//������ͣ��ť δ����ʱ������ʱ��δ����������Ϸ�ʱ������������Ϸ�ʱ����갴��ʱ
#define BMP_PAUSE_STATIC_PLAY_BUTTON L"images\\playButton\\1-1.bmp"
#define BMP_PLAY_STATIC_PLAY_BUTTON L"images\\playButton\\1-2.bmp" 
#define BMP_PAUSE_HOVER_PLAY_BUTTON L"images\\playButton\\2-1.bmp"
#define BMP_PLAY_HOVER_PLAY_BUTTON L"images\\playButton\\2-2.bmp"
#define BMP_MOUSE_DOWN_PLAY_BUTTON L"images\\playButton\\3.bmp" 
#define POS_X_PLAY_BUTTON 180
#define POS_Y_PLAY_BUTTON 520
#define WIDTH_PLAY_BUTTON 64
#define HEIGHT_PLAY_BUTTON 64

//��һ�װ�ť
#define BMP_STATIC_NEXT_BUTTON L"images\\nextButton\\1.bmp"
#define BMP_HOVER_NEXT_BUTTON L"images\\nextButton\\2.bmp"
#define BMP_DOWN_NEXT_BUTTON L"images\\nextButton\\3.bmp"
#define POS_X_NEXT_BUTTON 260
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

//�˳���ť
#define BMP_STATIC_X_BUTTON L"images\\xButton\\1.bmp"
#define BMP_HOVER_X_BUTTON L"images\\xButton\\2.bmp"
#define BMP_DOWN_X_BUTTON L"images\\xButton\\3.bmp"
#define WIDTH_X_BUTTON 40
#define HEIGHT_X_BUTTON 40
#define POS_X_X_BUTTON (WINDOW_WIDTH-WIDTH_X_BUTTON)
#define POS_Y_X_BUTTON 0

//ģʽ��ť
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

//�����б�
#define POS_X_SONG_LIST 20
#define POS_Y_SONG_LIST 64
#define WIDTH_SONG_LIST 950
#define HEIGHT_SONG_LIST 400

//�����б�ı�ͷ������,�Լ���Ӧ���
#define TEXT_OF_LIST_COLUMN_1 L"������"
#define TEXT_OF_LIST_COLUMN_2 L"����id"
#define WIDTH_OF_LIST_COLUMN_1 600
#define WIDTH_OF_LIST_COLUMN_2 (WIDTH_SONG_LIST-WIDTH_OF_LIST_COLUMN_1)


//������������һ�����Σ�
#define WIDTH_PROGRESS_BAR 950
#define HEIGHT_PROGRESS_BAR 10
#define POS_X_PROGRESS_BAR 20
#define POS_Y_PROGRESS_BAR 480

//--------------------------


//��������
#define CLASS_NAME L"CMusicPlayer"

//���ڱ���
#define WINDOW_TITLE L"CMusicPlayer"

//��ʼ������
	//hInstance ������
	//pre		�ò���windows��ʹ��
	//pCmdLind	�����в���
	//nCmdShow	������ʾ�ķ�ʽ
void initWin(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow);

//�������Ű�ť
	//hParent �����ھ��
	//hInstance ������
void playButtonInit(HWND hParent, HINSTANCE hInstance);

//����next��ť
	//hParent �����ھ��
	//hInstance ������
void nextButtonInit(HWND hParent, HINSTANCE hInstance);

//����prev��ť
	//hParent �����ھ��
	//hInstance ������
void prevButtonInit(HWND hParent, HINSTANCE hInstance);

//�����˳���ť
	//hParent �����ھ��
	//hInstance ������
void xButtonInit(HWND hParent, HINSTANCE hInstance);

//����ģʽ��ť
	//hParent �����ھ��
	//hInstance ������
void modeButtonInit(HWND hParent, HINSTANCE hInstance);

//���������б�
	//hParent �����ھ��
	//hInstance ������
void songListInit(HWND hParent, HINSTANCE hInstance);

//���ƽ�����
	//persent �������İٷֱ�  persentΪ98���ʾ98%
void drawProgressBar(double persent);


//�л����Ű�ť��ͼƬ
	//hwnd ��ť���
	//status ��ť��״̬
void switchPlayBtnBmp(HWND hwnd, int status);

//�л�ģʽ��ť��ͼƬ
	//hwnd ��ť���
	//status ��ť��״̬
void switchModeBtnBmp(HWND hwnd, int status);

