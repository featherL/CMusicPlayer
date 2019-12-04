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
	wc.lpszClassName = CLASS_MYBUTTON; //类名
	wc.cbWndExtra = sizeof(void *);  //用来传递参数的附加空间大小
	wc.style = CS_DBLCLKS;  //使窗口可以接受点击事件
	
	RegisterClassEx(&wc);  //注册窗口类
}

LRESULT CALLBACK buttonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE: //保存参数
		buttonSaveParam(hwnd, lParam);  
		break;
	case WM_PAINT:  //绘制按钮
		buttonPaint(hwnd);
		break;
	case WM_LBUTTONUP:
		buttonOnClick(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void buttonSaveParam(HWND hwnd, LPARAM lParam)
{
	void* param;  //参数
	param = ((LPCREATESTRUCT)lParam)->lpCreateParams;  //获取参数
	SetWindowLong(hwnd, GWL_USERDATA, (LONG)param);  //保存参数，对应了前面窗口类的wc.cbWndExtra
}

void buttonPaint(HWND hwnd)
{
	HDC hdc;  //设备上下文
	PAINTSTRUCT ps;  //与绘制环境有关的结构体
	RECT rect;  //矩形结构体

	GetClientRect(hwnd, &rect);  //获取控件的坐标，以矩形左上角和右下角坐标的形式

	COLORREF white = RGB(255, 255, 255);  //白色
	COLORREF black = RGB(0, 0, 0);  //黑色

	hdc = BeginPaint(hwnd, &ps);  //开始绘制

	HBRUSH hBrush = CreateSolidBrush(white);  //创建白色画刷
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);  //选择白色画刷
	HPEN hPen = CreatePen(PS_SOLID, 1, white);   //创建白色画笔
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);  //选择白色画笔

	//画一个椭圆
	Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);

	//恢复原来的画刷和画笔
	SelectObject(hdc, hOldBrush);
	SelectObject(hdc, hOldPen);

	wchar_t text[MAX_TEXT_LEN];
	GetWindowText(hwnd, text, MAX_TEXT_LEN);

	SetTextColor(hdc, black);  //设置文本颜色为黑色
	DrawText(hdc, text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //水平垂直居中绘制文本

	//删除创建的画刷和画笔
	DeleteObject(hBrush);
	DeleteObject(hPen);

	EndPaint(hwnd, &ps);  //结束绘制
}

void buttonOnClick(HWND hwnd)
{
	MessageBox(0, L"Click", L"Sub", 0);
}
