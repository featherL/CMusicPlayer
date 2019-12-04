#include "view.h"
#include "control.h"
#include "MyButton.h"

//��ʼ������
void initWin(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow)
{
	buttonInit();  //ע���Զ���İ�ť��


	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = windowProc;  //���ڹ��̺���
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;  //��������

	RegisterClass(&wc);

	HWND hWin = CreateWindowEx(
		0,                    // Optional window styles.
		CLASS_NAME,           // Window class
		WINDOW_TITLE,         // Window text
		WS_OVERLAPPEDWINDOW,  // Window style
		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,       // Parent window
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if(hWin == NULL)
		exit(0);


	//����һ����ť
	HWND hButton = CreateWindow(
		CLASS_MYBUTTON,
		L"|<", 
		WS_CHILD | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		20,
		20,
		hWin,
		NULL,
		(HINSTANCE)GetWindowLong(hWin, GWLP_HINSTANCE),
		NULL);



	ShowWindow(hWin, nCmdShow);  //��ʾ����
}