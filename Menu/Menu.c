/************************************************************************
* ��Ȩ����  (c)2008,   RunShan
* �ļ����ƣ� Menu.c

* ����ժҪ��
*     ���ļ�ʵ�ֹ��ڲ��׵���ɾ�Ĳ鹦�ܡ�
* ��ʷ��¼��
*     �������ڣ�2013-08-05   �޸��ˣ�����ľ
*************************************************************************/
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "..\\Menu\Menu.h"

void Menu_print(pList pt)
{   
	static int k = 0;
	struct Menu_t *pd;
	pd = (struct Menu_t *)(pt->pData);
	if (k == 0)
	{
		system("cls");
		printf("\t\t%-10s%-11s%-12s\n","�˱��","����","�۸�");
		k = 1;
	}
	printf("\t\t%-10s%-11s%-12d\n",pd->num,pd->name,pd->price);
	if (pt->pNext == NULL)
		k = 0;
}



void *Menu_add(void *data)
{ 	
	char str[8] = {0};
	struct Menu_t *pData,*ps;
	pData = (struct Menu_t *)malloc(sizeof(struct Menu_t));
	ps = (struct Menu_t *)data;
	if (data == NULL)
	{  
		system("cls");
		strcpy(pData->num,"10000");	
	}
	else
	{
		glb_putString(ps->num,'0','9',5,2);
		strcpy(pData->num,ps->num);
	}
	printf("\n������Ҫ���ӵĲ�����");
	glb_putString(pData->name,0,0,14,1);
	printf("������Ҫ���ӵļ۸�");
    pData->price = glb_putString(str,'0','9',2,2);
	printf("\n");
    return pData;
}





int Menu_del(pList pL)
{ 
	struct Menu_t *pt;
	static int k = 0;
	static int id = 0;
	static char str[8] = {0};
	if (k == 0) 
	{
		printf("������Ҫɾ���Ĳ˱��(5λ)��");
		glb_putString(str,'0','9',5,2);
		k = 1;
	}
	pt = (struct Menu_t *)(pL->pData);
	if (strcmp(pt->num,str) == 0)
	{
		memset(str,0,sizeof(char));
		k = 0;
		return 1;
	}
	else 
	{
		if (pL->pNext == NULL)
		{   
			memset(str,0,sizeof(char));
			k = 0;
		}
		return 0;	  
	}
}




int Menu_updata(pList pL)
{
	struct Menu_t *pt;
    static int k = 0;
	static char str[8] = {0};
	if (k == 0)
	{
		printf("������Ҫ�޸ĵĲ˱��(5λ)��");
		glb_putString(str,'0','9',5,2);
		k = 1;
	}
	pt = (struct Menu_t *)(pL->pData);
	if (strcmp(pt->num,str) == 0)
	{
		memset(str,0,sizeof(char));
		printf("\n�������������");
		glb_putString(pt->name,0,0,14,1);
		printf("��������۸�");
		pt->price = glb_putString(str,'0','9',2,2);
		memset(str,0,sizeof(char));
		k = 0;
		return 1;		
	}
	
	else 
	{
        if (pL->pNext == NULL)
        {
			memset(str,0,sizeof(char));
			k = 0;
        }
			return 0;
	}
		
}




void Menu_search(pList head)
{
	char str[8] = {0};
	pList ps,pL;
	struct Menu_t *data;
	pL = List_init(NULL);
	ps = head->pNext;
	if(ps == NULL)
	{
		system("cls");
		printf("\nδ���в�����Ϣ��������ӣ�\n");
		return;
	}
	system("cls");
	printf("\n\t\t\t(1) ȫ��");
	printf("\n\n\t\t\t(2) ���");
	printf("\n\n\t\t\t������Ҫ��ѯ��������");
	if(glb_putString(NULL,'1','2',1,2) == 1)
	{
        List_print(head,Menu_print);
		return;
	}
	printf("\n\n\t\t\t������Ҫ��ѯ�Ĳ˱��(5λ)��");
	glb_putString(str,'0','9',5,2);
	while(ps != NULL)
	{
		data = (struct Menu_t *)(ps->pData);
		if (strcmp(data->num,str) == 0)
		{
			List_add(pL,data);
			break;
		}		
		ps = ps->pNext;
	}
	if (ps != NULL)
	{  
          List_print(pL,Menu_print);  
	}
	else 
	{
        printf("\n\n��������δ��ѯ�������Ϣ");	
	}	      
} 


