/************************************************************************
* ��Ȩ����  (c)2008,   RunShan
* �ļ����ƣ� Log_in.c

* ����ժҪ��
*     ���ļ�ʵ�ֹ��ڵ�¼����ͳ�ʼ���Ĺ��ܡ�
* ��ʷ��¼��
*     �������ڣ�2013-08-05   �޸��ˣ�����ľ
*************************************************************************/
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "..\\Log_in\Log_in.h"
char acName[10] = {0};// ��ŵ�½�û���


void JR_EmptyRaw(int r1,int r2)
{
  int i,j;
  for (i = r1;i <= r2;i++)
  {
    JR_SetCursor(i,0);
    for (j=0;j<=80;j++)
    printf("%c",' ');// �ÿո������ÿ��
  }

}




void JR_SetCursor(int x, int y)
{
	
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {y, x};
    SetConsoleCursorPosition(hOut, pos);
}



int Log_in(pList head)
{  	 
     int a,b,c;
	 char time[10] = {0};
	 pList pt;
	 struct staff_t *data;
	 char name[10] = {0};// ���������û���
	 char psd[8] = {0}; // ������������
     char role[3][10] ={"����Ա","����","����Ա"};
     Ordernum_get(time,NULL);
	 sscanf(time,"%4d%2d%2d",&a,&b,&c);
	 while(1)
 { 
      system("cls");
	  printf("\n\n\n\t\t\t׿Խ��˻���¼����\n\n");
	  printf("\t\t\t%-19s","�û�����");
	  printf("(10λ)");
	  printf("\n\n\t\t\t%-19s","���룺");
	  printf("(6λ)");
      printf("\n\n\n\n\t\t\t\t\t   ѧ    Ա������ľ\n");
	  printf("\t\t\t\t\t   ��ǰ���ڣ�%4d-%02d-%02d",a,b,c);

	  JR_SetCursor(5,32);// ��궨λ���û��������λ��
	  glb_putString(name,0,0,10,1);// �������뺯����ֻ��������ĸ
	  JR_SetCursor(7,30);// ��λ�����������λ��
      glb_putString(psd,'0','9',6,2);//ֻ���������� 
      pt = head->pNext;
		while(pt)
	{
		data = (struct staff_t*)(pt->pData);
		if ((strcmp(data->acName,name) == 0)&&(strcmp(data->psd,psd) == 0))
		{		
		   strcpy(acName,data->acName); // �洢��½�û���
		   printf("\n\n\t\t\t��¼�ɹ������Ϊ��%s�������������...",role[data->role]);
		   getch();	  
		   return data->role;// ����Ա����ɫ��־
		}
           pt = pt->pNext;
	}
           printf("\n\n\t\t\t��������������������룬�����������...");
		   memset(psd,0,sizeof(char));
           getch();
   }
         
}
				



void Login_init(FILE *fp,pList head)
{	
	struct staff_t *data;
	data = (struct staff_t *)malloc(sizeof(struct staff_t));
	data->acNO = 1000;// ��ʼ����������Ա�Ĳ���
	strcpy(data->acName,"admin");
	strcpy(data->psd,"123456");
	data->role = 2;// ����Ա���
	data->flag = 1;
	List_add(head,data);// ��ӵ�����
	File_write(fp,head,sizeof(struct staff_t),0);// д���ļ�   

}
