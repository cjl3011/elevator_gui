#include"elevator.h"
#include<stdlib.h>
int orders(int out[],Input in[],int time,int in_size,int *condition)//size存储指令
{
	int floor=out[time],goal=0;//floor当前层数，out数组记录上一时刻层数
	Input *Ptr=NULL;
    int control(Input in[],int,Input **);//确定goal楼层
    if(0==(goal=control(in,in_size,&Ptr)))
	{
		out[time+1]=out[time];
		*condition=-2;
	}
	else if(goal==floor)
	{
		out[time+1]=out[time];
		if(Ptr!=NULL)
		{
			Ptr->is_done=1;
			Ptr=NULL;
		}
	}
	else
	{
		*condition=(goal>floor?1:-1);
		out[time+1]=out[time]+*condition;
	}
    return 0;
}
int control(Input in[],int size,Input **nPtr)//确定下一个楼层 
{
	int i,j=0,isFirst=0,next;
	int trans(char);
	for(i=1;i<=size;i++)
	    if(in[i].is_done==0)
	    {
		    if(isFirst==0)
	        {
			    j=in[i].time;
			    next=trans(in[i].order);
			    *nPtr=&in[i];
			    isFirst=1;
		    }
		    else if(j>in[i].time)
            {
			    j=in[i].time;
			    next=trans(in[i].order);
			    *nPtr=&in[i];
		    }
	    }
	if(j==0)
		return 0;
	else 
	    return next;
}
int trans(char order)//转化为数字楼层
{
	extern char daxie[];
	extern char xiaoxie[];
	int j;
	for(j=0;j<27;j++) 
	    if(daxie[j]==order||xiaoxie[j]==order)
		    return j%9+1;
	return 0;
}
