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


typedef struct ButtonData
{  //�洢�ؼ�����������
	HDC controlHdc;  //�ؼ��ͻ�������豸�����ľ��
	HDC compatibleHdc;  //�����ڿͻ�������豸�����ľ��
	ButtonBmp* buttonBmp;  //��ť���������ͼƬ��Դ
	HWND hParent;  //�����ھ��
	RECT clientRect;  //�ͻ�����������
	int isMouseTracked;  //����ƶ����¼��Ƿ񼤻�
}ButtonData;

//-------------

//ע����Ȳ���
void buttonInit();

//��ȡ�ؼ���ButtonData�ṹ���ָ��
ButtonData* getButtonData(HWND hwnd);

//�ؼ��Ĺ��̺���
LRESULT CALLBACK buttonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//���ڴ����󣬱��洫�ݹ����Ĳ����ȵ�
void buttonOnCreate(HWND hwnd, LPARAM lParam);

//��������ʱ����һЩ��Դ�ͷŵĲ���
void buttonOnDestroy(HWND hwnd);

//���ư�ť
void buttonPaint(HWND hwnd, ButtonData* btnData);

//�����ͣ�ڰ�ť�ϻ��ƵĶ���
void buttonOnMouseHover(HWND hwnd, ButtonData* btnData);

//��갴�¶���
void buttonOnMouseDown(HWND hwnd, ButtonData* btnData);

//����ɿ�����
void buttonOnMouseUp(HWND hwnd, ButtonData* btnData);

//����뿪��ť��Ҫ�Ѱ�ť���ӻָ�
void buttonOnMouseLeave(HWND hwnd, ButtonData* btnData);


