#include "MyButton.h"


void buttonInit()
{
	//填充结构体
	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof(wc);  //结构体的大小
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);  //背景颜色
	wc.hCursor = LoadCursor(0, IDC_ARROW);  //默认的小箭头作为鼠标图标
	wc.hInstance = GetModuleHandle(0);  //GetModuleHandle获取程序的实例句柄
	wc.lpfnWndProc = buttonProc;  //过程函数
	wc.lpszClassName = CLASS_MY_BUTTON; //类名
	wc.style = CS_DBLCLKS;  //使窗口可以接受点击事件

	
	
	RegisterClassEx(&wc);  //注册窗口类
}

//获取控件的ButtonData结构体的指针
ButtonData* getButtonData(HWND hwnd)
{
	ButtonData* ret;

	ret = (ButtonData*)GetWindowLong(hwnd, GWL_USERDATA);

	return ret;
}

LRESULT CALLBACK buttonProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	TRACKMOUSEEVENT tme;
	ButtonData* btnData;

	if(message == WM_CREATE)
	{ //保存创建窗口传入的参数,存储一些必要的数据等操作
		buttonOnCreate(hwnd, lParam);
	}

	btnData = getButtonData(hwnd);  //获取存起来的数据

	switch(message)
	{
	case WM_MOUSEMOVE:
		if (!btnData->isMouseTracked)
		{ //开启鼠标悬停，移出事件
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = hwnd;
			tme.dwFlags = TME_LEAVE | TME_HOVER;  //鼠标悬停，移出事件
			tme.dwHoverTime = 1;  //悬停事件发生需要的时间(ms)
			TrackMouseEvent(&tme);

			btnData->isMouseTracked = 0;
		}
		break;
	case WM_PAINT:                    //绘制按钮
		buttonPaint(hwnd, btnData);
		break;
	case WM_MOUSEHOVER:               //鼠标悬停
		buttonOnMouseHover(hwnd, btnData);
		btnData->isMouseTracked = 0;
		break;
	case WM_MOUSELEAVE:               //鼠标离开
		buttonOnMouseLeave(hwnd, btnData);
		btnData->isMouseTracked = 0;
		break;
	case WM_LBUTTONDOWN:              //鼠标按下
		buttonOnMouseDown(hwnd, btnData);
		break;
	case WM_LBUTTONUP:                //鼠标抬起
		buttonOnMouseUp(hwnd, btnData);
		//模仿win32自带的按钮控件发送点击消息到父窗口
		SendMessage(btnData->hParent, WM_COMMAND, MAKEWPARAM(0, BN_CLICKED), (LPARAM)hwnd);
		break;
	case WM_DESTROY:
		buttonOnDestroy(hwnd, btnData);  //释放分配的资源
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

//窗口创建后，保存传递过来的参数等等
void buttonOnCreate(HWND hwnd, LPARAM lParam)
{
	ButtonData* btnData = (ButtonData*)malloc(sizeof(ButtonData));  //分配空间存数据

	btnData->hParent = GetParent(hwnd);   //父窗口句柄
	
	btnData->isMouseTracked = 0;  //是否激活鼠标事件

	GetClientRect(hwnd, &btnData->clientRect);  //客户区矩形区域
	
	btnData->controlHdc = GetDC(hwnd);  //设备环境上下文句柄

	btnData->compatibleHdc = CreateCompatibleDC(btnData->controlHdc);  //兼容的设备上下文句柄

	btnData->buttonBmp = ((LPCREATESTRUCT)lParam)->lpCreateParams;  //图片资源通过CreateWindow的最后一个参数传来过来
	
	//保存btnData指针
	SetWindowLong(hwnd, GWL_USERDATA, (LONG)btnData);
}

//窗口销毁时，做一些资源释放的操作
void buttonOnDestroy(HWND hwnd, ButtonData* btnData)
{
	//释放设备上下文
	DeleteDC(btnData->compatibleHdc); 
	ReleaseDC(hwnd, btnData->controlHdc);  

	//btnData->buttonBmp这个指针是创建窗口传入的，应该由外面释放

	free(btnData);  //释放这个结构体的资源
}

//绘制按钮
void buttonPaint(HWND hwnd, ButtonData* btnData)
{
	PAINTSTRUCT ps;
	BeginPaint(hwnd, &ps);  //开始绘制
	
	SelectObject(btnData->compatibleHdc, btnData->buttonBmp->bmps[BMP_STATIC]);  //选中位图对象

	int width = btnData->clientRect.right - btnData->clientRect.left;  //窗口宽度
	int height = btnData->clientRect.bottom - btnData->clientRect.top;  //窗口高度

	BitBlt(btnData->controlHdc, 0, 0, width, height, btnData->compatibleHdc, 0, 0, SRCCOPY);

	EndPaint(hwnd, &ps);  //结束绘制
}


//鼠标悬停在按钮上绘制的动画
void buttonOnMouseHover(HWND hwnd, ButtonData* btnData)
{
	SelectObject(btnData->compatibleHdc, btnData->buttonBmp->bmps[BMP_MOUSE_HOVER]);  //选择位图

	int width = btnData->clientRect.right - btnData->clientRect.left;  //窗口宽度
	int height = btnData->clientRect.bottom - btnData->clientRect.top;  //窗口高度

	BitBlt(btnData->controlHdc, 0, 0, width, height, btnData->compatibleHdc, 0, 0, SRCCOPY);  //贴图
}

//鼠标按下动画
void buttonOnMouseDown(HWND hwnd, ButtonData* btnData)
{
	SelectObject(btnData->compatibleHdc, btnData->buttonBmp->bmps[BMP_MOUSE_DOWN]);  //选择位图

	int width = btnData->clientRect.right - btnData->clientRect.left;  //窗口宽度
	int height = btnData->clientRect.bottom - btnData->clientRect.top;  //窗口高度

	BitBlt(btnData->controlHdc, 0, 0, width, height, btnData->compatibleHdc, 0, 0, SRCCOPY);  //贴图
}


//鼠标松开动画
void buttonOnMouseUp(HWND hwnd, ButtonData* btnData)
{
	SelectObject(btnData->compatibleHdc, btnData->buttonBmp->bmps[BMP_MOUSE_HOVER]);  //选择位图，松开时鼠标还在按钮上方

	int width = btnData->clientRect.right - btnData->clientRect.left;  //窗口宽度
	int height = btnData->clientRect.bottom - btnData->clientRect.top;  //窗口高度

	BitBlt(btnData->controlHdc, 0, 0, width, height, btnData->compatibleHdc, 0, 0, SRCCOPY);  //贴图
}


//鼠标离开按钮后要把按钮样子恢复
void buttonOnMouseLeave(HWND hwnd, ButtonData* btnData)
{

	SelectObject(btnData->compatibleHdc, btnData->buttonBmp->bmps[BMP_STATIC]);  //选择位图

	int width = btnData->clientRect.right - btnData->clientRect.left;  //窗口宽度
	int height = btnData->clientRect.bottom - btnData->clientRect.top;  //窗口高度

	BitBlt(btnData->controlHdc, 0, 0, width, height, btnData->compatibleHdc, 0, 0, SRCCOPY);
}
