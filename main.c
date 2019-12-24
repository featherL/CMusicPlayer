#include "view.h"
#include "control.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow)
{
	//initWin(hInstance, pre, pCmdLine, nCmdShow);
	//eventLoop();

	/*
	wchar_t tmp[40];
	wsprintf(tmp, L"%d %d", sizeof(LONG), sizeof(void *));
	MessageBox(0, tmp, 0, 0);
	*/

	openDirectory(L"C:\\Users\\15107\\Music");
	

	//MusicNode* cur = g_headOfList;

	//if(cur != NULL)
	//{
	//	do
	//	{
	//		wchar_t output[MAX_PATH];
	//		wsprintf(output, L"play %s(%d)\n", cur->name, cur->deviceId);
	//		OutputDebugString(output);

	//		//³¢ÊÔ²¥·ÅÒôÀÖ
	//		MCI_PLAY_PARMS mciPlay;
	//		if(mciSendCommand(cur->deviceId, MCI_PLAY, MCI_WAIT, (DWORD)&mciPlay))
	//			break;

	//		cur = cur->next;
	//	} while(cur != g_headOfList);
	//}

	return 0;
}