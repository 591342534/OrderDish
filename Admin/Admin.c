/************************************************************************
* ��Ȩ����  (c)2008,   ׿Խ�����ְҵ��ѵѧУ��
* �ļ����ƣ� Admin.c

* ����ժҪ��
*     ���ļ�ʵ�ֹ��ڹ���Ա�������ݵĹ��ܡ�
* ��ʷ��¼��
*     �������ڣ�2013-08-05   �޸��ˣ�����ľ
*************************************************************************/
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "..\\File\File.h"
#include "..\\Admin\Admin.h"
#include "..\\List\List.h"
#include "..\\Staff\staff.h"
#include "..\\Table\Table.h"
#include "..\\Menu\Menu.h"
#include "..\\Glb_putstring\\Glb_putstring.h"



int Ui_admin()
{  
	int n;
	void (*pst[3])() = {Table_manage,Menu_manage,Staff_manage};
	while(1)
	{	
		system("cls");
		printf("\n\n\n\t\t\t����Ա����ѡ�����\n\n");
		printf("\t\t\t1��̨������\n\n");
		printf("\t\t\t2�����׹���\n\n");
		printf("\t\t\t3����Ա����\n\n");
		printf("\t\t\t4��ע��\n\n");
		printf("\t\t\t5���˳�\n\n");
		printf("\t\t\t����������Ҫѡ��Ĺ��ܣ�");
	    n = glb_putString(NULL,'1','5',1,2);
		if (n > 0 && n <4)
		{
			pst[n-1]();
		}
	    else if(n == 4)
			return 0;
		else if (n == 5)
		     return 1;		    				
	}	

}




void Staff_manage()
{
	char dirname[] = "./Date/Staff.txt";
	FILE *fp;
	pList head;
	int n,count;
	fp = File_open(dirname);
	head = File_read(fp,sizeof(struct staff_t));
	count = List_count(head);
	while(1)
	{	 
		system("cls");
		printf("\n\n\n\t\t\tԱ���������\n\n");
		printf("\t\t\t1������Ա��\n\n"); 
		printf("\t\t\t2��ɾ��Ա��\n\n");
		printf("\t\t\t3���޸�Ա��\n\n"); 
		printf("\t\t\t4����ѯԱ��\n\n"); 
		printf("\t\t\t5������\n\n"); 
		printf("\t\t\t������Ҫ�����Ĺ��ܣ�");
		n = glb_putString(NULL,'1','5',1,2);
		switch(n)
		{
		case 1:	
			List_print(head,staff_print);
			File_add(fp,head,sizeof(struct staff_t),staff_add);
			List_print(head,staff_print);		
			break;
		case 2:
			List_print(head,staff_print);
			File_remove(fp,head,sizeof(struct staff_t),staff_remove);
			head = File_read(fp,sizeof(struct staff_t));
			List_print(head,staff_print);			
			break;
		case 3:
			List_print(head,staff_print);
			File_updata(fp,head,sizeof(struct staff_t),staff_updata);
			head = File_read(fp,sizeof(struct staff_t));
			List_print(head,staff_print);		
			break;
		case 4:  
			staff_search(head);			
			break;
		case 5:
			break;
		}
		if (n == 5)
		{
			break;
		}
		else
		{
            printf("\n��<Esc>������...");
			while(getch() != 27)
			{}
		}
		
		
	}
	List_free(head);
}




void Table_manage()
{
	char dirname[] = "./Date/Table.txt";
	FILE *fp;
	pList head;
	int n;
	fp = File_open(dirname);
	head = File_read(fp,sizeof(struct Table_t));
	while(1)
	{	 
		system("cls");
		printf("\n\n\n\t\t\t̨���������\n\n");
		printf("\t\t\t1������̨��\n\n"); 
		printf("\t\t\t2��ɾ��̨��\n\n");
		printf("\t\t\t3���޸�̨��\n\n"); 
		printf("\t\t\t4����ѯ̨��\n\n"); 
		printf("\t\t\t5������\n\n"); 
		printf("\t\t\t��������Ҫ�����Ĺ��ܣ�");
	    n = glb_putString(NULL,'1','5',1,2);
		switch(n)
		{
		case 1:	
			List_print(head,Table_print);
			File_add(fp,head,sizeof(struct Table_t),Table_add);
			head = File_read(fp,sizeof(struct Table_t));
			List_print(head,Table_print);			
			break;
		case 2:
			List_print(head,Table_print);
			File_remove(fp,head,sizeof(struct Table_t),Table_remove);
			head = File_read(fp,sizeof(struct Table_t));
			List_print(head,Table_print);
			break;
		case 3:
			List_print(head,Table_print);
			File_updata(fp,head,sizeof(struct Table_t),Table_updata);
		    head = File_read(fp,sizeof(struct Table_t));
			List_print(head,Table_print);
			break;
		case 4: 
		    Table_search(head,3,4);
			break;
		case 5:
			break;
		}
		if (n == 5)
		{
			break;
		}
		else
		{
            printf("\n��<Esc>������...");
			while(getch() != 27)
			{}
		}
		
	}
	  List_free(head);
}





void Menu_manage()
{
	char dirname[] = "./Date/Menu.txt";
	FILE *fp;
	pList head;
	int n;
	fp = File_open(dirname);
	head = File_read(fp,sizeof(struct Menu_t));
	while(1)
	{	 
		system("cls");
		printf("\n\n\n\t\t\t���׹������\n\n");
		printf("\t\t\t1�����Ӳ���\n\n"); 
		printf("\t\t\t2��ɾ������\n\n");
		printf("\t\t\t3���޸Ĳ���\n\n"); 
		printf("\t\t\t4����ѯ����\n\n"); 
		printf("\t\t\t5������\n\n"); 
		printf("\t\t\t��������Ҫ�����Ĺ��ܣ�");
	    n = glb_putString(NULL,'1','5',1,2);
		switch(n)
		{
		case 1:	
			List_print(head,Menu_print);
			File_add(fp,head,sizeof(struct Menu_t),Menu_add);
			head = File_read(fp,sizeof(struct Menu_t));
			List_print(head,Menu_print);
			break;
		case 2:
			List_print(head,Menu_print);
			File_del(fp,dirname,head,sizeof(struct Menu_t),Menu_del);
			List_print(head,Menu_print);
			break;
		case 3:
			List_print(head,Menu_print);
			File_updata(fp,head,sizeof(struct Menu_t),Menu_updata);
		    head = File_read(fp,sizeof(struct Menu_t));
			List_print(head,Menu_print);
			break;
		case 4: 
	
		    Menu_search(head);
			break;
		case 5:
			break;
		}
		if (n == 5)
		{
			break;
		}
		else
		{
            printf("\n��<Esc>������...");
			while(getch() != 27)
			{}
		}
		
	}
	  List_free(head);
}