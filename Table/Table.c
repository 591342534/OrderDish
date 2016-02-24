/************************************************************************
* ��Ȩ����  (c)2008,   RunShan
* �ļ����ƣ� Table.c

* ����ժҪ��
*     ���ļ�ʵ�ֹ���̨������ɾ�Ĳ鹦�ܡ�
* ��ʷ��¼��
*     �������ڣ�2013-08-05   �޸��ˣ�����ľ
*************************************************************************/
#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include "..\\Table\Table.h"

void Table_print(pList pt)
{   
	static int k = 0;
    char stat[4][10] ={"����","ά��","ռ��","Ԥ��"};
	struct Table_t *pd;
	pd = (struct Table_t *)(pt->pData);
	if (k == 0)
	{
	 system("cls");
	 printf("\t\t%-10s%-14s%-13s\n","̨����","״̬","λ��");
	 k = 1;
	}
     printf("\t\t%-10s%-14s%-13s\n",pd->acNo,stat[pd->state],pd->seat);
	 if (pt->pNext == NULL)
	 k = 0;
}


void *Table_add(void *data)
{ 	
	struct Table_t *pData,*ps;
	pData = (struct Table_t *)malloc(sizeof(struct Table_t));
	ps = (struct Table_t *)data;
	if (data == NULL)
	{  	
	    system("cls");
	    strcpy(pData->acNo,"100");
	}
	else
    {
		glb_putString(ps->acNo,'0','9',4,2);// ����ת��������1
		strcpy(pData->acNo,ps->acNo);// �ѵ�����ı�Ÿ��Ƹ��±��
	}
	printf("\n������Ҫ���ӵ�̨��״̬(0-���С�1-ά�ޡ�2-ռ��)��");
	pData->state = glb_putString(NULL,'0','2',1,2);
	printf("\n������Ҫ���ӵ�̨��λ��(����)��");
    glb_putString(pData->seat,0,0,14,1);
    return pData;
}



int Table_remove(pList pL)
{ 
      struct Table_t *pt;
      static int k = 0;
	  static char str[8] = {0};
  if (k == 0) 
  {
	  printf("������Ҫɾ����̨�����(3λ)��");
	  glb_putString(str,'0','9',3,2);// strΪҪ��ɾ���ı��
	  k = 1;
  }
  pt = (struct Table_t *)(pL->pData);
  if (strcmp(pt->acNo,str) == 0)
  {
      memset(str,0,sizeof(char));   
	  pt->state = 1;      
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



int Table_updata(pList pL)
{
	struct Table_t *pt;
	static int k = 0;
	static char str[8] = {0};

	if (k == 0)
	{
		printf("������Ҫ�޸ĵ�̨�����(3λ)��");
		glb_putString(str,'0','9',3,2);
		k = 1;
	}
	    pt = (struct Table_t *)(pL->pData);
	  if (strcmp(pt->acNo,str) == 0)
	{
	    memset(str,0,sizeof(char));
		printf("\n��������״̬(0-���С�1-ά�ޡ�2-ռ��)��");
		pt->state = glb_putString(NULL,'0','2',1,2);
		printf("\n��������λ��(����)��");
		glb_putString(pt->seat,0,0,14,1);
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



int Table_search(pList head,int n,int m)
 {
	  pList pL,ps;
	  struct Table_t *data;
	  pL = List_init(NULL);
	  if (n > 2)
	  {
	    system("cls");
		printf("\n\t\t\t(1) ȫ��");
		printf("\n\n\t\t\t(2) ״̬");
		printf("\n\n\t\t\t������Ҫ��ѯ��������");
		if(glb_putString(NULL,'1','2',1,2) == 1)
		{
        List_print(head,Table_print);
		return 0;
		}
		else
	    printf("\n\n\t\t\t������Ҫ��ѯ��̨��״̬(0-���С�1-ά�ޡ�2-ռ��)��");
	    n = glb_putString(NULL,'0','2',1,2);
	  }	  
	  ps = head->pNext;
	  if(ps == NULL)
	{
		system("cls");
		printf("\nδ����̨����Ϣ��������ӣ�\n");
		return 0;
	}
	while(ps != NULL)
 {
         data = (struct Table_t *)(ps->pData);
         if ((data->state == n)||(data->state == m))
         {
		  List_add(pL,data);// ���������ļ�����������
         }
	     
		  ps = ps->pNext;
 }
  
         if (pL->pNext != NULL)
	     {   
		  List_print(pL,Table_print);// ��ӡ���������Ľ��
		  return 1;
	     }
		else
		{		    
			printf("\n\nδ��ѯ�������Ϣ");
			return 0;
		}	
	   	     		 
}



