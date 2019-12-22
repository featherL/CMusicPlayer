#pragma once

#include <Windows.h>
#include <windowsx.h>




//����
#define CLASS_MY_BUTTON L"MY_BUTTON"


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
	//hwnd��ť���
ButtonData* getButtonData(HWND hwnd);

//�ؼ��Ĺ��̺���
	//hwnd ��ť���
	//message ����������Ϣ
	//wParam ���渽����Ϣ
	//lParam ���渽����Ϣ
LRESULT CALLBACK buttonProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


//���ڴ����󣬱��洫�ݹ����Ĳ����ȵ�
	//hwnd ��ť���
	//lParam ���渽����Ϣ
void buttonOnCreate(HWND hwnd, LPARAM lParam);

//��������ʱ����һЩ��Դ�ͷŵĲ���
	//hwnd ��ť���
	//btnData ָ�򴢴水ť�ؼ��������ݵĽṹ���ָ��
void buttonOnDestroy(HWND hwnd, ButtonData* btnData);

//���ư�ť
	//hwnd ��ť���
	//btnData ָ�򴢴水ť�ؼ��������ݵĽṹ���ָ��
void buttonPaint(HWND hwnd, ButtonData* btnData);

//�����ͣ�ڰ�ť�ϻ��ƵĶ���
	//hwnd ��ť���
	//btnData ָ�򴢴水ť�ؼ��������ݵĽṹ���ָ��
void buttonOnMouseHover(HWND hwnd, ButtonData* btnData);

//��갴�¶���
	//hwnd ��ť���
	//btnData ָ�򴢴水ť�ؼ��������ݵĽṹ���ָ��
void buttonOnMouseDown(HWND hwnd, ButtonData* btnData);

//����ɿ�����
	//hwnd ��ť���
	//btnData ָ�򴢴水ť�ؼ��������ݵĽṹ���ָ��
void buttonOnMouseUp(HWND hwnd, ButtonData* btnData);

//����뿪��ť��Ҫ�Ѱ�ť���ӻָ�
	//hwnd ��ť���
	//btnData ָ�򴢴水ť�ؼ��������ݵĽṹ���ָ��
void buttonOnMouseLeave(HWND hwnd, ButtonData* btnData);


