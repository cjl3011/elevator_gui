#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include"egg.h"
#include"elevator.h"
#pragma comment(lib,"Winmm.lib")
extern int orders(int out[],Input in[],int time,int in_size,int *condition);
extern int assist(int out[],int time,int *direction,Input in[],int in_size);
extern egg_order();//进行egg库状态下的请求显示
extern void move_lift(int act);//实现电梯的动画上升(act=1 表示上升一层 act=-1表示下降1层 act=0停靠并切换图片 act=2表示关门准备出发)
extern void choose();//改变策略的图片
extern int mouse_input();//egg库的输入
extern void egg_inner_condition(int floor,int dir);//打印egg库版本电梯内部的运行状态提示(floor为楼层 dir为方向 1上 -1下 0停)
extern void egg_outer_condition(int floor,int dir);//打印egg库版本电梯外部的运行状态提示(floor为楼层 dir为方向 1上 -1下 0停 -2空闲)
extern int egg_tips();//打印egg库版本的初始化提示信息
int Time=1;//记录当前仿真时间
Input input[1001];//记录用户的输入请求指令,下标从一开始
int size=0;//input数组的当前元素个数
int State=1;//表示电梯当前的状态（/*0停止*/ 1上升 -1下降 -2空闲）
int output[1001]={0};//储存每个仿真时刻的电梯状态的数组，下标表示时间（如output[0]=1表示电梯在第0秒处于第一层）
static Output position[1001];//记录电梯1000内的运行情况
int go=0;//=1表示GO键被按下 
int delay=1000;//每次行动等待时间
int ratio=5;//等待时间与上升时间的比例
static int t=0;//=0表示get_input还不能走
static int output_way=1;//1表示动画方式，2表示快速方式，3表示完全方式
int strategy=1;//当前采取的策略号
HEGG main_egg;//主蛋的句柄
int step=0;//范围1-CUT 告诉动画
int initial=0;
int ng=0;
int ask(char order);//传入用户输入的新指令，判断是否是重复的指令,重复返回1，否则返回0
void getinput();//处理用户的请求输入，并写入到对应的结构体数组中(*size 指向对应当前input数组的大小)
void state_d();//转化输出部分,并在响应后更改input中的is_done变量
void hint();//打印用户输入指令提示
void locate(int x, int y);//定位到第y行的第x列
void clear();//XP下的代替system("command/ccls")的清屏函数
void print_s();//打印电梯的运行状况
int legal(char order);//判断输入是否合法,h合法返回1，否则返回0
void time_control(int inner[],int outer_up[],int outer_down[]);//主函数中用于遍历转换输入的数组
void Order();//打印剩余的指令
//void deploy();//进行电梯配置
const char daxie[]={"LKJHGFDSA123456789IUYTREWQO"};
const char xiaoxie[]={"lkjhgfdsa123456789iuytrewqo"};
const mouse key_position[KEY_AMOUNT]={	
										{'I',340,113,366,86,NAME1,NAME3},
										{'U',340,177,366,150,NAME1,NAME3},{'K',340,147,366,120,NAME2,NAME4},
										{'Y',340,238,366,211,NAME1,NAME3},{'J',340,207,366,180,NAME2,NAME4},
										{'T',340,304,366,277,NAME1,NAME3},{'H',340,276,366,249,NAME2,NAME4},
										{'R',340,364,366,337,NAME1,NAME3},{'G',340,336,366,309,NAME2,NAME4},
										{'E',340,428,366,399,NAME1,NAME3},{'F',340,400,366,373,NAME2,NAME4},
										{'W',340,495,366,468,NAME1,NAME3},{'D',340,467,366,440,NAME2,NAME4},
										{'Q',340,560,366,533,NAME1,NAME3},{'S',340,532,366,505,NAME2,NAME4}
																		 ,{'A',340,599,366,572,NAME2,NAME4},
										{'B',550,350,650,20,"",""},/*door*/

										{'1',1103,133,1138,95,"bitmap//内部1.bmp","bitmap//内部1-1.bmp"},
										{'2',1103,202,1138,164,"bitmap//内部2.bmp","bitmap//内部2-1.bmp"},
										{'3',1103,268,1138,230,"bitmap//内部3.bmp","bitmap//内部3-1.bmp"},
										{'4',1103,336,1138,298,"bitmap//内部4.bmp","bitmap//内部4-1.bmp"},
										{'5',1022,133,1057,95,"bitmap//内部5.bmp","bitmap//内部5-1.bmp"},
										{'6',1022,202,1057,164,"bitmap//内部6.bmp","bitmap//内部6-1.bmp"},
										{'7',1022,268,1057,230,"bitmap//内部7.bmp","bitmap//内部7-1.bmp"},
										{'8',1022,336,1057,298,"bitmap//内部8.bmp","bitmap//内部8-1.bmp"},
										{'9',1022,405,1057,367,"bitmap//内部9.bmp","bitmap//内部9-1.bmp"},

										{'0',1116,460,1165,418,"bitmap//GO2.bmp","bitmap//GO1.bmp"},/*GO键*/
										{'Z',1047,457,1100,417,"bitmap//不GO2","bitmap//不GO1"},/*不GO键*/


										{'O',572,699,628,657,"",""},/*S1*/
										{'P',479,656,535,614,"",""},/*S2*/
										{'L',502,557,558,515,"",""},/*S3*/
										{'N',640,557,696,515,"",""},/*S4*/
										{'M',666,656,722,614,"",""}/*S5*/
														};
int main()
{	
	DWORD Thread1;
	HANDLE thread1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)getinput,NULL,0,&Thread1);//新线程1
	DWORD Thread2;
	HANDLE thread2=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)mouse_input,NULL,0,&Thread2);//新线程2(egg输入)
	EggStart(1200,700);
	main_egg=LayEgg();
	//ShowConsoleWindow(0);
	initial=1;//完成初始化
	DrawBitmap("bitmap//背景.bmp");
	ShowConsoleWindow(1);
    mciSendString("play zombie.wma repeat","",0,NULL);
	t=1;//表示getinput可以走了
	output[1]=1;//赋予电梯初始状态
	position[1].floor=1;
	position[1].statue=-2;
	clear();
	Order();
	hint();
	while(1)
	{
		if(strategy==1)
     	{
	    	int i;
	    	for(i=1;i<=size;i++)
            	printf("%d %c %d %d %d\n",input[i].time,input[i].order,input[i].is_done,Time,State);
     	    orders(output,input,Time,size,&State);//先来先服务策略
     	}
		else
		{
			int i;
			for(i=1;i<=size;i++)
				printf("%d %c %d\n",input[i].time,input[i].order,input[i].is_done);
			assist(output,Time,&State,input,size);//顺便服务策略    
		}
		state_d();
		clear();
		//Order();
		choose();
		egg_order();
		if(output_way!=2)
			print_s();
		Order();
		hint();
		Time++;//仿真时间向后推进
	}
	return 0;
}
void getinput()//处理用户的请求输入，并写入到对应的结构体数组中(*size 指向对应当前input数组的大小)
{
	char ch[50];//缓冲字符串
	int i=0;
	while(t==0);//等待主函数结束
	while(initial==0);
	while(1)
	{
		i=0;
		gets(ch);
		locate(0,0);
		clear();
		locate(0,0);
		if(output_way!=2)
			print_s();
		Order();
		hint();
		while(ch[i]!='\0')//'\0'表示输入结束
		{
			if(ch[i]=='O'||ch[i]=='o')//先来先服务
				strategy=1;
			if(ch[i]=='P'||ch[i]=='p')//顺便服务
				strategy=2;
			if(ch[i]=='0')
				go=1;
			if(ch[i]!=' '&&ask(ch[i])==0&&legal(ch[i])==1)
			{
				size++;
				input[size].order=ch[i];
				input[size].is_done=0;
				input[size].time=Time;	
				if(State==-2)
					State=1;//初始化为上升
			}
			i++;
		}
	}
}
void state_d()//转化输出部分,并在响应后更改input中的is_done变量
{
	position[Time].floor=output[Time];
	if(output[Time+1]==output[Time]&&State!=-2)//下一个时刻和当前时刻的电梯层数相同（不移动）
	{
		int flag=0;//等待GO的时间		
		go=0;
		position[Time].statue=0;
not_go://按下不GO键
		egg_outer_condition(output[Time],0);
		egg_inner_condition(output[Time],0);
		move_lift(0);
		SetActiveEgg(main_egg);
		while(bitmap==1);
		while(action==1);
		ng=1;
		MovePen(1013,461);
		DrawBitmap("bitmap//不GO2.bmp");
		ng=0;
		while(go==0&&flag<=ratio-2)//GO键还没有被按下
		{
			clear();
			Order();
			print_s();
			hint();
			Sleep(delay);
			Time++;
			output[Time+1]=output[Time];
			position[Time].floor=output[Time];
			position[Time].statue=0;
			flag++;
		}
		if(go==1)
		{	
			while(bitmap==1);
			while(action==1);
			ng=1;
			MovePen(1096,461);
			DrawBitmap("bitmap//GO1.bmp");//偷懒了
			ng=0;
			move_lift(2);
			while(bitmap==1);
			while(action==1);
			ng=1;
			SetActiveEgg(main_egg);
			MovePen(1096,461);
			DrawBitmap("bitmap//GO2.bmp");//偷懒了
			ng=0;
		}
		else//没按GO键
		{
			move_lift(2);
			go=1;
		}
		if(go!=1)//按了不GO键
		{
			while(bitmap==1);
			while(action==1);
			ng=1;
			SetActiveEgg(main_egg);
			MovePen(1013,461);
			DrawBitmap("bitmap//不GO1.bmp");
			ng=0;
			goto not_go;
		}
		position[Time].statue=2;
		go=0;
	}
	else if(output[Time+1]==100*output[Time]||State==-2)//空闲
	{
		egg_outer_condition(output[Time],-2);
		egg_inner_condition(output[Time],-2);
		move_lift(-2);
		output[Time+1]=output[Time];
		position[Time].statue=-2;
	}
	else if(output[Time+1]>output[Time])//电梯要上升
	{
		egg_outer_condition(output[Time],1);
		egg_inner_condition(output[Time],1);
		move_lift(1);
		State=1;
		position[Time].statue=1;
	}
	else//电梯要下降
	{
		egg_outer_condition(output[Time],-1);
		egg_inner_condition(output[Time],-1);
		State=-1;
		position[Time].statue=-1;
		move_lift(-1);
	}
}
void print_s()//输出电梯状态
{
	int i;
	int min;
    min=max(1,Time-10);//打印最多11条记录
    printf("================电梯运行情况");
    for(i=1;i<=52;i++)
		printf("=");
	for(i=min;i<=Time;i++)
	{
		if(position[i].statue==-2||State==-2)//当前时刻为空闲
			printf("第%d时刻:电梯在%d楼，处于空闲状态\n",i,position[i].floor);
		else if(position[i].statue==0)//当前时刻电梯开门等待
			printf("第%d时刻:电梯在%d楼开门等待\n",i,position[i].floor);
		else if(position[i].statue==2)//关门
			printf("第%d时刻:电梯在%d楼关门\n",i,position[i].floor);
		else//当前时刻电梯要上升或者下降
		    printf("第%d时刻:电梯从%d楼到%d楼\n",i,position[i].floor,position[i].floor+position[i].statue);
	}
}
int ask(char order)//传入用户输入的新指令，判断是否是重复的指令,重复返回1，否则返回0
{
	int i;
	for(i=1;i<=size;i++)
		if(input[i].order==order&&input[i].is_done==0)
			return 1;
    return 0;
}
void hint()//打印用户输入指令提示
{
	printf("              |            您可以随时切换策略:                |\r\n");
	printf("              |  按o键为先来先服务策略，p键为顺便服务策略     |\r\n");
	printf("              |    1-9代表电梯内乘客按目标按钮,0代表GO键      |\r\n");
	printf("              |  q、w、e、r、t、y、u、i对应8层到1层的上行请求 |\r\n");
	printf("              |  a、s、d、f、g、h、j、k对应9层到2层的下行请求 |\r\n");
	printf("              =================================================\r\n");
	printf("请依次输入您的指令，并按回车键:\n");
}
int legal(char order)//判断输入是否合法,合法返回1，否则返回0
{
	int i;
	char wrong[]="oOLlzZxXcCvVbBnNmM";
    for(i=0;i<=17;i++)
		if(order==wrong[i])
			return 0;
	for(i=0;xiaoxie[i]!='\0'&&daxie[i]!='\0';i++)
		if(order==xiaoxie[i]||order==daxie[i])
			return 1;
	return 0;
}
void clear()//清屏函数
{
	int i;
    locate(0,0);
	for(i=1;i<=250;i++)
		printf("\t");
	locate(0,0);
    return;
}
void locate(int x,int y)//定位到第y行的第x列
{
    int xx=0x0b;
    HANDLE hOutput;
    COORD loc;
    loc.X=x;
    loc.Y=y;
    hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, loc);
    return;
}
void time_control(int inner[],int outer_up[],int outer_down[])//控制时间，在主函数中用于遍历转换输入的数组
{  
	int i;
	int floor=0;
    for(i=1;i<=size;i++)
	{
		if(input[i].is_done==0)//没有被响应的请求
		{
			if(input[i].order<='9'&&input[i].order>='1')//内部请求
				inner[input[i].order-48]=1;
            else//外部请求
			{
				switch(input[i].order)
				{
				    case 'q'://八层上行
					    outer_up[8]=1;
					    break;
				    case 'w'://七层上行
					    outer_up[7]=1;
					    break;
				    case 'e'://六层上行
					    outer_up[6]=1;
					    break;
				    case 'r'://五层上行
					    outer_up[5]=1;
					    break;
				    case 't'://四层上行
					    outer_up[4]=1;
					    break;
				    case 'y'://三层上行
					    outer_up[3]=1;
					    break;
				    case 'u'://二层上行
					    outer_up[2]=1;
					    break;
				    case 'i'://一层上行
					    outer_up[1]=1;
					    break;
				    case 'a'://九层下行
					    outer_down[9]=1;
					    break;
				    case 's'://八层下行
					    outer_down[8]=1;
					    break;
				    case 'd'://七层下行
					    outer_down[7]=1;
					    break;
				    case 'f'://六层下行
					    outer_down[6]=1;
					    break;
				    case 'g'://五层下行
					    outer_down[5]=1;
					    break;
			        case 'h'://四层下行
					    outer_down[4]=1;
					    break;
				    case 'j'://三层下行
					    outer_down[3]=1;
					    break;
				    case 'k'://二层下行
					    outer_down[2]=1;
					    break;
				    default:
					    break;
				}//时间控制完毕(请求转换完毕)
			}
		}
	}
}
void Order()//打印剩余的指令
{
	int inner[10]={0};//1到9楼的内部请求（0无 1有）
	int outer_up[10]={0};//1到8楼的外部上行请求（0无 1有）
	int outer_down[10]={0};//2到9楼的外部下行请求（0无 1有）
	int i;
    time_control(inner,outer_up,outer_down);//控制剩余的时间指令
    for(i=1;i<=80;i++)
		printf("=");
	printf("电梯内部未完成指令:");
	for(i=1;i<=9;i++)
		if(inner[i]==1)
			printf("%d  ",i);
	printf("\t\t当前采用的策略为:");
	switch (strategy)
	{
	    case 1:
		    printf("先来先服务策略");
		    break;
	    case 2:
		    printf("顺便服务策略");
		    break;
	    default:
		    break;
	}
    printf("\n");
	printf("电梯外部未完成指令:");
	for(i=1;i<=8;i++)
		if(outer_up[i]==1)
			printf("%d楼上行  ",i);
	printf("\n");
	printf("\t\t");
	for(i=2;i<=9;i++)
		if(outer_down[i]==1)
			printf("%d楼下行  ",i);
	printf("\n");
	for(i=1;i<=80;i++)
		printf("=");
}

