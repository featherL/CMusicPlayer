#include "main.h"


//win32程序入口
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE pre, PWSTR pCmdLine, int nCmdShow)
{
    //打开目录
    openDirectory(L"testMusic");
	
	initWin(hInstance, pre, pCmdLine, nCmdShow); //初始化窗口
	
	//将歌曲打开并显示到列表
	traverse(addSongToList);

	//事件循环
	eventLoop();


	return 0;
}