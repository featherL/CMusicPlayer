#pragma once

#include <Windows.h>
#include <windowsx.h>

//����
#define CLASS_MYBUTTON L"MYBUTTON"


#define MAX_TEXT_LEN 64


//ע����Ȳ���
void buttonInit();

//�ؼ��Ĺ��̺���
LRESULT CALLBACK buttonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//���ڴ����󣬱��洫�ݹ����Ĳ���
void buttonSaveParam(HWND hwnd, LPARAM lParam);

//���ư�ť
void buttonPaint(HWND hwnd);

//�����ͣ�ڰ�ť�ϻ��ƵĶ���
void buttonOnMouseHover(HWND hwnd);

//����뿪��ť��Ҫ�Ѱ�ť���ӻָ�
void buttonOnMouseLeave(HWND hwnd);

//������Ķ���
void buttonOnClick(HWND hwnd);