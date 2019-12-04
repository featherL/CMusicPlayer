#include "view.h"
#include "control.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow)
{
	initWin(hInstance, pre, pCmdLine, nCmdShow);
	eventLoop();

	/*
	wchar_t tmp[40];
	wsprintf(tmp, L"%d %d", sizeof(LONG), sizeof(void *));
	MessageBox(0, tmp, 0, 0);
	*/

	return 0;
}