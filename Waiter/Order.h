#ifndef _ORDER_H_
#define _ORDER_H_

#include <conio.h>
#include "..\\File\File.h"
#include "..\\List\List.h"
#include "..\\Table\Table.h"
#include "..\\Menu\Menu.h"
#include "..\\Log_in\Log_in.h"
#include "..\\Glb_putstring\\Glb_putstring.h"

struct Order_t //����
{
	char ordernum[15]; //������
	char acname[10]; // ���˷���Ա
	char tablenum[6]; // ̨����
	int money; //�ܽ��
	int amount; //�ܷ���
	
};

struct Title_t  //�굥
{
	char ordernum[15]; //������
	struct Menu_t pMenu;// ĳһ����
	int amount;// ĳһ���˵ķ���
	
};

/************************************************************************
* �������ƣ�struct Order_t *Order_init(char str[])
* ����������
           �����ṹ���ʼ������
* ����˵����
*       char str[]  ��˵�̨����
* ����ֵ��
*        ���س�ʼ���Ķ������ָ��
*************************************************************************/
struct Order_t *Order_init(char str[]);

/************************************************************************
* �������ƣ�struct Title_t *Title_init(struct Order_t *pNew,struct Menu_t *data,int n)
* ����������
           �굥�ṹ���ʼ������
* ����˵����
*       struct Order_t *pNew     �����̨����Ӧ�Ķ������ݵ�ָ��
        struct Menu_t *data      �����Ĳ�������
        int n                    �˵ķ���
* ����ֵ��
*        ���س�ʼ�����굥���ָ��
*************************************************************************/
struct Title_t *Title_init(struct Order_t *pNew,struct Menu_t *data,int n);

/************************************************************************
* �������ƣ�void Order_add(int count1,struct Order_t *pNew,pList pTitle,pList pOrder,pList pMenu,char tabpath[])
* ����������
           �Ӳ˹��ܺ���
* ����˵����
*       int count1               ��������ĸ���
        struct Order_t *pNew    ��Ӧ�Ķ�������ָ��
        pList pTitle            �굥�����ͷָ��
        pList pOrder            ���������ͷָ��
        pList pMenu             ���������ͷָ��
        char tabpath[]          �굥���м���·��
* ����ֵ��
*       ��
*************************************************************************/
void Order_add(int count1,struct Order_t *pNew,pList pTitle,pList pOrder,pList pMenu,char tabpath[]);
/************************************************************************
* �������ƣ�void Order_del(int count1,struct Order_t *pNew,pList pTitle,pList pMenu,pList pOrder,char tabpath[])
* ����������
           ���˹��ܺ���
* ����˵����
*       int count1               ��������ĸ���
        struct Order_t *pNew    ��Ӧ�Ķ�������ָ��
        pList pTitle            �굥�����ͷָ��
        pList pOrder            ���������ͷָ��
        pList pMenu             ���������ͷָ��
        char tabpath[]          �굥���м���·��
* ����ֵ��
*       ��
*************************************************************************/
void Order_del(int count1,struct Order_t *pNew,pList pTitle,pList pMenu,pList pOrder,char tabpath[]);

/************************************************************************
* �������ƣ�void Order_statist(struct Order_t *pNew,pList pTitle)
* ����������
           �������ܽ��ܷ���ͳ�ƺ���
* ����˵����
*       struct Order_t *pNew     �������ݵ�ָ��
        pList pTitle             �굥�����ͷָ��
* ����ֵ��
*        ��
*************************************************************************/
void Order_statist(struct Order_t *pNew,pList pTitle);

/************************************************************************
* �������ƣ�void Order_print(pList pMenu,pList pTitle,struct Order_t *pNew)
* ����������
           ������ӡ����
* ����˵����
*       pList pMenu            ���׵�ͷָ��
        pList pTitle           �굥��ͷָ��
        struct Order_t *pNew   �������ݵ�ָ��
* ����ֵ��
*        ��
*************************************************************************/
void Order_print(pList pMenu,pList pTitle,struct Order_t *pNew);

/************************************************************************
* �������ƣ�long Ordernum_get(char num[],char str[])
* ����������
           �Զ����ɶ����ŵĺ���
* ����˵����
*       char num[]    �����ṹ���еĶ����ų�Ա����
        char str[]    ��˵�̨����
* ����ֵ��
*        ���ض�����
*************************************************************************/
long Ordernum_get(char num[],char str[]);

/************************************************************************
* �������ƣ�void Orderdate_input(long *stardate,long *enddate)
* ����������
           ��ʼ���ںͽ������ڵ����뺯��
* ����˵����
*       long *stardate    ��ʼ���ڵ�ָ��
        long *enddate     �������ڵ�ָ��
* ����ֵ��
*        ��
*************************************************************************/
void Orderdate_input(long *stardate,long *enddate);

/************************************************************************
* �������ƣ�void convert(char s[],int data,int n)
* ����������
           ����ת������
* ����˵����
*       char s[]     ���ת�����
        int data    ��ת��������
        int n       ���ڵ�λ��
* ����ֵ��
*        ��
*************************************************************************/
void convert(char s[],int data,int n);

/************************************************************************
* �������ƣ�void Order_search_unbuy(pList pOrder,pList pTable)
* ����������
           δ�򶩵���ѯ����
* ����˵����
*      pList pOrder     ������ͷָ��
    
* ����ֵ��
*        ��
*************************************************************************/
void Order_search_unbuy(pList pOrder);

/************************************************************************
* �������ƣ�void Order_search_buy()
* ����������
           ���򶩵���ѯ����
* ����˵����
*        ��
* ����ֵ��
*        ��
*************************************************************************/
void Order_search_buy();

/************************************************************************
* �������ƣ�void Title_print(pList pTitle,struct Order_t *pOrder)
* ����������
           �굥��ӡ����
* ����˵����
*      pList pTitle             �굥��ͷָ��
       struct Order_t *pOrder   �������ݵ�ָ��
* ����ֵ��
*        ��
*************************************************************************/
void Title_print(pList pTitle,struct Order_t *pOrder);

#endif


