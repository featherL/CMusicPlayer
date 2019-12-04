#include "view.h"
#include "control.h"
#include "MyButton.h"

//初始化窗口
void initWin(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow)
{
	buttonInit();  //注册自定义的按钮类


	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = windowProc;  //窗口过程函数
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;  //窗口类名

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


	//创建一个按钮
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



	ShowWindow(hWin, nCmdShow);  //显示窗口
}