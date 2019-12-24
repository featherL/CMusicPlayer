#include "MusicControl.h"

//static�������ȫ�ֱ�����������ļ��ɼ�
static MusicNode* g_headOfList = NULL;			//���и����������ͷָ��
static MusicNode* g_curNode = NULL;				//��ǰ���ڲ��ŵĸ���
static int g_allModes[] = { MODE_LOOP, MODE_ORDER, MODE_RANDOWM };	//�����л�ģʽ
static int g_sizeOfAllModes = 3;				//g_allModes����Ԫ�صĸ���
static int g_modeIndex = 0;						//g_allModes������±꣬��ʾ��ǰģʽ����ʼΪѭ������ģʽ
static int g_status = STATUS_STOP;				//��ǰ��״̬

//��ȡ��ǰ�����ĳ���
	//����ֵΪ��ǰ�����ĳ��ȣ�����ǰ�޸������Ż�����ͣ���򷵻�1
DWORD getCurrentMusicLenght()
{
	if(g_curNode != NULL)
	{
		return g_curNode->length;
	}

	return 1;	//���ܷ���0����Ϊ�����Ҫ��������
}

//��ȡ��ǰ�������Ž���
	//����ֵ��ǰ���ŵ�λ�ã�����ǰ�޸������Ż���ͣ���򷵻�0
DWORD getCurrentMusicPos()
{
	DWORD pos = 0;
	if(g_curNode != NULL)
	{
		//��ȡ��ǰ���ŵ�λ��
		MCI_STATUS_PARMS mciStatusParms;
		mciStatusParms.dwItem = MCI_STATUS_POSITION;

		if(0 == mciSendCommand(g_curNode->deviceId, MCI_STATUS, MCI_STATUS_ITEM, &mciStatusParms))
		{
			pos = mciStatusParms.dwReturn;  //��ǰλ��
		}
	}

	return pos;
}

//��ͣ��ǰ��������
	//�ɹ�����1�����򷵻�0
int pauseCurrentMusic()
{
	if(g_curNode != NULL && g_status == STATUS_PLAY)
	{
		MCI_GENERIC_PARMS mciPause;
		if(0 == mciSendCommand(g_curNode->deviceId, MCI_PAUSE, 0, (DWORD)&mciPause))
		{
			g_status = STATUS_PAUSE;    //����״̬Ϊ��ͣ
			return 1;					//�ɹ�
		}
	}

	return 0;		//ʧ��
}

//�ָ���ǰ��������
	//�ɹ�����1�����򷵻�0
int resumeCurrentMusic()
{
	if(g_curNode != NULL && g_status == STATUS_PAUSE)
	{
		MCI_GENERIC_PARMS mciResume;
		if(0 == mciSendCommand(g_curNode->deviceId, MCI_RESUME, 0, &mciResume))
		{
			g_status = STATUS_PLAY;		//����״̬Ϊ���ڲ���
			return 1;					//�ɹ�
		}
	}

	return 0;		//ʧ��
}

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
	//���ųɹ�����1�����򷵻�0
int playMusic(WORD deviceId)
{
	MusicNode* cur;
	int flag = 0;
	cur = g_headOfList;
	
	if(cur != NULL)
	{
		do
		{	//�ҵ�deviceId��Ӧ�Ľڵ�
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
			{  //���ųɹ�
				g_curNode = cur;			//���浱ǰ���ŵĽڵ�
				g_status = STATUS_PLAY;		//���ĵ�ǰ״̬
				return 1;
			}
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

				//��ȡ�����ļ��ĳ���
				MCI_STATUS_PARMS mciStatusParms;
				mciStatusParms.dwItem = MCI_STATUS_LENGTH;

				if(0 == mciSendCommand(mciOpen.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)&mciStatusParms))
				{ 
					ret = 1;  //ֻҪ��һ�׸����򿪳ɹ��������ķ���ֵ��Ϊ1

					//����һ���ڵ���뵽����
					newNode = (MusicNode*)malloc(sizeof(MusicNode));

					newNode->length = mciStatusParms.dwReturn;  //�����������
					lstrcpyn(newNode->name, fileInfo.cFileName, MAX_PATH);  //�����������
					newNode->deviceId = mciOpen.wDeviceID;		//�豸id�����ڲ��������Ĳ��ţ���ͣ��

					//���뵽����
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

//��ȡ��ǰ��״̬
	//����ֵΪ��ǰ״̬��ȡֵΪSTATUS_STOP��STATUS_PAUSE��STATUS_PLAY
int getStatus()
{
	return g_status;		//��ǰ״̬�������˾�̬ȫ�ֱ���g_status��
}

//������һ������
	//�ɹ�����1�����򷵻�0
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

//������һ������
	//�ɹ�����1�����򷵻�0
int playPrev()
{
	MusicNode* cur = g_curNode;            //��ȡ��ǰ�Ľ��ָ��


	if (cur->pre != NULL)
	{
		cur = cur->pre;
		MCI_PLAY_PARMS mciPlay;
		if (0 == mciSendCommand(cur->deviceId, MCI_PLAY, 0, (DWORD)&mciPlay))
		{
			g_curNode = cur;
			return 1;
		}
	}


	return 0;
}

//ѭ���л�����ģʽ
	//�����л����ģʽ
int switchMode()
{
	g_modeIndex = (g_modeIndex + 1) % g_sizeOfAllModes;  //ѭ�����Ĳ���ģʽ

	return g_allModes[g_modeIndex];		//����ģʽ
}

//���������õĻص�����������
	//node �������Ľڵ�
	//�ص���������ֵΪ1��ʾ��������������ֹͣ����
typedef int (*TraverseCallBack)(MusicNode* node);

//��������������ÿ���ڵ���ûص�����
	//callBackFunc �ص�����
void traverse(TraverseCallBack callBackFunc)
{
	MusicNode* cur;
	cur = g_headOfList;
	if (cur != NULL)
	{   
		do
		{
			if (!callBackFunc(cur)) //���ûص�����
			{
				break;
			}
			cur = cur->next;
		} while (cur != g_headOfList);
	}	
}
