#include "main.h"


//win32�������
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow)
{
    //��Ŀ¼
    openDirectory(L"testMusic");
	
	initWin(hInstance, pre, pCmdLine, nCmdShow); //��ʼ������
	
	//�������򿪲���ʾ���б�
	traverse(addSongToList);

	//�¼�ѭ��
	eventLoop();


	return 0;
}