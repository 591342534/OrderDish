/************************************************************************
* ��Ȩ����  (c)2008,   RunShan
* �ļ����ƣ� main.c

* ����ժҪ��
*     ���ļ�Ϊ��������ڣ�ʵ��ϵͳ�����С�
* ��ʷ��¼��
*     �������ڣ�2013-08-05   �޸��ˣ�����ľ
*************************************************************************/
#include <windows.h>
#include ".\\Staff\staff.h"
#include ".\\File\File.h"
#include ".\\Log_in\Log_in.h"
#include ".\\Admin\Admin.h"
#include ".\\Waiter\Waiter.h"
#include ".\\Manage\Manage.h"

 int main()
{
  int n,k;
  pList head;
  char dir_staff[] = "./Date/Staff.txt";
  FILE * fp;
  int (*pF[3])() = {Ui_waiter,Ui_manage,Ui_admin};
  fp = File_open(dir_staff); 
  head = File_read(fp,sizeof(struct staff_t));
  if (head->pNext == NULL)
  {
	  Login_init(fp,head);
  }   
	  while (1)
	  {
	      fclose(fp);
		  n = Log_in(head);
	      k = pF[n]();
	      if (k == 1)
			   break;
		  else
		  {
		    fp = File_open(dir_staff); 
            head = File_read(fp,sizeof(struct staff_t));
		  }

	  }
         system("cls");
         printf("\n\n\n\n\t\t\t���˳�ϵͳ.....");
         return 0; 
}