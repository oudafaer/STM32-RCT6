#ifndef __IR_H
#define __IR_H 
#include "sys.h"   

  
#define RDATA 	PAin(1)	 	//�������������

//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0
#define REMOTE_ID 0      		   

extern u8 RmtCnt;			//�������µĴ���

void IR_Init(void);    	//���⴫��������ͷ���ų�ʼ��
u8 IR_Scan(void);	    
#endif
