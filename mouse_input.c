#include<stdio.h>
#include"egg.h"
#include"elevator.h"
extern int ask(char order);//�����û��������ָ��ж��Ƿ����ظ���ָ��,�ظ�����1�����򷵻�0
extern void egg_order();
int mouse_input()
{
	int i,mx,my,event;
	while(initial==0);
	while((event=WaitForEvent())!=EXIT)
	{
		if(event==KEYDOWN)
		{
			mx=(int)GetMouseX();
			my=(int)GetMouseY();
			for(i=0;i<KEY_AMOUNT;i++)
				if(mx>=key_position[i].leftup_x&&
					mx<=key_position[i].rightdown_x&&
					my>=key_position[i].rightdown_y&&
					my<=key_position[i].leftup_y&&
					ask(key_position[i].order)==0)
				{
					if(key_position[i].order=='O'||
					   key_position[i].order=='P'||
					   key_position[i].order=='0'||
					   key_position[i].order=='Z')
					{
						if(key_position[i].order=='O')//�����ȷ���
							strategy=1;
						if(key_position[i].order=='P')//˳�����
							strategy=2;
						if(key_position[i].order=='0')//GO��
							go=1;
						if(key_position[i].order=='Z')//��GO��
							go=0;
					}
					else
					{
						input[++size].order=key_position[i].order;
						input[size].time=Time;
						input[size].is_done=0;
						if(State==-2)
							State=1;//��ʼ��Ϊ����
					}
					break;
				}
				egg_order();
		}
	}
	return 0;
}

