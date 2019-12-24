#pragma once

#include <Windows.h>

//路径操作的函数
#include <Shlwapi.h> 
#pragma comment(lib,"shlwapi.lib")

#include <stdlib.h>

//mci接口
#include <mmsystem.h>  
#pragma comment (lib, "winmm.lib")

//宏定义
//顺序播放、循环播放、随机播放
#define MODE_ORDER 1
#define MODE_LOOP 2
#define MODE_RANDOWM 3



//-----------------------------------
typedef struct MusicNode
{
	WORD deviceId;				//打开的音乐文件的设备id
	wchar_t name[MAX_PATH];		//歌曲的名字
	struct MusicNode* pre;		//指向上一个节点
	struct MusicNode* next;		//指向下一个节点
}MusicNode;


extern MusicNode* g_headOfList;			//所有歌曲的链表的头指针
extern MusicNode* g_headOfPlaying;		//播放队列链表的头指针
extern MusicNode* g_curNode;			//当前正在播放的歌曲

//扫描目录下的mp3文件，存入相关信息到g_headOfList指向的链表中
	//directory 目录的路径，参数不保证正确性,函数内部判断
	//若至少有一首歌曲成功打开，返回1，否则返回0
int openDirectory(wchar_t *directory);


//添加节点到某节点后面
	//node	要插入到哪个节点后面，这个参数不能为NULL
	//newNode 添加的节点
void appendNode(MusicNode* node, MusicNode*newNode);
