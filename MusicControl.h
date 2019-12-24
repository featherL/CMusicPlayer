#pragma once

//win32api
#include <Windows.h>

//路径操作的函数
#include <Shlwapi.h> 
#pragma comment(lib,"shlwapi.lib")

//标准库，要使用malloc函数
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
	DWORD length;				//歌曲的长度
	wchar_t name[MAX_PATH];		//歌曲的名字
	struct MusicNode* pre;		//指向上一个节点
	struct MusicNode* next;		//指向下一个节点
}MusicNode;

//扫描目录下的mp3文件，存入相关信息到g_headOfList指向的链表中
	//directory 目录的路径，参数不保证正确性,函数内部判断
	//若至少有一首歌曲成功打开，返回1，否则返回0
int openDirectory(wchar_t *directory);

//-------------------------------------------
//遍历链表用的回调函数的类型
	//node 遍历到的节点
	//回调函数返回值为1表示继续遍历，否则停止遍历
typedef int (*TraverseCallBack)(MusicNode* node);

//遍历歌曲链表，对每个节点调用回调函数
	//callBackFunc 回调函数
void traverse(TraverseCallBack callBackFunc);

//-------------------------------------------
//添加节点到某节点后面
	//node	要插入到哪个节点后面，这个参数不能为NULL
	//newNode 添加的节点
void appendNode(MusicNode* node, MusicNode*newNode);

//释放头指针指向的链表的所有节点
	//list 指向头指针变量的指针(指针的指针！指针的指针！指针的指针!)
void freeList(MusicNode** list);

//获取当前的状态
	//返回值为当前状态，取值为STATUS_STOP、STATUS_PAUSE、STATUS_PLAY
int getStatus();

//播放音乐
	//deviceId 设备id
	//播放成功返回1，否则返回0
int playMusic(WORD deviceId);

//播放下一首音乐
	//成功返回1，否则返回0
int playNext();

//播放上一首音乐
	//成功返回1，否则返回0
int playPrev();

//循环切换播放模式
	//返回切换后的模式
int switchMode();

//暂停当前歌曲播放
	//成功返回1，否则返回0
int pauseCurrentMusic();

//恢复当前歌曲播放
	//成功返回1，否则返回0
int resumeCurrentMusic();

//获取当前歌曲播放进度
	//返回值当前播放的位置，若当前无歌曲播放或暂停，则返回0
DWORD getCurrentMusicPos();

//获取当前歌曲的长度
	//返回值为当前歌曲的长度，若当前无歌曲播放或者暂停，则返回1
DWORD getCurrentMusicLenght();

//停止当前歌曲播放
	//成功返回1，否则返回0
int stopCurrentMusic();


