#pragma once

#include <Windows.h>
#include <windowsx.h>




//����
#define CLASS_MYBUTTON L"MYBUTTON"


#define MAX_TEXT_LEN 64


//---------------------
//��ť����״̬�����ͼƬ

//��ֹ�������ͣ����갴�£����̧��
#define BMP_STATIC 0
#define BMP_MOUSE_HOVER 1
#define BMP_MOUSE_DOWN 2


typedef struct ButtonBmp
{  //��ť�����ͼƬ
	HBITMAP bmps[3];
}ButtonBmp;

//--------------------------

//ע����Ȳ���
void buttonInit();

//�ؼ��Ĺ��̺���
LRESULT CALLBACK buttonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//���ڴ����󣬱��洫�ݹ����Ĳ����ȵ�
void buttonOnCreate(HWND hwnd, LPARAM lParam);

//���ư�ť
void buttonPaint(HWND hwnd);

//�����ͣ�ڰ�ť�ϻ��ƵĶ���
void buttonOnMouseHover(HWND hwnd);

//��갴�¶���
void buttonOnMouseDown(HWND hwnd);

//����ɿ�����
void buttonOnMouseUp(HWND hwnd);

//����뿪��ť��Ҫ�Ѱ�ť���ӻָ�
void buttonOnMouseLeave(HWND hwnd);

