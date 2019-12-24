#include "MusicControl.h"

//static让下面的全局变量仅在这个文件可见
static MusicNode* g_headOfList = NULL;			//所有歌曲的链表的头指针
static MusicNode* g_curNode = NULL;				//当前正在播放的歌曲
static int g_allModes[] = { MODE_LOOP, MODE_ORDER, MODE_RANDOWM };	//所有切换模式
static int g_sizeOfAllModes = 3;				//g_allModes数组元素的个数
static int g_modeIndex = 0;						//g_allModes数组的下标，表示当前模式，初始为循环播放模式
static int g_status = STATUS_STOP;				//当前的状态

//获取当前歌曲的长度
	//返回值为当前歌曲的长度，若当前无歌曲播放或者暂停，则返回1
DWORD getCurrentMusicLenght()
{
	if(g_curNode != NULL)
	{
		return g_curNode->length;
	}

	return 1;	//不能返回0，因为这个数要用作除数
}

//获取当前歌曲播放进度
	//返回值当前播放的位置，若当前无歌曲播放或暂停，则返回0
DWORD getCurrentMusicPos()
{
	DWORD pos = 0;
	if(g_curNode != NULL)
	{
		//获取当前播放的位置
		MCI_STATUS_PARMS mciStatusParms;
		mciStatusParms.dwItem = MCI_STATUS_POSITION;

		if(0 == mciSendCommand(g_curNode->deviceId, MCI_STATUS, MCI_STATUS_ITEM, &mciStatusParms))
		{
			pos = mciStatusParms.dwReturn;  //当前位置
		}
	}

	return pos;
}

//暂停当前歌曲播放
	//成功返回1，否则返回0
int pauseCurrentMusic()
{
	if(g_curNode != NULL && g_status == STATUS_PLAY)
	{
		MCI_GENERIC_PARMS mciPause;
		if(0 == mciSendCommand(g_curNode->deviceId, MCI_PAUSE, 0, (DWORD)&mciPause))
		{
			g_status = STATUS_PAUSE;    //设置状态为暂停
			return 1;					//成功
		}
	}

	return 0;		//失败
}

//恢复当前歌曲播放
	//成功返回1，否则返回0
int resumeCurrentMusic()
{
	if(g_curNode != NULL && g_status == STATUS_PAUSE)
	{
		MCI_GENERIC_PARMS mciResume;
		if(0 == mciSendCommand(g_curNode->deviceId, MCI_RESUME, 0, &mciResume))
		{
			g_status = STATUS_PLAY;		//设置状态为正在播放
			return 1;					//成功
		}
	}

	return 0;		//失败
}

//释放头指针指向的链表的所有节点
	//list 指向头指针变量的指针(指针的指针！指针的指针！指针的指针!)
void freeList(MusicNode** list)
{
	MusicNode* tmp;
	MusicNode* cur = *list;
	if(cur != NULL)
	{
		do
		{
			tmp = cur->next;	//保存下一个节点的指针
			free(cur);
			cur = tmp;
		} while(cur != *list);

		*list = NULL;			//头指针置为NULL
	}
}


//播放音乐
	//deviceId 设备id
	//播放成功返回1，否则返回0
int playMusic(WORD deviceId)
{
	MusicNode* cur;
	int flag = 0;
	cur = g_headOfList;
	
	if(cur != NULL)
	{
		do
		{	//找到deviceId对应的节点
			if(cur->deviceId == deviceId)
			{
				flag = 1;
				break;
			}
			cur = cur->next;
		} while(cur != g_headOfList);

		if(flag == 1)
		{
			MCI_PLAY_PARMS mciPlay;
			if(0 == mciSendCommand(cur->deviceId, MCI_PLAY, 0, (DWORD)&mciPlay))
			{  //播放成功
				g_curNode = cur;			//保存当前播放的节点
				g_status = STATUS_PLAY;		//更改当前状态
				return 1;
			}
		}
	}

	return 0;
}

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

				//获取歌曲文件的长度
				MCI_STATUS_PARMS mciStatusParms;
				mciStatusParms.dwItem = MCI_STATUS_LENGTH;

				if(0 == mciSendCommand(mciOpen.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)&mciStatusParms))
				{ 
					ret = 1;  //只要有一首歌曲打开成功，函数的返回值就为1

					//创建一个节点插入到链表
					newNode = (MusicNode*)malloc(sizeof(MusicNode));

					newNode->length = mciStatusParms.dwReturn;  //保存歌曲长度
					lstrcpyn(newNode->name, fileInfo.cFileName, MAX_PATH);  //保存歌曲名字
					newNode->deviceId = mciOpen.wDeviceID;		//设备id，用于操作歌曲的播放，暂停等

					//插入到链表
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

//获取当前的状态
	//返回值为当前状态，取值为STATUS_STOP、STATUS_PAUSE、STATUS_PLAY
int getStatus()
{
	return g_status;		//当前状态保存在了静态全局变量g_status中
}

//播放下一首音乐
	//成功返回1，否则返回0
int playNext()
{
	MusicNode* cur = g_curNode;            //获取当前的结点指针


	if (cur->next != NULL)
	{
		cur = cur->next;
		MCI_PLAY_PARMS mciPlay;
		if (0 == mciSendCommand(cur->deviceId, MCI_PLAY, 0, (DWORD)&mciPlay))
		{
			g_curNode = cur;
			return 1;
		}
	}
	

	return 0;
}

//循环切换播放模式
	//返回切换后的模式
int switchMode()
{
	g_modeIndex = (g_modeIndex + 1) % g_sizeOfAllModes;  //循环更改播放模式

	return g_allModes[g_modeIndex];		//返回模式
}

//遍历链表用的回调函数的类型
	//node 遍历到的节点
	//回调函数返回值为1表示继续遍历，否则停止遍历
typedef int (*TraverseCallBack)(MusicNode* node);

//遍历歌曲链表，对每个节点调用回调函数
	//callBackFunc 回调函数
void traverse(TraverseCallBack callBackFunc)
{
	MusicNode* cur;
	cur = g_headOfList;
	if (cur != NULL)
	{   
		do
		{
			if (!callBackFunc(cur)) //调用回调函数
			{
				break;
			}
			cur = cur->next;
		} while (cur != g_headOfList);
	}	
}
