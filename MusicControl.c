#include "MusicControl.h"

MusicNode* g_headOfList = NULL;			//���и����������ͷָ��
MusicNode* g_headOfPlaying = NULL;		//���Ŷ��������ͷָ��
MusicNode* g_curNode = NULL;			//��ǰ���ڲ��ŵĸ���


//ɨ��Ŀ¼�µ�mp3�ļ������������Ϣ��g_headOfListָ���������
	//directory Ŀ¼��·������������֤��ȷ��,�����ڲ��ж�
	//��������һ�׸����ɹ��򿪣�����1�����򷵻�0
int openDirectory(wchar_t* directory)
{
	int ret = 0;		//����ֵ
	
	wchar_t directoryFullPath[MAX_PATH];  //�洢Ŀ¼�ľ���·��
	wchar_t *fileName;					  //���directory���ļ�·���������ָ��һ���ַ���Ϊ�ļ���

	//��ȡdirectory�ľ���·������ȡ���ľ���·��ĩβû�зָ���
	GetFullPathName(directory, MAX_PATH, directoryFullPath, &fileName);

	wchar_t* match[MAX_PATH];		//����ƥ��mp3�ļ���·��
	PathCombine(match, directoryFullPath, L"*.mp3");

	WIN32_FIND_DATA fileInfo;		//���������ļ��Ľṹ��
	HANDLE handle;					//���������ļ��ľ��

	if((handle = FindFirstFile(match, &fileInfo)) != -1)
	{  //���óɹ�
		do
		{
			//mp3�ļ���·��
			wchar_t musicPath[MAX_PATH];
			PathCombine(musicPath, directoryFullPath, fileInfo.cFileName);

			//��mp3�ļ�
			MCI_OPEN_PARMS mciOpen;
			mciOpen.lpstrElementName = musicPath;

			MusicNode* newNode;
			if(0 == mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&mciOpen))
			{ //�򿪳ɹ�
				ret = 1;  //ֻҪ��һ�׸����򿪳ɹ��������ķ���ֵ��Ϊ1
				
				//����һ���ڵ���뵽����
				newNode = (MusicNode*)malloc(sizeof(MusicNode));
				lstrcpyn(newNode->name, fileInfo.cFileName, MAX_PATH);  //�����������
				newNode->deviceId = mciOpen.wDeviceID;		//�豸id�����ڲ��������Ĳ��ţ���ͣ��
				
				if(g_headOfList == NULL)
				{  //��һ�β���ڵ�
					g_headOfList = newNode;
					
					//ѭ������
					newNode->next = newNode;
					newNode->pre = newNode;
				}
				else
				{  
					MusicNode* tail = g_headOfList->pre;	//����β��
					appendNode(tail, newNode);				//���ӵ�����β��
				}
			}
		} while(FindNextFile(handle, &fileInfo));
	}

	return ret;
}

//��ӽڵ㵽ĳ�ڵ����
	//node	Ҫ���뵽�ĸ��ڵ���棬�����������ΪNULL
	//newNode ��ӵĽڵ�
void appendNode(MusicNode* node, MusicNode* newNode)
{
	MusicNode* nextNode = node->next;	//������һ���ڵ��ָ��
	
	//ƴ��node��newNode
	node->next = newNode;
	newNode->pre = node;

	//ƴ��newNode��nextNode
	newNode->next = nextNode;
	nextNode->pre = newNode;
}