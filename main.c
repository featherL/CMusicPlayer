#include "view.h"
#include "control.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow)
{
	
	
	initWin(hInstance, pre, pCmdLine, nCmdShow); //��ʼ������
	
	//��Ŀ¼���������򿪲���ʾ���б�
	openDirectory(L"C:\\Users\\15107\\Music");
	traverse(addSongToList);

	//�¼�ѭ��
	eventLoop();


	return 0;
}