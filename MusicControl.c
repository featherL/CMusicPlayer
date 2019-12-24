#include "MusicControl.h"

MusicNode* g_headOfList = NULL;			//所有歌曲的链表的头指针
MusicNode* g_headOfPlaying = NULL;		//播放队列链表的头指针
MusicNode* g_curNode = NULL;			//当前正在播放的歌曲


//扫描目录下的mp3文件，存入相关信息到g_headOfList指向的链表中
	//directory 目录的路径，参数不保证正确性,函数内部判断
	//若至少有一首歌曲成功打开，返回1，否则返回0
int openDirectory(wchar_t* directory)
{
	int ret = 0;		//返回值
	
	wchar_t dirFullPath[MAX_PATH];  //存储目录的绝对路径
	wchar_t *fileName;					  //如果directory是文件路径，则这个指向一个字符串为文件名

	//获取directory的绝对路径，获取到的绝对路径末尾没有分隔符
	GetFullPathName(directory, MAX_PATH, dirFullPath, &fileName);

	wchar_t* match[MAX_PATH];		//用来匹配mp3文件的路径
	PathCombine(match, dirFullPath, L"*.mp3");  //拼接路径，拼接成dirFullPath\\*.mp3

	WIN32_FIND_DATA fileInfo;		//用来查找文件的结构体
	HANDLE handle;					//用来查找文件的句柄

	if((handle = FindFirstFile(match, &fileInfo)) != -1)
	{  //调用成功
		do
		{
			//mp3文件的路径
			wchar_t musicPath[MAX_PATH];
			PathCombine(musicPath, dirFullPath, fileInfo.cFileName);

			//打开mp3文件
			MCI_OPEN_PARMS mciOpen;
			mciOpen.lpstrElementName = musicPath;

			MusicNode* newNode;
			if(0 == mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&mciOpen))
			{ //打开成功
				ret = 1;  //只要有一首歌曲打开成功，函数的返回值就为1
				
				//创建一个节点插入到链表
				newNode = (MusicNode*)malloc(sizeof(MusicNode));
				lstrcpyn(newNode->name, fileInfo.cFileName, MAX_PATH);  //保存歌曲名字
				newNode->deviceId = mciOpen.wDeviceID;		//设备id，用于操作歌曲的播放，暂停等
				
				if(g_headOfList == NULL)
				{  //第一次插入节点
					g_headOfList = newNode;
					
					//循环链表
					newNode->next = newNode;
					newNode->pre = newNode;
				}
				else
				{  
					MusicNode* tail = g_headOfList->pre;	//链表尾部
					appendNode(tail, newNode);				//附加到链表尾部
				}
			}
		} while(FindNextFile(handle, &fileInfo));
	}

	return ret;
}

//添加节点到某节点后面
	//node	要插入到哪个节点后面，这个参数不能为NULL
	//newNode 添加的节点
void appendNode(MusicNode* node, MusicNode* newNode)
{
	MusicNode* nextNode = node->next;	//保存下一个节点的指针
	
	//拼接node和newNode
	node->next = newNode;
	newNode->pre = node;

	//拼接newNode和nextNode
	newNode->next = nextNode;
	nextNode->pre = newNode;
}