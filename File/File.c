/************************************************************************
* ��Ȩ����  (c)2008,   RunShan
* �ļ����ƣ� File.c

* ����ժҪ��
*     ���ļ�ʵ�ֹ����ļ����������й��ܡ�
* ��ʷ��¼��
*     �������ڣ�2013-08-05   �޸��ˣ�����ľ
*************************************************************************/
#include <string.h>
#include <conio.h>
#include <malloc.h>
#include <windows.h>
#include "..\\File\\File.h"
#include "..\\Glb_putstring\\Glb_putstring.h"


FILE *File_open(char *dirname)
{
	FILE *fp;
	fp = fopen(dirname,"rb+");// �ļ����ڣ���r+��
	if (fp == NULL)
	{
		fp = fopen(dirname,"wb+");// �ļ������ڣ���w+��
		if (fp == NULL)
		{
			printf("file open failed.\n");// �򿪲��ɹ�������ʾ
		}
	} 
	
	return fp;
}



int File_write(FILE *fp,pList head,int size,int n)
{	
	pList pt;
	int count = 0;
	fseek(fp,0,n);// �ļ�ָ��ƫ�Ƶ�nָ����λ��
	pt = head->pNext;
	while(pt != NULL)
	{ 
		count++;
        fwrite(pt->pData,size,1,fp);// ��nָ����λ��д������
		fflush(fp);// �����ļ�
		pt = pt->pNext;
	}
	return count;
}




pList File_read(FILE *fp,int size)
{
	pList head;
	int flag;
    void *p1;
	fseek(fp,0,SEEK_SET);//��λ���ļ�ͷ
	head = List_init(NULL);
	p1 = malloc(size);
	flag = fread(p1,size,1,fp);// flag���������ɹ����
	while(flag)
	{		 	
		List_add(head,p1);
		p1 = malloc(size);// ÿ�ο���һ���¿ռ䣬���ÿ�ζ�����������
		flag = fread(p1,size,1,fp); 
	}
    return head;//���ض��������ͷָ��
}



void File_remove(FILE *fp,pList head,int size,int (*prem)(pList))
{	
	
	pList pt;
	int count;
	count = 0;
    pt = head->pNext;
	while(pt != NULL)
	{
		count++;// ��¼����λ��
		if(prem(pt))// ��ѯҪ�����Ľ������
		break;
		pt = pt->pNext;	
	}
      
	  	if (pt == NULL)
	    printf("\nδ�鵽������Ϣ");

		else
	{

		printf("\n�Ƿ�ȷ��ɾ��(y)�ǡ�(n)��:");
		if (glb_putString(NULL,0,0,1,1) == 'y')// ��ʾ�Ƿ�ȷ��ɾ��
		{
			fseek(fp,(count-1)*size,SEEK_SET);// ��λ��Ҫ��ɾ���Ľ��λ��
		    fwrite(pt->pData,size,1,fp);// ���Ǿ�����
		    fflush(fp);
			printf("\nɾ���ɹ�");
		}
		else
			printf("\nɾ��ʧ��");	
} 
  
	   printf("�������������...");
	   getch();	
}



void File_add(FILE *fp,pList head,int size,void *(*padd)(void *data))//���һ����Ա
{	
	pList pNew,pt;
	pt = head;
	while(pt->pNext != NULL )
	{   
		pt=pt->pNext; 
	}
   	pNew = List_init(padd(pt->pData));		
	printf("�Ƿ�ȷ������(y)�ǡ�(n)��:");
	if (glb_putString(NULL,0,0,1,1) == 'y')// ��ʾ�Ƿ�ȷ������
	{
	        pt->pNext = pNew; 
			fseek(fp,0,SEEK_END);//��λ���ļ�ĩβ�������  
			fwrite(pNew->pData,size,1,fp);// ��������������
			fflush(fp);	  	     
	        printf("\n���ӳɹ�");			
	}
	else
	    	printf("\n����ʧ��");
          
    printf("�������������...");
	getch();	          
}



void File_del(FILE *fp,char dir[],pList head,int size,int (*pdel)(pList))
{
   
  	pList pt,ps;
	ps = head;
	pt = head->pNext;
	while (pt != NULL )
{    
	if (pdel(pt))
{
			
	  printf("\n�Ƿ�ȷ��ɾ��(y)�ǡ�(n)��:");
     if (glb_putString(NULL,0,0,1,1) == 'y')
    { 
	   ps->pNext = pt->pNext; 
	   free(pt);// �ͷ�Ҫɾ���Ľ��
       fclose(fp);
	   fp = fopen(dir,"w+");// ��W+��ʽ���´��ļ�
 	   File_write(fp,head,size,0);// ���°�����д���ļ�
	   printf("\nɾ���ɹ�");
	}
	else
	   printf("\nɾ��ʧ��");
	   break;
}
        ps = pt;
		pt = pt->pNext;
}
     if (pt == NULL)
	 	printf("\nδ�ҵ�������Ϣ");	
     printf("�������������...");
	 getch();	
}



void File_updata(FILE *fp,pList head,int size,int (*p)(pList))//���������޸���Ϣ��ͬʱ���µ��ļ���
{
	pList pt;
	int count;
	count = 0;
    pt = head->pNext;
	while(pt != NULL)
	{
		count++;// ��¼Ҫ���µ������������е�λ��
		if(p(pt))// ����Ҫ���µ�����
		{ 
		  break;			
		}
		pt = pt->pNext;		
	}

	if(pt == NULL)
	printf("\nδ�鵽������Ϣ");

    else
	{
		printf("\n�Ƿ�ȷ���޸�(y)�ǡ�(n)��:");
		if (glb_putString(NULL,0,0,1,1) == 'y')
		{
			fseek(fp,(count-1)*size,SEEK_SET);// ��λ��Ҫ���µĽ��λ��
		    fwrite(pt->pData,size,1,fp);// ���Ǿ�����
		    fflush(fp);
			printf("\n�޸ĳɹ�");
		}
		else
			printf("\n�޸�ʧ��");    
	} 
	 printf("�������������...");
	 getch();	
}

