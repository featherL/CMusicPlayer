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

//三个状态：停止，暂停，播放
#define STATUS_STOP 1
#define STATUS_PAUSE 2
#define STATUS_PLAY 3


//-----------------------------------
typedef struct MusicNode
{
	WORD deviceId;				//打开的音乐文件的设备id
	wchar_t name[MAX_PATH];		//歌曲的名字
	struct MusicNode* pre;		//指向上一个节点
	struct MusicNode* next;		//指向下一个节点
}MusicNode;

//扫描目录下的mp3文件，存入相关信息到g_headOfList指向的链表中
	//directory 目录的路径，参数不保证正确性,函数内部判断
	//若至少有一首歌曲成功打开，返回1，否则返回0
int openDirectory(wchar_t *directory);


//添加节点到某节点后面
	//node	要插入到哪个节点后面，这个参数不能为NULL
	//newNode 添加的节点
void appendNode(MusicNode* node, MusicNode*newNode);

//释放头指针指向的链表的所有节点
	//list 指向头指针变量的指针(指针的指针！指针的指针！指针的指针!)
void freeList(MusicNode** list);

//获取当前的状态，播放、暂停、停止
int getStatus();

//播放音乐
	//deviceId 设备id
int playMusic(WORD deviceId);

//播放下一首音乐
	//成功返回1，否则返回0
int playNext();
