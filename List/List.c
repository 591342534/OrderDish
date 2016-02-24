/************************************************************************
* ��Ȩ����  (c)2008,   RunShan
* �ļ����ƣ� List.c

* ����ժҪ��
*     ���ļ�ʵ�ֹ���������������Ĺ��ܡ�
* ��ʷ��¼��
*     �������ڣ�2013-08-05   �޸��ˣ�����ľ
*************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "..\\List\List.h"


 pList List_init(void * data)
{  
	pList head;
	head = (pList) malloc(sizeof(struct List));// ������ռ�
	if (head == NULL)
	{
		printf("Memory error.\n");
		return NULL;
	}
	memset(head,0,sizeof(struct List));// ����
	head->pData = data;// ������ֵ
	return head;
}



void List_print(pList head,void (*pstr)(pList))
{
   pList pt;
   pt = head->pNext;	   
   while (pt != NULL)  
   {
       pstr(pt);// ����ָ�룬��ͬ�������ݵĴ�ӡ
	   pt = pt->pNext;
   }
 
}



void List_add(pList head,void *data)
{
	pList pNew,pt;
	pt = head;
	pNew = List_init(data);// ��ʼ��һ���½��
	while(pt->pNext != NULL )// ����ƫ�Ƶ������
	{   
		pt=pt->pNext; 
	}   	
    	pt->pNext = pNew;// ��ĩβ��ӽ��
}



int  List_count(pList head)
{
	pList p1;
	int nCount = 0;
	p1=head->pNext;
	while(p1 != NULL)
	{
		nCount++;
		p1=p1->pNext;
	}
	return nCount;
}



void List_free(pList head)
{
	pList ptr = head->pNext;
	while(ptr!=NULL)
	{
		head->pNext=ptr->pNext;
		free(ptr->pData);// ���ͷ�������ռ�
		free(ptr);// ���ͷŽ��ռ�
		ptr = head->pNext;
	}
	    free(head);// ����ͷ�ͷ���
}
