#include "MyButton.h"


//全局变量
static ButtonBmp* g_buttonBmp = NULL;  //按钮所需图片
static HDC g_hdc = NULL;  //窗口区域的环境上下文句柄
static HDC g_hdcBmp = NULL;  //用来贴图用的环境上下文句柄
static RECT g_winRect;  //窗口客户区区域
static HWND g_parent = NULL;  //父窗口句柄
static int g_isTracked = 0;  //记录鼠标事件是否激活


void buttonInit()
{
	//填充结构体
	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof(wc);  //结构体的大小
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);  //背景颜色
	wc.hCursor = LoadCursor(0, IDC_ARROW);  //默认的小箭头作为鼠标图标
	wc.hInstance = GetModuleHandle(0);  //GetModuleHandle获取程序的实例句柄
	wc.lpfnWndProc = buttonProc;  //过程函数
	wc.lpszClassName = CLASS_MYBUTTON; //类名
	wc.cbWndExtra = sizeof(void *);  //用来传递参数的附加空间大小
	wc.style = CS_DBLCLKS;  //使窗口可以接受点击事件
	
	RegisterClassEx(&wc);  //注册窗口类
}

LRESULT CALLBACK buttonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TRACKMOUSEEVENT tme;

	switch(uMsg)
	{
	case WM_CREATE: //保存参数
		buttonOnCreate(hwnd, lParam);
		break;
	case WM_MOUSEMOVE:
		if (!g_isTracked)
		{ //开启鼠标悬停，移出事件
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = hwnd;
			tme.dwFlags = TME_LEAVE | TME_HOVER;  //鼠标悬停，移出事件
			tme.dwHoverTime = 1;  //悬停事件发生需要的时间(ms)
			TrackMouseEvent(&tme);

			g_isTracked = 1;
		}
		break;
	case WM_PAINT:                    //绘制按钮
		buttonPaint(hwnd);
		break;
	case WM_MOUSEHOVER:               //鼠标悬停
		//MessageBox(0, L"test", L"test", MB_OK);
		buttonOnMouseHover(hwnd);
		g_isTracked = 0;
		break;
	case WM_MOUSELEAVE:               //鼠标离开
		buttonOnMouseLeave(hwnd);
		g_isTracked = 0;
		break;
	case WM_LBUTTONDOWN:              //鼠标按下
		buttonOnMouseDown(hwnd);
		break;
	case WM_LBUTTONUP:                //鼠标抬起
		buttonOnMouseUp(hwnd);
		//模仿win32自带的按钮控件发送点击消息到父窗口
		SendMessage(g_parent, WM_COMMAND, MAKEWPARAM(0, BN_CLICKED), (LPARAM)hwnd);  
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void buttonOnCreate(HWND hwnd, LPARAM lParam)
{
	void* param;  //参数
	param = ((LPCREATESTRUCT)lParam)->lpCreateParams;  //获取参数
	
	g_buttonBmp = (ButtonBmp*)param;  //获取ButtonBmp结构体指针

	GetClientRect(hwnd, &g_winRect);  //获取窗口区域

	g_hdc = GetDC(hwnd);  //获取客户区域的设备上下文句柄
	g_hdcBmp = CreateCompatibleDC(g_hdc);  //创建一个兼容g_hdc的上下文句柄
	
	g_parent = GetParent(hwnd);  //获取父窗口句柄
}

//绘制按钮
void buttonPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	BeginPaint(hwnd, &ps);  //开始绘制
	
	SelectObject(g_hdcBmp, g_buttonBmp->bmps[BMP_STATIC]);  //选中位图对象

	int width = g_winRect.right - g_winRect.left;  //窗口宽度
	int height = g_winRect.bottom - g_winRect.top;  //窗口高度

	BitBlt(g_hdc, 0, 0, width, height, g_hdcBmp, 0, 0, SRCCOPY);

	EndPaint(hwnd, &ps);  //结束绘制
}

//鼠标悬停在按钮上绘制的动画
void buttonOnMouseHover(HWND hwnd)
{
	SelectObject(g_hdcBmp, g_buttonBmp->bmps[BMP_MOUSE_HOVER]);  //选择位图

	int width = g_winRect.right - g_winRect.left;  //窗口宽度
	int height = g_winRect.bottom - g_winRect.top;  //窗口高度

	BitBlt(g_hdc, 0, 0, width, height, g_hdcBmp, 0, 0, SRCCOPY);  //贴图
}

//鼠标按下动画
void buttonOnMouseDown(HWND hwnd)
{
	SelectObject(g_hdcBmp, g_buttonBmp->bmps[BMP_MOUSE_DOWN]);  //选择位图

	int width = g_winRect.right - g_winRect.left;  //窗口宽度
	int height = g_winRect.bottom - g_winRect.top;  //窗口高度

	BitBlt(g_hdc, 0, 0, width, height, g_hdcBmp, 0, 0, SRCCOPY);  //贴图
}

//鼠标松开动画
void buttonOnMouseUp(HWND hwnd)
{
	SelectObject(g_hdcBmp, g_buttonBmp->bmps[BMP_MOUSE_HOVER]);  //选择位图，松开时鼠标还在按钮上方

	int width = g_winRect.right - g_winRect.left;  //窗口宽度
	int height = g_winRect.bottom - g_winRect.top;  //窗口高度

	BitBlt(g_hdc, 0, 0, width, height, g_hdcBmp, 0, 0, SRCCOPY);  //贴图
}

//鼠标离开按钮的动画
void buttonOnMouseLeave(HWND hwnd)
{

	SelectObject(g_hdcBmp, g_buttonBmp->bmps[BMP_STATIC]);  //选择位图

	int width = g_winRect.right - g_winRect.left;  //窗口宽度
	int height = g_winRect.bottom - g_winRect.top;  //窗口高度

	BitBlt(g_hdc, 0, 0, width, height, g_hdcBmp, 0, 0, SRCCOPY);
}


