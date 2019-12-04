#include "MyButton.h"

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
	switch(uMsg)
	{
	case WM_CREATE: //�������
		buttonSaveParam(hwnd, lParam);  
		break;
	case WM_PAINT:  //���ư�ť
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
	void* param;  //����
	param = ((LPCREATESTRUCT)lParam)->lpCreateParams;  //��ȡ����
	SetWindowLong(hwnd, GWL_USERDATA, (LONG)param);  //�����������Ӧ��ǰ�洰�����wc.cbWndExtra
}

void buttonPaint(HWND hwnd)
{
	HDC hdc;  //�豸������
	PAINTSTRUCT ps;  //����ƻ����йصĽṹ��
	RECT rect;  //���νṹ��

	GetClientRect(hwnd, &rect);  //��ȡ�ؼ������꣬�Ծ������ϽǺ����½��������ʽ

	COLORREF white = RGB(255, 255, 255);  //��ɫ
	COLORREF black = RGB(0, 0, 0);  //��ɫ

	hdc = BeginPaint(hwnd, &ps);  //��ʼ����

	HBRUSH hBrush = CreateSolidBrush(white);  //������ɫ��ˢ
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);  //ѡ���ɫ��ˢ
	HPEN hPen = CreatePen(PS_SOLID, 1, white);   //������ɫ����
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);  //ѡ���ɫ����

	//��һ����Բ
	Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);

	//�ָ�ԭ���Ļ�ˢ�ͻ���
	SelectObject(hdc, hOldBrush);
	SelectObject(hdc, hOldPen);

	wchar_t text[MAX_TEXT_LEN];
	GetWindowText(hwnd, text, MAX_TEXT_LEN);

	SetTextColor(hdc, black);  //�����ı���ɫΪ��ɫ
	DrawText(hdc, text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //ˮƽ��ֱ���л����ı�

	//ɾ�������Ļ�ˢ�ͻ���
	DeleteObject(hBrush);
	DeleteObject(hPen);

	EndPaint(hwnd, &ps);  //��������
}

void buttonOnClick(HWND hwnd)
{
	MessageBox(0, L"Click", L"Sub", 0);
}
