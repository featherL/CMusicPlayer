#include "view.h"
#include "control.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow)
{
	
	
	initWin(hInstance, pre, pCmdLine, nCmdShow); //初始化窗口
	
	//打开目录，将歌曲打开并显示到列表
	openDirectory(L"C:\\Users\\15107\\Music");
	traverse(addSongToList);

	//事件循环
	eventLoop();


	return 0;
}