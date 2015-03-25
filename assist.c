#include"elevator.h"
extern char daxie[];
extern char xiaoxie[];
int assist(int out[],int time,int *direction,Input in[],int in_size)//˳�������ԣ�0ֹͣ 1���� -1�½� -2����
{
	int keyinfo[3][9]={0},floor=out[time]-1,d=-2;//�洢����������Ϣ,[1][]�ڲ�����,[2][]�ⲿ�A������,[0][]�ⲿ��������,[][n]n+1��,1��ѡ,0δ��ѡ
    int find(Input *,int,int,int,int[][9],int *);
	int newd(int[][9],int,int *,int);
	int finish(Input in[],int direction,int floor,int size);
    if(!find(in,in_size,time,floor,keyinfo,&d))//�� 
	{
		*direction=-2;
		out[time+1]=100*out[time];
		return -2;//�õ����ڿ���״̬
	}
	else//�ǿ� 
	{
		newd(keyinfo,floor,&*direction,d);
        if(keyinfo[1][floor]||(keyinfo[0][floor]&&*direction==-1)||(keyinfo[2][floor]&&*direction==1))//��Ҫͣ�� 
		{
			out[time+1]=out[time];//��һʱ������һʱ��ͬһλ��
			keyinfo[1][floor]=0;//����ָ����Ϊ"��ִ��"
			if(*direction==-2)
				keyinfo[0][floor]=keyinfo[2][floor]=0;
			else
				keyinfo[1+*direction][floor]=0;
            finish(in,*direction,floor,in_size); 
			return 0;//0ָ��Ҫ��ͣ 
		}
		else//����Ҫͣ�������ݽ�Ҫ�ƶ� 
		{
			if(*direction==-2)//ͣһ��� 
				*direction=d;//�·���Ϊ����ָ�����ڷ�������ָ���򲻸ı䣩
			if(*direction==-2)
			{
				out[time+1]=out[time];//��һʱ������һʱ��ͬһλ��
				return *direction;//���ƶ�����-2 
			}
			else//��Ҫ�ƶ� 
			{
				out[time+1]=out[time]+*direction;
				return *direction;
			}//��ǰ���з����ƶ�һ��
		}
	}
}
int find(Input *in,int size,int curTime,int floor,int keyinfo[][9],int *d)//�������������е���һ��Ŀ��¥�� 
{
    int i,j,empty=0;//0ָ�� 
    for(i=1;i<=size;i++) 
	    if(!in[i].is_done&&in[i].time<=curTime)
	    {
		    int is_finished=0,ifFirst=1;//0ָδ���ָ��,1ָ���ָ�� 
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
int newd(int keyinfo[][9],int floor,int *direction,int d)//ȷ���µ����з��� 
{
	int i;
    if(*direction==-2) 
	    *direction=d; 
	for(i=floor+*direction;i>=0&&i<9;i+=*direction)//��ǰ���з���Ѱ��
		if(keyinfo[1][i]||keyinfo[0][i]||keyinfo[2][i])
			return 0;//���ı����з���
	for(i=floor-*direction;i>=0&&i<9;i-=*direction)//��ǰ���з�����෴����Ѱ��
		if(keyinfo[1][i]||keyinfo[0][i]||keyinfo[2][i])
		{ 
		    *direction*=-1;//�ı����з��� 
			return 0; 
		}
	if(keyinfo[1+*direction][floor]==1){}//�жϵ�ǰ¥���Ƿ��ϰ�ť�����������Ϊ�� 
	else if(keyinfo[1-*direction][floor]==1) 
        *direction*=-1;//�����Ϊ�� 
	return 0;
}
int finish(Input in[],int direction,int floor,int size)//�������� 
{
	int i;
    for(i=1;i<=size;i++)
	{
		if(in[i].order==xiaoxie[(direction+1)*9+floor]||in[i].order==daxie[(direction+1)*9+floor])
			in[i].is_done=1;//�����		
		if(in[i].order==xiaoxie[9+floor]||in[i].order==daxie[9+floor])
			in[i].is_done=1;
	}
	return 1;
}