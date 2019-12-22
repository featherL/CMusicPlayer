#pragma once

#include <Windows.h>
#include <windowsx.h>




//类名
#define CLASS_MY_BUTTON L"MY_BUTTON"


#define MAX_TEXT_LEN 64

//---------------------
//按钮各种状态所需的图片

//静止，鼠标悬停，鼠标按下，鼠标抬起
#define BMP_STATIC 0
#define BMP_MOUSE_HOVER 1
#define BMP_MOUSE_DOWN 2


typedef struct ButtonBmp
{  //按钮所需的图片
	HBITMAP bmps[3];
}ButtonBmp;

//--------------------------


typedef struct ButtonData
{  //存储控件的所有数据
	HDC controlHdc;  //控件客户区域的设备上下文句柄
	HDC compatibleHdc;  //兼容于客户区域的设备上下文句柄
	ButtonBmp* buttonBmp;  //按钮绘制所需的图片资源
	HWND hParent;  //父窗口句柄
	RECT clientRect;  //客户区矩形区域
	int isMouseTracked;  //鼠标移动等事件是否激活
}ButtonData;

//-------------

//注册类等操作
void buttonInit();

//获取控件的ButtonData结构体的指针
	//hwnd按钮句柄
ButtonData* getButtonData(HWND hwnd);

//控件的过程函数
	//hwnd 按钮句柄
	//message 用来传入消息
	//wParam 保存附加信息
	//lParam 保存附加信息
LRESULT CALLBACK buttonProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


//窗口创建后，保存传递过来的参数等等
	//hwnd 按钮句柄
	//lParam 保存附加信息
void buttonOnCreate(HWND hwnd, LPARAM lParam);

//窗口销毁时，做一些资源释放的操作
	//hwnd 按钮句柄
	//btnData 指向储存按钮控件所有数据的结构体的指针
void buttonOnDestroy(HWND hwnd, ButtonData* btnData);

//绘制按钮
	//hwnd 按钮句柄
	//btnData 指向储存按钮控件所有数据的结构体的指针
void buttonPaint(HWND hwnd, ButtonData* btnData);

//鼠标悬停在按钮上绘制的动画
	//hwnd 按钮句柄
	//btnData 指向储存按钮控件所有数据的结构体的指针
void buttonOnMouseHover(HWND hwnd, ButtonData* btnData);

//鼠标按下动画
	//hwnd 按钮句柄
	//btnData 指向储存按钮控件所有数据的结构体的指针
void buttonOnMouseDown(HWND hwnd, ButtonData* btnData);

//鼠标松开动画
	//hwnd 按钮句柄
	//btnData 指向储存按钮控件所有数据的结构体的指针
void buttonOnMouseUp(HWND hwnd, ButtonData* btnData);

//鼠标离开按钮后要把按钮样子恢复
	//hwnd 按钮句柄
	//btnData 指向储存按钮控件所有数据的结构体的指针
void buttonOnMouseLeave(HWND hwnd, ButtonData* btnData);


