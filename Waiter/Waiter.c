#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "..\\Waiter\Waiter.h"

extern  char acName[10];//����Ա��¼��

/************************************************************************
int Ui_waiter()
����Ա����
************************************************************************/
int Ui_waiter()
{  
	pList pTable;
	int n;
    FILE *fp;
	void (*pst[5])(pList pTable) = {Open_desk,Order_dishes,Settle_Accounts,turnover_search,Order_search};
	fp = File_open("./Date/Table.txt");
    pTable= File_read(fp,sizeof(struct Table_t));
	while(1)
	{	
		system("cls");
		printf("\n\n\n\t\t\t����Ա����ѡ�����\n\n");
		printf("\t\t\t1������\n\n");
		printf("\t\t\t2�����\n\n");
		printf("\t\t\t3������\n\n");
		printf("\t\t\t4��Ӫҵ���ѯ\n\n");
		printf("\t\t\t5������/δ�򵥲�ѯ\n\n");
		printf("\t\t\t6��ע��\n\n");
		printf("\t\t\t7���˳�\n\n");
		printf("\t\t\t����������Ҫѡ��Ĺ��ܣ�");
		n = glb_putString(NULL,'1','7',1,2);
		if (n > 0 && n <6)
		{
			pst[n-1](pTable);
		}
		else if(n == 6)
			return 0;
		else if (n == 7)
			return 1;		    				
	}	
	   
	  
}

/************************************************************************
void  Open_desk(pList pTable)
����
************************************************************************/
void  Open_desk(pList pTable)
{	
	pList pt;
	int n;
	struct Table_t *ps;
	char str[8] = {0};
    FILE *fp;
	fp = File_open("./Date/Table.txt");

	while (1)
	{
		system("cls");
    n = Table_search(pTable,0,3);// ��ӡ���к�Ԥ����̨��
	if (n == 0)
	{
		printf("�����޿������ӣ������������...");
		getch();
		return;
	}
    printf("������Ҫ������̨���ţ�");
	glb_putString(str,'0','9',3,2);// str���Ҫ������̨����
    pt = pTable->pNext;
	while(pt != NULL)
	 { 	  
		ps = (struct Table_t *)(pt->pData);
		if (strcmp(ps->acNo,str) == 0)
		{	
			if ((ps->state == 0)||(ps->state == 3))
     		break;
		}
		pt = pt->pNext;
	 }
	
	 if (pt == NULL)
	  {
		  memset(str,0,sizeof(char));
		  printf("\n̨��������򲻿���,���������룬�����������...");
		  getch();
	  }
	  else
		  break;
	}
	  
	     if (ps->state == 3)// ��ΪԤ��״̬��ֱ����תΪ��˽���
	     {
			 ps->state = 2;//ռ�ã�ת����˽���
			 File_write(fp,pTable,sizeof(struct Table_t),0);// ����̨���ļ�
			 printf("\n�����ɹ��������������...");
			 getch();
			 Order_dishes(pTable);// ��ת����˽���
			 return;
	     }
	     printf("\n�Ƿ����Ͽ�ʼ���(y)ȷ����(n)���أ�");
	     if(glb_putString(NULL,0,0,1,1) != 'y')
		 {     
			 ps->state = 3;//Ԥ��״̬
			 File_write(fp,pTable,sizeof(struct Table_t),0);
			 printf("\nԤ���ɹ��������������...");
			 getch();
		 }  
		 else 
		 {
			 ps->state = 2;//ռ�ã�ת����˽���
			 File_write(fp,pTable,sizeof(struct Table_t),0);
			 printf("\n�����ɹ��������������...");
			 getch();
			 Order_dishes(pTable);
			 return;
		 }			 
	   
}

/************************************************************************
void Order_dishes(pList pTable)
���
************************************************************************/
void Order_dishes(pList pTable)
{
	FILE *fd;
	int n,count1;
	pList pMenu,pOrder,pTitle,pt;
    struct Order_t *pNew,*pdata;
	char txt[] = ".txt";
    char str[8] = {0};
    char tabpath[30] ="./Date/Cache/";// �굥�����·��

	fd = File_open("./Date/Menu.txt");
	pMenu = File_read(fd,sizeof(struct Menu_t));	
	fd = File_open("./Date/Cache/Order.txt");
    pOrder = File_read(fd,sizeof(struct Order_t));

	while (1)
	{
		system("cls");
	n = Table_search(pTable,2,4);// �ж��Ƿ��п�������
	if (n == 0)
	{		
		printf("�����޿������ӣ������������...");
		getch();
		return;
	}
	printf("������Ҫ��˵�̨���ţ�");
	glb_putString(str,'0','9',3,2);
    strcat(tabpath,str);
	strcat(tabpath,txt);// ��ȡ�굥��·��
    pt = pOrder->pNext;
	while(pt)
	{
         pdata = (struct Order_t *)(pt->pData);
		if (strcmp(pdata->tablenum,str) == 0)// �жϵ�ǰδ�򶩵����Ƿ���ڴ�̨���Ķ���
		{
			pNew = pdata;
			fd = File_open(tabpath);
	        pTitle = File_read(fd,sizeof(struct Title_t));
			break;
		}
		pt = pt->pNext;
	}

    if (pt == NULL)// δ�򶩵�����������̨���Ķ���
    {	
        pt = pTable ->pNext;
		while(pt)
		{
			if (strcmp(((struct Table_t *)(pt->pData))->acNo,str) == 0)
			{
				if (((struct Table_t *)(pt->pData))->state == 2)
				{
					pNew = Order_init(str);// ��ʼ��һ���������
					List_add(pOrder,pNew);
					File_write(fd,pOrder,sizeof(struct Order_t),0);// д��δ�򶩵��ļ�
					fd = fopen(tabpath,"w+");// ��w+��ʽ���굥�ļ������ڿ�ʼ���
		            pTitle = File_read(fd,sizeof(struct Title_t));
					break;
				}
				else if (((struct Table_t *)(pt->pData))->state == 0)
				{
					printf("\n������Ϊ�������ȿ������ܵ�ˣ��Ƿ�����(y)������(n)���أ�");
					if (glb_putString(NULL,0,0,1,1) == 'y')
						Open_desk(pTable);// ��ת����������
					return;
				}		
		
			}
		               pt = pt->pNext;
		
		}
		if (pt == NULL)
		{
			memset(str,0,sizeof(char));
			strcpy(tabpath,"./Date/Cache/");
			printf("\n���������������ߴ���ά��״̬�����������룬�����������...");
			getch();
		}
		else
			break;		
    }
	else
		break;
}
     Order_print(pMenu,pTitle,pNew);
	 count1 = List_count(pMenu);// ��ȡ���׵ĸ���
	 while (1)	
{
	JR_EmptyRaw(count1+3,count1+12);// ��ղ�������ļ�����Ϣ
	JR_SetCursor(count1+3,0);
	printf("\t\t(1)�����\n");
	printf("\t\t(2)���˲�\n");
	printf("\t\t(3)������\n");
	printf("\t\t������Ҫ�����Ĺ��ܣ�");
    n = glb_putString(NULL,'1','3',1,2);
	switch(n)
	{ 
	 case 1:
		 {
			 Order_add(count1,pNew,pTitle,pOrder,pMenu,tabpath); // �Ӳ˹��ܺ���
		     break;
		 }	
	 case 2:
		 {
			 Order_del(count1,pNew,pTitle,pMenu,pOrder,tabpath);// ���˹��ܺ���
			 break;
		 }
	 case 3:
		     break;
		
	}	
	        
	 if (n == 3)
	 {
		 break;
	 }
	 	   		   
	}	 
	 List_free(pOrder);
	 List_free(pMenu);
	 List_free(pTitle);
}

/************************************************************************
void turnover_search(pList  pTable)
Ӫҵ���ѯ
************************************************************************/
void turnover_search(pList  pTable)
{
  FILE *fp;
  pList pOrder,pt;
  struct Order_t *data;
  long *stardate,*enddate;
  long ordernum;// ������
  int a,b,c;// ������ӡ������
  long money = 0;// ��Ӫҵ��
  stardate = (long *)malloc(sizeof(long));// ��ʼ����
  enddate = (long *)malloc(sizeof(long));// ��������
  fp = File_open("./Date/Order/Order.txt");
  pOrder = File_read(fp,sizeof(struct Order_t));// �������򶩵�����

  system("cls");
  printf("\n\t\t\t(1):�����ѯ\n");
  printf("\n\t\t\t(2):��ʷ��ѯ\n");
  printf("\n\t\t\t������Ҫѡ��Ĺ��ܣ�");
  if (glb_putString(NULL,'1','2',1,2) == 1)
  {
	  system("cls");
	  *stardate = Ordernum_get(NULL,NULL);// ��ȡ��ǰϵͳ����
	  *enddate = *stardate;
  }
  else
  {
      Orderdate_input(stardate,enddate);// ���뿪ʼ�ͽ�������
	  printf("\n");
  }
 
  printf("\t\t%-16s%-18s%-11s\n","������","ʱ��","���");
  pt = pOrder->pNext;
  while (pt)
  {
	  data = (struct Order_t *)(pt->pData);
	  sscanf(data->ordernum,"%8ld",&ordernum);// �ַ���ת���ɳ�����
	  if ((strcmp(data->acname,acName) == 0)&&((ordernum <= *enddate) && (ordernum >= *stardate)))//
	  {
		  money = money + (data->money);// Ӫҵ���ۼ�
         sscanf(data->ordernum,"%4d%2d%2d",&a,&b,&c);//�ֱ�ȡ��������
		 printf("\t\t%-16s%d%s%2d%s%2d%-6s%s%d\n",data->ordernum,a,"��",b,"��",c,"��","��",data->money);		 
	  }
	  pt = pt->pNext;
  } 
      printf("\n\t\tӪҵ���ܶ��%ld\n",money);
      List_free(pOrder);
	  printf("\n\t\t�����������...");
	  getch();
}

/************************************************************************
void Order_search(pList  pTable)
����/δ�򵥲�ѯ
************************************************************************/
void Order_search(pList  pTable)
{
	int n;
	FILE *fp;
	pList pOrder;
	fp = File_open("./Date/Cache/Order.txt");
    pOrder = File_read(fp,sizeof(struct Order_t));// ����δ������
    while (1)
    {
    system("cls");
	printf("\n\n\n\t\t\t����/δ�򵥲�ѯ����\n\n");
	printf("\t\t\t1��δ�򵥲�ѯ\n\n");
	printf("\t\t\t2�����򵥲�ѯ\n\n");
	printf("\t\t\t3���˳�\n\n");
	printf("\t\t\t����������Ҫѡ��Ĺ��ܣ�");
	n = glb_putString(NULL,'1','3',1,2);
	switch(n)
	{
	case 1:
		Order_search_unbuy(pOrder);// δ�򵥲�ѯ���� 
		getch();
		break;
	case 2:
		Order_search_buy();// ���򵥲�ѯ����
		getch();
		break;
	case 3:
		
		break;
	}
	 if (n == 3)
	 {
		break;
	 }
   
	}
     List_free(pOrder);// �ͷ�����
}

/************************************************************************
void Settle_Accounts(pList pTable)
���˹���
************************************************************************/
void Settle_Accounts(pList pTable)
{
	FILE *fp;
	int money;
	pList pt,pTitle,pOrder,ps;
	struct Order_t * data;
	char txt[] = ".txt";
    char str[6] = {0};
	char str1[6] = {0};
    char tabpath[30] ="./Date/Cache/";// δ���굥·��
	fp = File_open("./Date/Cache/Order.txt");// ��δ�򶩵��ļ�
	pOrder = File_read(fp,sizeof(struct Order_t));
	while(1)
	{	
	system("cls");
	pt = pOrder->pNext;
	if (pt == NULL)//�жϵ�ǰ�Ƿ���δ�򶩵�
	{
		printf("\nĿǰû��δ�򶩵��������������...");
		return;
	}
	printf("\t\t%12s%12s%11s%11s\n","������","̨����","���","״̬");
	while (pt)
	{
		data = (struct Order_t *)(pt->pData);
		printf("\t\t%12s%12s%11d%11s\n",data->ordernum,data->tablenum,data->money,"δ֧��");// ��ӡ����δ�ᶩ����Ϣ
		pt = pt->pNext;
	}  
	printf("\n������Ҫ���˵�̨����(3λ)��");
	glb_putString(str,'0','9',3,2);	
	ps = pOrder;
	pt = pOrder->pNext;
	while (pt)
	{
		data = (struct Order_t *)(pt->pData);
		if (strcmp(data->tablenum,str) == 0)// �ҳ�Ҫ���˵Ķ������
			break;
		ps = pt;
		pt = pt->pNext;
	}
	if (pt == NULL)// δ�ҵ�����������ʾ
	{
		printf("\n\n̨�����޶��������󣬰�<Esc>�����ء��������������룺");
		if (getch() == 27)
		return;	
		memset(str,0,sizeof(char));
	}
	else
	   break;
	}	
	strcat(tabpath,str);// ��ȡ�굥��·��
	strcat(tabpath,txt);
	fp = File_open(tabpath);// �򿪽����˵��굥�ļ�
	pTitle = File_read(fp,sizeof(struct Title_t));// ����δ���굥����
	Title_print(pTitle,data);// ��ӡδ���굥��Ϣ
	printf("\n������Ϊ%s�Ƿ���ˣ�(y)ȷ����(n)���أ�",data->ordernum);
	if (glb_putString(NULL,0,0,1,1) == 'y')
	{
		printf("\nʵ�ս�");
		money = glb_putString(str1,'0','9',5,2);// ������
		if (money < data->money)// ʵ�ս���С�ڶ������
		{
			printf("\nʵ�ս��С�ڶ������޷����ˣ������������...");
			getch();
			return;
		}
		printf("\n���ҽ�%d",money - (data->money));
		fp = File_open("./Date/Title/Title.txt");
		File_write(fp,pTitle,sizeof(struct Title_t),2);//д���ѽ��굥����
		
		fp = File_open("./Date/Order/Order.txt");
		fseek(fp,0,2);
		strcpy(data->acname,acName);//д����˷���Ա��¼���������ṹ����
		fwrite(data,sizeof(struct Order_t),1,fp);//д���ѽᶩ���Ľ�㵽��һ���ļ�
		fflush(fp);
		
		ps->pNext = pt->pNext;// ɾ�����
		free(pt);//�ͷ��ѽᶩ���Ľ��
		fp = fopen("./Date/Cache/Order.txt","w+");
		File_write(fp,pOrder,sizeof(struct Order_t),0);//ˢ��δ�ᶩ�����ļ�
		
		pt = pTable->pNext;
		while(pt)
		{
			if(strcmp(((struct Table_t *)(pt->pData))->acNo,str) == 0)// �ҵ��ѽ���̨�����
			{
				((struct Table_t *)(pt->pData))->state = 0;// ����״̬��Ϊ����
				fp = File_open("./Date/Table.txt");
				File_write(fp,pTable,sizeof(struct Table_t),0);// ����̨����Ϣ�ļ�
				break;
			}
			pt = pt->pNext;
		}
		printf("\n���˳ɹ�");			   
	}
	else
		printf("\n����ʧ��");
	printf("�������������...");
	getch();
	List_free(pTitle);
    List_free(pOrder);
}