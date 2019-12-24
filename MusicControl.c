#include "MusicControl.h"

//static�������ȫ�ֱ�����������ļ��ɼ�
static MusicNode* g_headOfList = NULL;			//���и����������ͷָ��
static MusicNode* g_headOfPlaying = NULL;		//���Ŷ��������ͷָ��
static MusicNode* g_curNode = NULL;			//��ǰ���ڲ��ŵĸ���
static int g_mode = MODE_ORDER;					//��ʼΪ˳�򲥷�ģʽ
static int g_status = STATUS_STOP;				//��ǰ��״̬

//�ͷ�ͷָ��ָ�����������нڵ�
	//list ָ��ͷָ�������ָ��(ָ���ָ�룡ָ���ָ�룡ָ���ָ��!)
void freeList(MusicNode** list)
{
	MusicNode* tmp;
	MusicNode* cur = *list;
	if(cur != NULL)
	{
		do
		{
			tmp = cur->next;	//������һ���ڵ��ָ��
			free(cur);
			cur = tmp;
		} while(cur != *list);

		*list = NULL;			//ͷָ����ΪNULL
	}
}


//��������
	//deviceId �豸id
int playMusic(WORD deviceId)
{
	MusicNode* cur;
	int flag = 0;
	cur = g_headOfPlaying;
	do
	{
		if (cur->deviceId == deviceId) {
			flag = 1;
			break;
		}
		cur = cur->next;
	} while (cur != g_headOfPlaying);
	if(flag == 1){
		MCI_PLAY_PARMS mciPlay;
		if (0 == mciSendCommand(cur->deviceId, MCI_PLAY, 0, (DWORD)&mciPlay))
		{
			g_curNode = cur;
			return 1;
		}
	}
	return 0;
}

//ɨ��Ŀ¼�µ�mp3�ļ������������Ϣ��g_headOfListָ���������
	//directory Ŀ¼��·������������֤��ȷ��,�����ڲ��ж�
	//��������һ�׸����ɹ��򿪣�����1�����򷵻�0
int openDirectory(wchar_t* directory)
{
	int ret = 0;		//����ֵ
	
	wchar_t dirFullPath[MAX_PATH];  //�洢Ŀ¼�ľ���·��
	wchar_t *fileName;					  //���directory���ļ�·���������ָ��һ���ַ���Ϊ�ļ���

	//��ȡdirectory�ľ���·������ȡ���ľ���·��ĩβû�зָ���
	GetFullPathName(directory, MAX_PATH, dirFullPath, &fileName);

	wchar_t* match[MAX_PATH];		//����ƥ��mp3�ļ���·��
	PathCombine(match, dirFullPath, L"*.mp3");  //ƴ��·����ƴ�ӳ�dirFullPath\\*.mp3

	WIN32_FIND_DATA fileInfo;		//���������ļ��Ľṹ��
	HANDLE handle;					//���������ļ��ľ��

	if((handle = FindFirstFile(match, &fileInfo)) != -1)
	{  //���óɹ�
		do
		{
			//mp3�ļ���·��
			wchar_t musicPath[MAX_PATH];
			PathCombine(musicPath, dirFullPath, fileInfo.cFileName);

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

//��ȡ��ǰ��״̬�����š���ͣ��ֹͣ
int getStatus()
{
	return g_status;		//��ǰ״̬�������˾�̬ȫ�ֱ���g_status��
}

//������һ��
int playNext()
{
	MusicNode* cur = g_curNode;            //��ȡ��ǰ�Ľ��ָ��


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

//���ò���ģʽ
void setMode(int mode)
{
	g_mode = mode;
}

//��õ�ǰģʽ
int getMode()
{
	return g_mode;
}

