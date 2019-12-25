#include "control.h"

//static属性让全局变量，仅在该文件可见
static Handler g_handlers[MAX_LEN_FOR_HANDLER];		//存储控件的回调函数及其句柄
static int g_lenOfHandlers = 0;						//g_handlers数组元素的个数
static WORD g_select = 1;							//列表选中的歌曲对应的设备id
static int g_indexOfItem = 0;						//下一个添加进列表的项的索引

//主窗口过程函数
	//hwnd 窗口句柄
	//message 用来传入消息
	//wParam 保存附加信息
	//lParam 保存附加信息
	//操作系统要求一个返回值
LRESULT CALLBACK windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message)
	{
	case WM_CREATE:
		winOnCreate(hwnd);
		break;
	case WM_NOTIFY:
		winOnNotify(hwnd, message, wParam, lParam);
		break;
	case WM_NCHITTEST:  //鼠标点击测试事件（可用于实现窗口拖动）
		return winOnNcHitTest(hwnd, lParam);
	case WM_NCDESTROY:
		//窗口销毁消息，WM_NCDESTROY是子窗口都销毁后才触发的
		winOnDestroy();
		break;
	case WM_COMMAND:
		//控件触发的消息
		return winOnCommand(hwnd, message, wParam, lParam);  //里面会调用控件绑定的回调函数
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);  //默认的窗口过程函数
	}

	return 0;  //正常退出
}

//事件消息处理循环
void eventLoop()
{
	MSG msg = { 0 };
	while(msg.message != WM_QUIT)
	{
		//取出消息
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);  //将按键消息码转换成对应的字符编码
			DispatchMessage(&msg);  //分发消息给窗口过程函数
		}
		else
		{
			//检查当前歌曲是否播放完毕
			//如果播放完毕，播放下一首
			progressWhenNoMessage();
		}
	}
}


//添加歌曲到歌曲列表显示，该函数作为回调函数传入traverseAllMusic
	//node 歌曲节点
	//返回值，给traverseAllMusic函数用
int addSongToList(MusicNode* node)
{
	LVITEM lvitem;
	lvitem.mask = LVIF_TEXT;
	lvitem.cchTextMax = MAX_PATH;

	lvitem.iItem = g_indexOfItem;  //第几项

	lvitem.iSubItem = 0;			//列
	lvitem.pszText = node->name;
	ListView_InsertItem(g_hSongList, &lvitem);	//第一列用ListView_InsertItem

	//将设备id转换成字符串
	wchar_t strId[1024];
	wsprintf(strId, L"%u", node->deviceId);

	lvitem.iSubItem = 1;			//列
	lvitem.pszText = strId;
	ListView_SetItem(g_hSongList, &lvitem);		//其它列用ListView_SetItem

	g_indexOfItem++;			//递增，备下一次插入用

	return 1;
}

//根据控件句柄，获取回调函
	//hwnd 控件的句柄
	//返回值为回调函数指针，若没有返回NULL
CallBackFunc getCallBackFunc(HWND hwnd)
{
	int i;
	for(i = 0; i < g_lenOfHandlers; i++)
	{
		if(g_handlers[i].hwnd == hwnd)
			return g_handlers[i].func;
	}

	return NULL;  //不存在该控件的回调函数
}

//给控件绑定回调函数
	//hwnd 控件的句柄
	//func 回调函数指针
void bindCallBackFunc(HWND hwnd, CallBackFunc func)
{
	if(g_lenOfHandlers < MAX_LEN_FOR_HANDLER)
	{
		g_handlers[g_lenOfHandlers].hwnd = hwnd;
		g_handlers[g_lenOfHandlers].func = func;
		g_lenOfHandlers++;  //长度递增1 
	}
	else
	{//数组超过上限
		exit(0); 
	}
}

//窗口销毁事件
void winOnDestroy()
{
	//释放按钮的资源

	//播放按钮
	releaseBmpResource(g_playBtnBmp1); 
	releaseBmpResource(g_playBtnBmp2);
	free(g_playBtnBmpCur);

	//上一首，下一首按钮
	releaseBmpResource(g_prevBtnBmp);
	releaseBmpResource(g_nextBtnBmp);

	//模式按钮
	releaseBmpResource(g_modeBtnBmp1);
	releaseBmpResource(g_modeBtnBmp2);
	releaseBmpResource(g_modeBtnBmp3);
	free(g_modeBtnBmpCur);
	
	//退出按钮
	releaseBmpResource(g_xBtnBmp);

	//删除内存位图
	DeleteObject(g_hBitmap);


	//释放设备句柄
	DeleteDC(g_hBuffOfMainWin);
	ReleaseDC(g_hWin, g_hdcOfMainWin);

	
	PostQuitMessage(0);  //发送WM_QUIT消息，这样消息循环的才能退出
}

//释放按钮的位图资源
void releaseBmpResource(ButtonBmp* btnBmp)
{
	for(int i = 0; i < 3; i++)
	{
		DeleteObject(btnBmp->bmps[i]);
	}

	free(btnBmp);
}

//鼠标点击测试事件，当点击按住在顶部一定的区域，让窗口拖动
	//hWin 主窗口的句柄
	//lParam 主窗口过程函数中的lParam参数
	//该函数返回值作为主窗口过程函数的返回值返回
LRESULT winOnNcHitTest(HWND hWin, LPARAM lParam)
{
	POINT point;
	RECT rect;

	//鼠标点击的坐标
	point.x = GET_X_LPARAM(lParam);
	point.y = GET_Y_LPARAM(lParam);
	ScreenToClient(hWin, &point);  //讲坐标转换成相对于窗口客户区的坐标

	//获取窗口客户区矩形区域
	GetClientRect(hWin, &rect);

	if(point.y >= rect.top && point.y < rect.top + MOVE_WINDOW_HEIGHT)
	{ //顶部高度为MOVE_WINDOW_HEIGHT的区域用于移动窗口
		return HTCAPTION;
	}
	else
	{ //其它区域认为是客户区域的点击
		return HTCLIENT;
	}
}

//命令事件，处理控件发来的消息
	//hWin 主窗口的句柄
	//message 主窗口过程函数中的message参数
	//wParam 主窗口过程函数中的wParam参数
	//lParam 主窗口过程函数中的lParam参数
	//该函数返回值作为主窗口过程函数的返回值返回
LRESULT winOnCommand(HWND hWin, UINT message, WPARAM wParam, LPARAM lParam)
{
	int code;  //通知码
	HWND hControl;  //控件句柄
	CallBackFunc func;  //控件的事件处理函数

	code = HIWORD(wParam);
	hControl = (HWND)lParam; 

	func = getCallBackFunc(hControl);  //获取该控件的事件处理函数
	if(func != NULL)
		return func(hControl, code);  //调用函数处理控件的事件
	else
		return DefWindowProc(hWin, message, wParam, lParam);
}

//窗口创建事件,获取设备句柄等操作
void winOnCreate(HWND hWin)
{
	g_hWin = hWin;
	g_hdcOfMainWin = GetDC(hWin);
	g_hBuffOfMainWin = CreateCompatibleDC(g_hdcOfMainWin);
	g_hBitmap = CreateCompatibleBitmap(g_hdcOfMainWin, WINDOW_WIDTH, WINDOW_HEIGHT);
}

//WM_NOTIFY事件处理,这里处理列表的事件
	//hWin 主窗口句的柄
	//message 主窗口过程函数中的message参数
	//wParam 主窗口过程函数中的wParam参数
	//lParam 主窗口过程函数中的lParam参数
void winOnNotify(HWND hWin, UINT message, WPARAM wParam, LPARAM lParam)
{
	int code = ((LPNMHDR)lParam)->code;  //通知码
	if(code == NM_CLICK || code == NM_DBLCLK)
	{ //表项被单击或者双击

		LPNMITEMACTIVATE lpInfo = (LPNMITEMACTIVATE)lParam;  //这个指针指向的结构体有点击的项的信息

		//获取这一项歌曲对应的设备id
		wchar_t strId[1024];
		if(lpInfo->iItem >= 0)
		{
			ListView_GetItemText(g_hSongList, lpInfo->iItem, 1, &strId, 1024);  //第lpInfo->iItem行第1列
			WORD id = (WORD)StrToInt(strId);	//字符串转换成数字

			//双击播放
			if(code == NM_DBLCLK)
			{
				stopCurrentMusic();
				playMusic(id); 

                //切换按钮状态
                int status = getStatus();
                switchPlayBtnBmp(g_hPlayBtn, status);
			}
			else
			{ //单击只更改g_select
				g_select = id;
			}
			
		}
	}

}

//退出按钮的事件处理函数
	//hwnd 按钮的句柄
	//code 通知码
LRESULT quitBtnHandler(HWND hwnd, int code)
{
	if(code == BN_CLICKED)
	{  //按钮点击消息
		HWND hParent = GetParent(hwnd);  //父窗口句柄，这个按钮的父窗口是主窗口
		DestroyWindow(hParent);  //销毁整个主窗口
	}

	return 0;  //正常退出 
}

//没有消息时的逻辑，循环获取音乐的进度，更新进度条，及时播放下一首
void progressWhenNoMessage()
{
	if(getStatus() == STATUS_PLAY)
	{
		DWORD pos = getCurrentMusicPos();			//获取进度
		DWORD lenght = getCurrentMusicLenght();		//获取长度

		if(pos == lenght)
		{ //播完了，播放下一首
			if(!playNext())
			{ //调用失败
				//输出调试信息
				wchar_t output[1024];
				wsprintf(output, L"调用出错:playNext()\n");
				OutputDebugString(output);
			}
		}
		else
		{
			double persent = (double)pos * 100 / lenght;	//计算百分值
			drawProgressBar(persent);				//绘制进度条
		}
	}
}

//播放按钮的事件处理函数
	//hwnd 按钮的句柄
	//code 通知码
LRESULT playBtnHandler(HWND hwnd, int code)
{
	if(code == BN_CLICKED)
	{  //点击事件
		int status = getStatus();  //获取播放状态
		if(status == STATUS_PLAY)
		{	//正在播放，点击按钮则为暂停播放
			
			//暂停播放
			if(!pauseCurrentMusic())
			{ //调用失败
				//输出调试信息
				wchar_t output[1024];
				wsprintf(output, L"调用出错:pauseCurrentMusic()\n");
				OutputDebugString(output);
			}

		}
		else if(status == STATUS_PAUSE)
		{  //暂停状态则恢复播放
			//恢复播放
			if(!resumeCurrentMusic())
			{ //调用失败
				//输出调试信息
				wchar_t output[1024];
				wsprintf(output, L"调用出错:resumeCurrentMusic()\n");
				OutputDebugString(output);
			}
		}
		else
		{  //STATUS_STOP 未开始播放，则开始播放
			if(!playMusic(g_select))
			{ //调用失败
				//输出调试信息
				wchar_t output[1024];
				wsprintf(output, L"调用出错:playMusic(%d)\n", g_select);
				OutputDebugString(output);
			}
		}

		//获取操作后的状态
		status = getStatus();

		//切换按钮的图片
		switchPlayBtnBmp(hwnd, status);
	}

	return 0;
}

//播放按钮的事件处理函数
	//hwnd 按钮的句柄
	//code 通知码 
LRESULT modeBtnHandler(HWND hwnd, int code)
{
	if (code == BN_CLICKED)
	{  //点击事件

		//切换播放模式，并返回切换后的模式代表的值
		int mode = switchMode();

		//切换模式按钮的图片
		switchModeBtnBmp(hwnd, mode);
	}

	return 0;
}

//切换下一首按钮的事件处理函数
	//hwnd 按钮的句柄
	//code 通知码 
LRESULT nextBtnHandler(HWND hwnd, int code)
{
	if (code == BN_CLICKED)
	{  //点击事件

		//停止当前歌曲播放
		if(stopCurrentMusic())
		{ //先停止当前歌曲的播放
			//播放下一首歌
			playNext();

            //更新播放按钮的状态
            int status = getStatus();
            switchPlayBtnBmp(g_hPlayBtn, status);
		}
		else
		{ //停止失败
			//输出调试信息
			wchar_t output[1024];
			wsprintf(output, L"调用出错:stopCurrentMusic\n");
			OutputDebugString(output);
		}
	}

	return 0;
}

//切换上一首按钮的事件处理函数
	//hwnd 按钮的句柄
	//code 通知码 
LRESULT prevBtnHandler(HWND hwnd, int code)
{
	if (code == BN_CLICKED)
	{  //点击事件

		//停止当前歌曲播放
		if(stopCurrentMusic())
		{ //先停止当前歌曲的播放
			//播放上一首歌
			playPrev();
            //更新播放按钮的状态
            int status = getStatus();
            switchPlayBtnBmp(g_hPlayBtn, status);
		}
		else
		{ //停止失败
			//输出调试信息
			wchar_t output[1024];
			wsprintf(output, L"调用出错:stopCurrentMusic\n");
			OutputDebugString(output);
		}
	}

	return 0;
}
