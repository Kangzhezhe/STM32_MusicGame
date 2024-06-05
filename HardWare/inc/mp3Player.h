#ifndef __MP3PLAYER_H__
#define __MP3PLAYER_H__

#include "main.h"

/* ״̬ */
enum
{
	STA_IDLE = 0,	/* ����״̬ */
	STA_PLAYING,	/* ����״̬ */
	STA_ERR,			/*  error  */
    STA_SUSPEND
};

typedef struct
{
	uint8_t  ucVolume;		/* ��ǰ�������� */
	uint8_t  ucStatus;		/* ״̬��0��ʾ������1��ʾ�����У�2 ���� */	
	uint32_t ucFreq;			/* ����Ƶ�� */
}MP3_TYPE;	

void mp3PlayerDemo(const char *mp3file);
void MP3_Playing();
void MP3_decode_file(const char *mp3file);
void MP3_decoder_Init(void);
void MP3_decoder_Free();
u32 MP3_Get_duration();
void MP3_Set_volume(int vol);
void MP3_suspend();
void MP3_resume();
#endif  /* __MP3PLAYER_H__   */
