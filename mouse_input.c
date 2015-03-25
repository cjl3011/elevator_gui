#include<stdio.h>
#include"egg.h"
#include"elevator.h"
extern int ask(char order);//传入用户输入的新指令，判断是否是重复的指令,重复返回1，否则返回0
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
						if(key_position[i].order=='O')//先来先服务
							strategy=1;
						if(key_position[i].order=='P')//顺便服务
							strategy=2;
						if(key_position[i].order=='0')//GO键
							go=1;
						if(key_position[i].order=='Z')//不GO键
							go=0;
					}
					else
					{
						input[++size].order=key_position[i].order;
						input[size].time=Time;
						input[size].is_done=0;
						if(State==-2)
							State=1;//初始化为上升
					}
					break;
				}
				egg_order();
		}
	}
	return 0;
}

