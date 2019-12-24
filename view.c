#include "view.h"

ButtonBmp * g_playBtnBmpCur = NULL;		//���Ű�ť�ĵ�ǰʹ�õ�һ��ͼƬ
ButtonBmp* g_playBtnBmp1 = NULL;		//���Ű�ť��û�в���ʱ��һ��ͼƬ
ButtonBmp* g_playBtnBmp2 = NULL;		//���Ű�ť����ʱ��һ��ͼƬ
ButtonBmp* g_nextBtnBmp = NULL;   //��һ�װ�ť�����ͼƬ
ButtonBmp* g_prevBtnBmp = NULL;   //��һ�װ�ť�����ͼƬ
ButtonBmp* g_xBtnBmp = NULL;      //�˳���ť�����ͼƬ
ButtonBmp* g_modeBtnBmpCur = NULL;//ģʽ��ť�ĵ�ǰʹ�õ�һ�����ͼƬ
ButtonBmp* g_modeBtnBmp1 = NULL;  //ģʽ��ť˳�򲥷�ʹ�õ����ͼƬ
ButtonBmp* g_modeBtnBmp2 = NULL;  //ģʽ��ťѭ������ʹ�õ����ͼƬ
ButtonBmp* g_modeBtnBmp3 = NULL;  //ģʽ��ť�������ʹ�õ����ͼƬ

HDC g_hdcOfMainWin;			//�����ڵ��豸���
HDC g_hBuffOfMainWin;		//����������豸����
HBITMAP g_hBitmap;			//������ͼ���ڴ�����
HWND g_hWin;				//�����ھ��
HWND g_hSongList;			//�����б�ľ��


//��ʼ������
	//hInstance ������
	//pre		�ò���windows��ʹ��
	//pCmdLind	�����в���
	//nCmdShow	������ʾ�ķ�ʽ
void initWin(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow)
{
	buttonInit();          //ע���Զ���İ�ť��
	InitCommonControls();  //��ʼ��window�ṩ�Ŀؼ�


	WNDCLASSEX wc = { 0 };
	wc.hCursor = LoadCursor(0, IDC_ARROW);  //������ʽ
	wc.cbSize = sizeof(WNDCLASSEX);  //�ṹ��Ĵ�С
	wc.hbrBackground = (HBRUSH)GetStockBrush(BLACK_BRUSH);  //������ɫ
	wc.lpfnWndProc = windowProc;  //���ڹ��̺���
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;  //��������

	RegisterClassEx(&wc);

	HWND hWin = CreateWindow(
		CLASS_NAME,           // ��������
		WINDOW_TITLE,         // ���ڱ���
		WS_POPUP,  // ������ʽ��û�б�������û�б߿򣨲��ɵ�����С��
		// ����λ�ã�Ĭ�ϣ������ڴ�С
		400, 200, WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL,       // ������
		NULL,       // �˵�
		hInstance,  // �����ʵ�����
		NULL        // �������
	);

	if(hWin == NULL)
		exit(0);

	playButtonInit(hWin, hInstance);        //���Ű�ť
	nextButtonInit(hWin, hInstance);        //��һ�װ�ť
	prevButtonInit(hWin, hInstance);        //��һ�װ�ť
	xButtonInit(hWin, hInstance);           //�رմ��ڰ�ť
	modeButtonInit(hWin, hInstance);        //ģʽ��ť
	songListInit(hWin, hInstance);			//�����б�

	ShowWindow(hWin, nCmdShow);             //��ʾ����
}

//����ģʽ��ť
	//hParent �����ھ��
	//hInstance ������
void modeButtonInit(HWND hParent, HINSTANCE hInstance)
{
	g_modeBtnBmpCur = (ButtonBmp*)malloc(sizeof(ButtonBmp)); //��ǰ��������Ҫ��ͼƬ��
	g_modeBtnBmp1 = (ButtonBmp*)malloc(sizeof(ButtonBmp));
	g_modeBtnBmp2 = (ButtonBmp*)malloc(sizeof(ButtonBmp));
	g_modeBtnBmp3 = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	//����ͼƬ��Դ

	//ѭ������ͼƬ
	g_modeBtnBmp1->bmps[BMP_STATIC] = LoadImage(0, BMP_STATIC_MODE_1_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);
	//�����ͣ
	g_modeBtnBmp1->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_HOVER_MODE_1_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);
	//��갴��
	g_modeBtnBmp1->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_DOWN_MODE_1_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);


	//˳�򲥷�ͼƬ
	g_modeBtnBmp2->bmps[BMP_STATIC] = LoadImage(0, BMP_STATIC_MODE_2_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);
	//�����ͣ
	g_modeBtnBmp2->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_HOVER_MODE_2_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);
	//��갴��
	g_modeBtnBmp2->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_DOWN_MODE_2_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);


	//�������ͼƬ
	g_modeBtnBmp3->bmps[BMP_STATIC] = LoadImage(0, BMP_STATIC_MODE_3_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);
	//�����ͣ
	g_modeBtnBmp3->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_HOVER_MODE_3_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);
	//��갴��
	g_modeBtnBmp3->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_DOWN_MODE_3_BUTTON, IMAGE_BITMAP,
		WIDTH_MODE_BUTTON, HEIGHT_MODE_BUTTON, LR_LOADFROMFILE);


	memcpy(g_modeBtnBmpCur, g_modeBtnBmp1, sizeof(ButtonBmp));        //��ʼΪѭ�����ŵ�ͼƬ


	HWND hModeBtn = CreateWindow(
		CLASS_MY_BUTTON,
		NULL,
		WS_CHILD | WS_VISIBLE,  //WS_CHILD��ʾ���������ĳ�����ڵ��Ӵ��ڣ�WS_VISIBLE��ʾ���ڿɼ��������ý��᲻��ʾ��
		POS_X_MODE_BUTTON,
		POS_Y_MODE_BUTTON,
		WIDTH_MODE_BUTTON,
		HEIGHT_MODE_BUTTON,
		hParent,
		NULL,
		hInstance,
		(LPARAM)g_modeBtnBmpCur   //���ڰ�ťͼƬ��ָ�룬��Ϊ��������
	);

	//���¼�������
	bindCallBackFunc(hModeBtn, modeBtnHandler);
}

//�����˳���ť
	//hParent �����ھ��
	//hInstance ������
void xButtonInit(HWND hParent, HINSTANCE hInstance)
{
	ButtonBmp* btnBmp = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	g_xBtnBmp = btnBmp;

	//����ͼƬ��Դ

	//��̬
	btnBmp->bmps[BMP_STATIC] = LoadImage(0, BMP_STATIC_X_BUTTON, IMAGE_BITMAP,
		WIDTH_X_BUTTON, HEIGHT_X_BUTTON, LR_LOADFROMFILE);

	//�����ͣ
	btnBmp->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_HOVER_X_BUTTON, IMAGE_BITMAP,
		WIDTH_X_BUTTON, HEIGHT_X_BUTTON, LR_LOADFROMFILE);

	//��갴��
	btnBmp->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_DOWN_X_BUTTON, IMAGE_BITMAP,
		WIDTH_X_BUTTON, HEIGHT_X_BUTTON, LR_LOADFROMFILE);


	HWND hXBtn = CreateWindow(
		CLASS_MY_BUTTON,
		NULL,
		WS_CHILD | WS_VISIBLE,
		POS_X_X_BUTTON,
		POS_Y_X_BUTTON,
		WIDTH_X_BUTTON,
		HEIGHT_X_BUTTON,
		hParent,
		NULL,
		hInstance,
		(LPARAM)btnBmp   //���ڰ�ťͼƬ��ָ�룬��Ϊ��������
	);


	bindCallBackFunc(hXBtn, quitBtnHandler);            
}

//����prev��ť
	//hParent �����ھ��
	//hInstance ������
void prevButtonInit(HWND hParent, HINSTANCE hInstance)
{
	ButtonBmp* btnBmp = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	g_prevBtnBmp = btnBmp;

	//����ͼƬ��Դ

	//��̬
	btnBmp->bmps[BMP_STATIC] = LoadImage(0, BMP_STATIC_PREV_BUTTON, IMAGE_BITMAP,
		WIDTH_PREV_BUTTON, HEIGHT_PREV_BUTTON, LR_LOADFROMFILE);

	//�����ͣ
	btnBmp->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_HOVER_PREV_BUTTON, IMAGE_BITMAP,
		WIDTH_PREV_BUTTON, HEIGHT_PREV_BUTTON, LR_LOADFROMFILE);

	//��갴��
	btnBmp->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_DOWN_PREV_BUTTON, IMAGE_BITMAP,
		WIDTH_PREV_BUTTON, HEIGHT_PREV_BUTTON, LR_LOADFROMFILE);


	HWND hPrevBtn = CreateWindow(
		CLASS_MY_BUTTON,
		NULL,
		WS_CHILD | WS_VISIBLE,
		POS_X_PREV_BUTTON,
		POS_Y_PREV_BUTTON,
		WIDTH_PREV_BUTTON,
		HEIGHT_PREV_BUTTON,
		hParent,
		NULL,
		hInstance,
		(LPARAM)btnBmp   //���ڰ�ťͼƬ��ָ�룬��Ϊ��������
	);

	bindCallBackFunc(hPrevBtn, playPrev); 
}

//����next��ť
	//hParent �����ھ��
	//hInstance ������
void nextButtonInit(HWND hParent, HINSTANCE hInstance) 
{
	ButtonBmp* btnBmp = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	g_nextBtnBmp = btnBmp;

	//����ͼƬ��Դ

	//��̬
	btnBmp->bmps[BMP_STATIC] = LoadImage(0, BMP_STATIC_NEXT_BUTTON, IMAGE_BITMAP,
		WIDTH_NEXT_BUTTON, HEIGHT_NEXT_BUTTON, LR_LOADFROMFILE);

	//�����ͣ
	btnBmp->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_HOVER_NEXT_BUTTON, IMAGE_BITMAP,
		WIDTH_NEXT_BUTTON, HEIGHT_NEXT_BUTTON, LR_LOADFROMFILE);

	//��갴��
	btnBmp->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_DOWN_NEXT_BUTTON, IMAGE_BITMAP,
		WIDTH_NEXT_BUTTON, HEIGHT_NEXT_BUTTON, LR_LOADFROMFILE);


	HWND hNextBtn = CreateWindow(
		CLASS_MY_BUTTON,
		NULL,
		WS_CHILD | WS_VISIBLE,
		POS_X_NEXT_BUTTON,
		POS_Y_NEXT_BUTTON,
		WIDTH_NEXT_BUTTON,
		HEIGHT_NEXT_BUTTON,
		hParent,
		NULL,
		hInstance,
		(LPARAM)btnBmp   //���ڰ�ťͼƬ��ָ�룬��Ϊ��������
	);

	bindCallBackFunc(hNextBtn, playNext); 
}

//�������Ű�ť
	//hParent �����ھ��
	//hInstance ������
void playButtonInit(HWND hParent, HINSTANCE hInstance)
{
	g_playBtnBmpCur = (ButtonBmp*)malloc(sizeof(ButtonBmp));
	g_playBtnBmp1 = (ButtonBmp*)malloc(sizeof(ButtonBmp));
	g_playBtnBmp2 = (ButtonBmp*)malloc(sizeof(ButtonBmp));

	//����ͼƬ��Դ
	
	//δ�����õ�һ�׶���
	//��̬
	g_playBtnBmp1->bmps[BMP_STATIC] = LoadImage(0, BMP_PAUSE_STATIC_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);

	//�����ͣ
	g_playBtnBmp1->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_PAUSE_HOVER_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);

	//��갴��
	g_playBtnBmp1->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_MOUSE_DOWN_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);


	//��һ��ͼ������ʱ�õ�һ�׶���
	g_playBtnBmp2->bmps[BMP_STATIC] = LoadImage(0, BMP_PLAY_STATIC_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);

	g_playBtnBmp2->bmps[BMP_MOUSE_HOVER] = LoadImage(0, BMP_PLAY_HOVER_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);

	g_playBtnBmp2->bmps[BMP_MOUSE_DOWN] = LoadImage(0, BMP_MOUSE_DOWN_PLAY_BUTTON, IMAGE_BITMAP,
		WIDTH_PLAY_BUTTON, HEIGHT_PLAY_BUTTON, LR_LOADFROMFILE);  //����ͼ�͵�һ�׵�һ��

	//ѡ��һ��ͼ��Ϊ��ǰ��ʹ�õ�һ��ͼ
	//�����ڴ濽���ķ�ʽ�����ݸ���һ��
	memcpy(g_playBtnBmpCur, g_playBtnBmp1, sizeof(ButtonBmp));

	HWND hPlayBtn = CreateWindow(
		CLASS_MY_BUTTON,
		NULL,
		WS_CHILD | WS_VISIBLE,
		POS_X_PLAY_BUTTON,
		POS_Y_PLAY_BUTTON,
		WIDTH_PLAY_BUTTON,
		HEIGHT_PLAY_BUTTON,
		hParent,
		NULL,
		hInstance,
		(LPARAM)g_playBtnBmpCur   //���ڰ�ťͼƬ��ָ�룬��Ϊ��������
		);


	//�󶨰�ť����¼�
	bindCallBackFunc(hPlayBtn, playBtnHandler);
}

//���������б�
	//hParent �����ھ��
	//hInstance ������
void songListInit(HWND hParent, HINSTANCE hInstance)
{
	HWND hSongList = CreateWindow(
		WC_LISTVIEW,
		NULL,
		WS_CHILD |WS_VISIBLE | LBS_NOTIFY,
		POS_X_SONG_LIST,
		POS_Y_SONG_LIST,
		WIDTH_SONG_LIST,
		HEIGHT_SONG_LIST,
		hParent,
		NULL,
		hInstance,
		NULL
	);

	g_hSongList = hSongList;	//��������ȫ�ֱ�������

	//�����б���У��б��ͷ��
	LV_COLUMN   lvc;
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;

	lvc.cx = WIDTH_OF_LIST_COLUMN_1;		//���
	lvc.pszText = TEXT_OF_LIST_COLUMN_1;	//��ͷ����
	ListView_InsertColumn(hSongList, 0, &lvc);

	lvc.cx = WIDTH_OF_LIST_COLUMN_2;		//���
	lvc.pszText = TEXT_OF_LIST_COLUMN_2;	//��ͷ����
	ListView_InsertColumn(hSongList, 1, &lvc);
}

//���ƽ�����
	//persent �������İٷֱ�  persentΪ98���ʾ98%
void drawProgressBar(double persent)
{
	RECT rect;
	HBRUSH bgBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);  //��ɫ����
	HBRUSH fgBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);  //��ɫǰ��

	rect.left = POS_X_PROGRESS_BAR;
	rect.right = rect.left + WIDTH_PROGRESS_BAR;
	rect.top = POS_Y_PROGRESS_BAR;
	rect.bottom = rect.top + HEIGHT_PROGRESS_BAR;

	int length = (int)(persent * WIDTH_PROGRESS_BAR / 100);

	SelectObject(g_hBuffOfMainWin, g_hBitmap);		//ѡ��һ��������ܿ�ʼ����
	FillRect(g_hBuffOfMainWin, &rect, bgBrush);		//���Ʊ���

	rect.right = rect.left + length;				//���������Ҷ�λ��Ϊ���λ�ü��ϳ���

	FillRect(g_hBuffOfMainWin, &rect, fgBrush);		//���ƽ�����

	//��������ڴ濽���������Ĵ��ڵ�����
	BitBlt(g_hdcOfMainWin, POS_X_PROGRESS_BAR, POS_Y_PROGRESS_BAR, 
		WIDTH_PROGRESS_BAR, HEIGHT_PROGRESS_BAR, g_hBuffOfMainWin,
		POS_X_PROGRESS_BAR, POS_Y_PROGRESS_BAR, SRCCOPY);
}

//�л����Ű�ť��ͼƬ
	//hwnd ��ť���
	//status ��ť��״̬
void switchPlayBtnBmp(HWND hwnd, int status)
{
	if(status == STATUS_PLAY)
	{ //����״̬
		memcpy(g_playBtnBmpCur, g_playBtnBmp2, sizeof(ButtonBmp));
	}
	else
	{ //��ͣ״̬
		memcpy(g_playBtnBmpCur, g_playBtnBmp1, sizeof(ButtonBmp));
	}

	//ˢ�°�ť
	InvalidateRect(hwnd, NULL, FALSE);
	UpdateWindow(hwnd);
}

//�л�ģʽ��ť��ͼƬ
	//hwnd ��ť���
	//status ��ť��״̬
void switchModeBtnBmp(HWND hwnd, int status)
{
	if (status == MODE_LOOP)
	{ //ѭ������״̬
		memcpy(g_modeBtnBmpCur, g_modeBtnBmp1, sizeof(ButtonBmp));
	}
	else if(status == MODE_ORDER)
	{ //˳�򲥷�״̬
		memcpy(g_modeBtnBmpCur, g_modeBtnBmp2, sizeof(ButtonBmp));
	}
	else 
	{ //�������״̬
		memcpy(g_modeBtnBmpCur, g_modeBtnBmp3, sizeof(ButtonBmp));
	}

	//ˢ�°�ť
	InvalidateRect(hwnd, NULL, FALSE);
	UpdateWindow(hwnd);
}