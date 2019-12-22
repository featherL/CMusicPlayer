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
	wc.lpszClassName = CLASS_MY_BUTTON; //����
	wc.style = CS_DBLCLKS;  //ʹ���ڿ��Խ��ܵ���¼�

	
	
	RegisterClassEx(&wc);  //ע�ᴰ����
}

//��ȡ�ؼ���ButtonData�ṹ���ָ��
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
	{ //���洴�����ڴ���Ĳ���,�洢һЩ��Ҫ�����ݵȲ���
		buttonOnCreate(hwnd, lParam);
	}

	btnData = getButtonData(hwnd);  //��ȡ������������

	switch(message)
	{
	case WM_MOUSEMOVE:
		if (!btnData->isMouseTracked)
		{ //���������ͣ���Ƴ��¼�
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = hwnd;
			tme.dwFlags = TME_LEAVE | TME_HOVER;  //�����ͣ���Ƴ��¼�
			tme.dwHoverTime = 1;  //��ͣ�¼�������Ҫ��ʱ��(ms)
			TrackMouseEvent(&tme);

			btnData->isMouseTracked = 0;
		}
		break;
	case WM_PAINT:                    //���ư�ť
		buttonPaint(hwnd, btnData);
		break;
	case WM_MOUSEHOVER:               //�����ͣ
		buttonOnMouseHover(hwnd, btnData);
		btnData->isMouseTracked = 0;
		break;
	case WM_MOUSELEAVE:               //����뿪
		buttonOnMouseLeave(hwnd, btnData);
		btnData->isMouseTracked = 0;
		break;
	case WM_LBUTTONDOWN:              //��갴��
		buttonOnMouseDown(hwnd, btnData);
		break;
	case WM_LBUTTONUP:                //���̧��
		buttonOnMouseUp(hwnd, btnData);
		//ģ��win32�Դ��İ�ť�ؼ����͵����Ϣ��������
		SendMessage(btnData->hParent, WM_COMMAND, MAKEWPARAM(0, BN_CLICKED), (LPARAM)hwnd);
		break;
	case WM_DESTROY:
		buttonOnDestroy(hwnd, btnData);  //�ͷŷ������Դ
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

//���ڴ����󣬱��洫�ݹ����Ĳ����ȵ�
void buttonOnCreate(HWND hwnd, LPARAM lParam)
{
	ButtonData* btnData = (ButtonData*)malloc(sizeof(ButtonData));  //����ռ������

	btnData->hParent = GetParent(hwnd);   //�����ھ��
	
	btnData->isMouseTracked = 0;  //�Ƿ񼤻�����¼�

	GetClientRect(hwnd, &btnData->clientRect);  //�ͻ�����������
	
	btnData->controlHdc = GetDC(hwnd);  //�豸���������ľ��

	btnData->compatibleHdc = CreateCompatibleDC(btnData->controlHdc);  //���ݵ��豸�����ľ��

	btnData->buttonBmp = ((LPCREATESTRUCT)lParam)->lpCreateParams;  //ͼƬ��Դͨ��CreateWindow�����һ��������������
	
	//����btnDataָ��
	SetWindowLong(hwnd, GWL_USERDATA, (LONG)btnData);
}

//��������ʱ����һЩ��Դ�ͷŵĲ���
void buttonOnDestroy(HWND hwnd, ButtonData* btnData)
{
	//�ͷ��豸������
	DeleteDC(btnData->compatibleHdc); 
	ReleaseDC(hwnd, btnData->controlHdc);  

	//btnData->buttonBmp���ָ���Ǵ������ڴ���ģ�Ӧ���������ͷ�

	free(btnData);  //�ͷ�����ṹ�����Դ
}

//���ư�ť
void buttonPaint(HWND hwnd, ButtonData* btnData)
{
	PAINTSTRUCT ps;
	BeginPaint(hwnd, &ps);  //��ʼ����
	
	SelectObject(btnData->compatibleHdc, btnData->buttonBmp->bmps[BMP_STATIC]);  //ѡ��λͼ����

	int width = btnData->clientRect.right - btnData->clientRect.left;  //���ڿ��
	int height = btnData->clientRect.bottom - btnData->clientRect.top;  //���ڸ߶�

	BitBlt(btnData->controlHdc, 0, 0, width, height, btnData->compatibleHdc, 0, 0, SRCCOPY);

	EndPaint(hwnd, &ps);  //��������
}


//�����ͣ�ڰ�ť�ϻ��ƵĶ���
void buttonOnMouseHover(HWND hwnd, ButtonData* btnData)
{
	SelectObject(btnData->compatibleHdc, btnData->buttonBmp->bmps[BMP_MOUSE_HOVER]);  //ѡ��λͼ

	int width = btnData->clientRect.right - btnData->clientRect.left;  //���ڿ��
	int height = btnData->clientRect.bottom - btnData->clientRect.top;  //���ڸ߶�

	BitBlt(btnData->controlHdc, 0, 0, width, height, btnData->compatibleHdc, 0, 0, SRCCOPY);  //��ͼ
}

//��갴�¶���
void buttonOnMouseDown(HWND hwnd, ButtonData* btnData)
{
	SelectObject(btnData->compatibleHdc, btnData->buttonBmp->bmps[BMP_MOUSE_DOWN]);  //ѡ��λͼ

	int width = btnData->clientRect.right - btnData->clientRect.left;  //���ڿ��
	int height = btnData->clientRect.bottom - btnData->clientRect.top;  //���ڸ߶�

	BitBlt(btnData->controlHdc, 0, 0, width, height, btnData->compatibleHdc, 0, 0, SRCCOPY);  //��ͼ
}


//����ɿ�����
void buttonOnMouseUp(HWND hwnd, ButtonData* btnData)
{
	SelectObject(btnData->compatibleHdc, btnData->buttonBmp->bmps[BMP_MOUSE_HOVER]);  //ѡ��λͼ���ɿ�ʱ��껹�ڰ�ť�Ϸ�

	int width = btnData->clientRect.right - btnData->clientRect.left;  //���ڿ��
	int height = btnData->clientRect.bottom - btnData->clientRect.top;  //���ڸ߶�

	BitBlt(btnData->controlHdc, 0, 0, width, height, btnData->compatibleHdc, 0, 0, SRCCOPY);  //��ͼ
}


//����뿪��ť��Ҫ�Ѱ�ť���ӻָ�
void buttonOnMouseLeave(HWND hwnd, ButtonData* btnData)
{

	SelectObject(btnData->compatibleHdc, btnData->buttonBmp->bmps[BMP_STATIC]);  //ѡ��λͼ

	int width = btnData->clientRect.right - btnData->clientRect.left;  //���ڿ��
	int height = btnData->clientRect.bottom - btnData->clientRect.top;  //���ڸ߶�

	BitBlt(btnData->controlHdc, 0, 0, width, height, btnData->compatibleHdc, 0, 0, SRCCOPY);
}


