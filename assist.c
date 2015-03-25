#include"elevator.h"
extern char daxie[];
extern char xiaoxie[];
int assist(int out[],int time,int *direction,Input in[],int in_size)//顺便服务策略：0停止 1上升 -1下降 -2空闲
{
	int keyinfo[3][9]={0},floor=out[time]-1,d=-2;//存储键盘输入信息,[1][]内部请求,[2][]外部丄行请求,[0][]外部下行请求,[][n]n+1层,1被选,0未被选
    int find(Input *,int,int,int,int[][9],int *);
	int newd(int[][9],int,int *,int);
	int finish(Input in[],int direction,int floor,int size);
    if(!find(in,in_size,time,floor,keyinfo,&d))//空 
	{
		*direction=-2;
		out[time+1]=100*out[time];
		return -2;//置电梯于空闲状态
	}
	else//非空 
	{
		newd(keyinfo,floor,&*direction,d);
        if(keyinfo[1][floor]||(keyinfo[0][floor]&&*direction==-1)||(keyinfo[2][floor]&&*direction==1))//需要停靠 
		{
			out[time+1]=out[time];//下一时刻与上一时刻同一位置
			keyinfo[1][floor]=0;//将该指令标记为"已执行"
			if(*direction==-2)
				keyinfo[0][floor]=keyinfo[2][floor]=0;
			else
				keyinfo[1+*direction][floor]=0;
            finish(in,*direction,floor,in_size); 
			return 0;//0指需要暂停 
		}
		else//不需要停靠，电梯将要移动 
		{
			if(*direction==-2)//停一会儿 
				*direction=d;//新方向为最先指令所在方向（若无指令则不改变）
			if(*direction==-2)
			{
				out[time+1]=out[time];//下一时刻与上一时刻同一位置
				return *direction;//不移动返回-2 
			}
			else//将要移动 
			{
				out[time+1]=out[time]+*direction;
				return *direction;
			}//向当前运行方向移动一层
		}
	}
}
int find(Input *in,int size,int curTime,int floor,int keyinfo[][9],int *d)//查找请求序列中的下一个目标楼层 
{
    int i,j,empty=0;//0指空 
    for(i=1;i<=size;i++) 
	    if(!in[i].is_done&&in[i].time<=curTime)
	    {
		    int is_finished=0,ifFirst=1;//0指未完成指令,1指完成指令 
		    for(j=0;j<27;j++) 
			if(xiaoxie[j]==in[i].order)
		    {	
			    if(!(j%9==floor&&curTime-1==in[i].time))
			    {	
				    keyinfo[j/9][j%9]=1; 
					is_finished=1;
					empty=1; 
			    }
			    if(ifFirst)
				    if(j%9>floor)		
					{ 
					    *d=1;  
						ifFirst=0; 
					}
				    else if(j%9<floor)  
					{ 
					    *d=-1; 
						ifFirst=0; 
					}
					break;
			}
		    if(!is_finished) 
			    for(j=0;j<27;j++) 
				    if(daxie[j]==in[i].order)
		            {	
			            if(!(j%9==floor&&curTime-1==in[i].time))
			            {	
					        keyinfo[j/9][j%9]=1;
							empty=1;
						} 
			            if(ifFirst)
				            if(j%9>floor)		
							{ 
							    *d=1;  
								ifFirst=0; 
							}
				            else if(j%9<floor)  
							{ 
                                *d=-1; 
								ifFirst=0; 
							}
				            break;
			        }
	    }
	return empty;
}
int newd(int keyinfo[][9],int floor,int *direction,int d)//确定新的运行方向 
{
	int i;
    if(*direction==-2) 
	    *direction=d; 
	for(i=floor+*direction;i>=0&&i<9;i+=*direction)//向当前运行方向寻找
		if(keyinfo[1][i]||keyinfo[0][i]||keyinfo[2][i])
			return 0;//不改变运行方向
	for(i=floor-*direction;i>=0&&i<9;i-=*direction)//向当前运行方向的相反方向寻找
		if(keyinfo[1][i]||keyinfo[0][i]||keyinfo[2][i])
		{ 
		    *direction*=-1;//改变运行方向 
			return 0; 
		}
	if(keyinfo[1+*direction][floor]==1){}//判断当前楼层是否按上按钮，若有则方向改为上 
	else if(keyinfo[1-*direction][floor]==1) 
        *direction*=-1;//方向改为下 
	return 0;
}
int finish(Input in[],int direction,int floor,int size)//消除命令 
{
	int i;
    for(i=1;i<=size;i++)
	{
		if(in[i].order==xiaoxie[(direction+1)*9+floor]||in[i].order==daxie[(direction+1)*9+floor])
			in[i].is_done=1;//已完成		
		if(in[i].order==xiaoxie[9+floor]||in[i].order==daxie[9+floor])
			in[i].is_done=1;
	}
	return 1;
}