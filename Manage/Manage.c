/************************************************************************
* ��Ȩ����  (c)2008,   ׿Խ�����ְҵ��ѵѧУ��
* �ļ����ƣ� Manage.c

* ����ժҪ��
*     ���ļ�ʵ�ֹ��ھ����ѯ�Ĺ��ܡ�
* ��ʷ��¼��
*     �������ڣ�2013-08-05   �޸��ˣ�����ľ
*************************************************************************/
#include <stdio.h>
#include <windows.h>
#include "..\\Manage\Manage.h"
#include "..\\List\List.h"
#include "..\\Staff\staff.h"
#include "..\\Waiter\Order.h"


int Ui_manage()
{	
	int n;
	while(1)
	{			
		system("cls");
		printf("\n\n\n\t\t\t������ѡ�����\n\n");
		printf("\t\t\t1��Ӫ�ջ���\n\n");
		printf("\t\t\t2��ע��\n\n");
		printf("\t\t\t3���˳�\n\n");
		printf("\t\t\t����������Ҫѡ��Ĺ��ܣ�");
		n = glb_putString(NULL,'1','3',1,2);
	    if (n == 1)
	   {
		Profit_statist();
	   }
		else if(n == 2)
			return 0;
		else if (n == 3)
			return 1;		    				
	}	

}



void Profit_statist()
{
	pList pOrder,pStaff;
	pList p1,p2;
	struct Order_t *Odate;
	struct staff_t *Sdate;
	FILE *fp;
	long money,income;// �ܽ��
	long *stardate,*enddate;
    long ordernum;// ������
	money = income = 0;
	stardate = (long *)malloc(sizeof(long));// ��ʼ����
    enddate = (long *)malloc(sizeof(long));// ��������
	fp = File_open("./Date/Order/Order.txt");
    pOrder= File_read(fp,sizeof(struct Order_t));
	fp = File_open("./Date/Staff.txt");
    pStaff= File_read(fp,sizeof(struct staff_t));

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
    printf("\t\t\t%-15s%s\n","����Ա","Ӫ��");
	p1 = pStaff->pNext;
	while (p1)
	{
		Sdate = (struct staff_t *)(p1->pData);
		p2 = pOrder->pNext;
		while(p2)
		{
			Odate = (struct Order_t *)(p2->pData);
			sscanf(Odate->ordernum,"%8ld",&ordernum);// ��ȡ�������ϵ�����
			if ((strcmp(Sdate->acName,Odate->acname) == 0)&&(ordernum <= *enddate) && (ordernum >= *stardate))
			{
				money = money + (Odate->money);
			}
			p2 = p2->pNext;
		}
		if ((Sdate->role == 0))// �ж��Ƿ�Ϊ����Ա
		{
			printf("\t\t\t%-15s%s%ld\n",Sdate->acName,"��",money);
			income = income + money;// �ۼ�ÿ������Ա��Ӫҵ��
			money = 0;
		}	
		p1 = p1->pNext;
	}

	    printf("\n\t\t\t��Ӫҵ���%ld\n",income);
		printf("\n\t\t\t�밴���������...");
		getch();
}