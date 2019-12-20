#include "MyButton.h"


//ȫ�ֱ���
static ButtonBmp* g_buttonBmp = NULL;  //��ť����ͼƬ
static HDC g_hdc = NULL;  //��������Ļ��������ľ��
static HDC g_hdcBmp = NULL;  //������ͼ�õĻ��������ľ��
static RECT g_winRect;  //���ڿͻ�������
static HWND g_parent = NULL;  //�����ھ��
static int g_isTracked = 0;  //��¼����¼��Ƿ񼤻�


void buttonInit()
{
	//���ṹ��
	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof(wc);  //�ṹ��Ĵ�С
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);  //������ɫ
	wc.hCursor = LoadCursor(0, IDC_ARROW);  //Ĭ�ϵ�С��ͷ��Ϊ���ͼ��
	wc.hInstance = GetModuleHandle(0);  //GetModuleHandle��ȡ�����ʵ�����
	wc.lpfnWndProc = buttonProc;  //���̺���
	wc.lpszClassName = CLASS_MYBUTTON; //����
	wc.cbWndExtra = sizeof(void *);  //�������ݲ����ĸ��ӿռ��С
	wc.style = CS_DBLCLKS;  //ʹ���ڿ��Խ��ܵ���¼�
	
	RegisterClassEx(&wc);  //ע�ᴰ����
}

LRESULT CALLBACK buttonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TRACKMOUSEEVENT tme;

	switch(uMsg)
	{
	case WM_CREATE: //�������
		buttonOnCreate(hwnd, lParam);
		break;
	case WM_MOUSEMOVE:
		if (!g_isTracked)
		{ //���������ͣ���Ƴ��¼�
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = hwnd;
			tme.dwFlags = TME_LEAVE | TME_HOVER;  //�����ͣ���Ƴ��¼�
			tme.dwHoverTime = 1;  //��ͣ�¼�������Ҫ��ʱ��(ms)
			TrackMouseEvent(&tme);

			g_isTracked = 1;
		}
		break;
	case WM_PAINT:                    //���ư�ť
		buttonPaint(hwnd);
		break;
	case WM_MOUSEHOVER:               //�����ͣ
		//MessageBox(0, L"test", L"test", MB_OK);
		buttonOnMouseHover(hwnd);
		g_isTracked = 0;
		break;
	case WM_MOUSELEAVE:               //����뿪
		buttonOnMouseLeave(hwnd);
		g_isTracked = 0;
		break;
	case WM_LBUTTONDOWN:              //��갴��
		buttonOnMouseDown(hwnd);
		break;
	case WM_LBUTTONUP:                //���̧��
		buttonOnMouseUp(hwnd);
		//ģ��win32�Դ��İ�ť�ؼ����͵����Ϣ��������
		SendMessage(g_parent, WM_COMMAND, MAKEWPARAM(0, BN_CLICKED), (LPARAM)hwnd);  
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void buttonOnCreate(HWND hwnd, LPARAM lParam)
{
	void* param;  //����
	param = ((LPCREATESTRUCT)lParam)->lpCreateParams;  //��ȡ����
	
	g_buttonBmp = (ButtonBmp*)param;  //��ȡButtonBmp�ṹ��ָ��

	GetClientRect(hwnd, &g_winRect);  //��ȡ��������

	g_hdc = GetDC(hwnd);  //��ȡ�ͻ�������豸�����ľ��
	g_hdcBmp = CreateCompatibleDC(g_hdc);  //����һ������g_hdc�������ľ��
	
	g_parent = GetParent(hwnd);  //��ȡ�����ھ��
}

//���ư�ť
void buttonPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	BeginPaint(hwnd, &ps);  //��ʼ����
	
	SelectObject(g_hdcBmp, g_buttonBmp->bmps[BMP_STATIC]);  //ѡ��λͼ����

	int width = g_winRect.right - g_winRect.left;  //���ڿ��
	int height = g_winRect.bottom - g_winRect.top;  //���ڸ߶�

	BitBlt(g_hdc, 0, 0, width, height, g_hdcBmp, 0, 0, SRCCOPY);

	EndPaint(hwnd, &ps);  //��������
}

//�����ͣ�ڰ�ť�ϻ��ƵĶ���
void buttonOnMouseHover(HWND hwnd)
{
	SelectObject(g_hdcBmp, g_buttonBmp->bmps[BMP_MOUSE_HOVER]);  //ѡ��λͼ

	int width = g_winRect.right - g_winRect.left;  //���ڿ��
	int height = g_winRect.bottom - g_winRect.top;  //���ڸ߶�

	BitBlt(g_hdc, 0, 0, width, height, g_hdcBmp, 0, 0, SRCCOPY);  //��ͼ
}

//��갴�¶���
void buttonOnMouseDown(HWND hwnd)
{
	SelectObject(g_hdcBmp, g_buttonBmp->bmps[BMP_MOUSE_DOWN]);  //ѡ��λͼ

	int width = g_winRect.right - g_winRect.left;  //���ڿ��
	int height = g_winRect.bottom - g_winRect.top;  //���ڸ߶�

	BitBlt(g_hdc, 0, 0, width, height, g_hdcBmp, 0, 0, SRCCOPY);  //��ͼ
}

//����ɿ�����
void buttonOnMouseUp(HWND hwnd)
{
	SelectObject(g_hdcBmp, g_buttonBmp->bmps[BMP_MOUSE_HOVER]);  //ѡ��λͼ���ɿ�ʱ��껹�ڰ�ť�Ϸ�

	int width = g_winRect.right - g_winRect.left;  //���ڿ��
	int height = g_winRect.bottom - g_winRect.top;  //���ڸ߶�

	BitBlt(g_hdc, 0, 0, width, height, g_hdcBmp, 0, 0, SRCCOPY);  //��ͼ
}

//����뿪��ť�Ķ���
void buttonOnMouseLeave(HWND hwnd)
{

	SelectObject(g_hdcBmp, g_buttonBmp->bmps[BMP_STATIC]);  //ѡ��λͼ

	int width = g_winRect.right - g_winRect.left;  //���ڿ��
	int height = g_winRect.bottom - g_winRect.top;  //���ڸ߶�

	BitBlt(g_hdc, 0, 0, width, height, g_hdcBmp, 0, 0, SRCCOPY);
}


