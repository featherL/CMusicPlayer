#include "view.h"
#include "control.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow)
{
	openDirectory(L"C:\\Users\\15107\\Music");

	initWin(hInstance, pre, pCmdLine, nCmdShow);
	eventLoop();

	//MusicNode* cur = g_headOfList;

	//if(cur != NULL)
	//{
	//	do
	//	{
	//		wchar_t output[MAX_PATH];
	//		wsprintf(output, L"play %s(%d)\n", cur->name, cur->deviceId);
	//		OutputDebugString(output);

	//		//���Բ�������
	//		MCI_PLAY_PARMS mciPlay;
	//		if(mciSendCommand(cur->deviceId, MCI_PLAY, MCI_WAIT, (DWORD)&mciPlay))
	//			break;

	//		cur = cur->next;
	//	} while(cur != g_headOfList);
	//}

	return 0;
}