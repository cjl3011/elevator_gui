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
extern egg_order();//����egg��״̬�µ�������ʾ
extern void move_lift(int act);//ʵ�ֵ��ݵĶ�������(act=1 ��ʾ����һ�� act=-1��ʾ�½�1�� act=0ͣ�����л�ͼƬ act=2��ʾ����׼������)
extern void choose();//�ı���Ե�ͼƬ
extern int mouse_input();//egg�������
extern void egg_inner_condition(int floor,int dir);//��ӡegg��汾�����ڲ�������״̬��ʾ(floorΪ¥�� dirΪ���� 1�� -1�� 0ͣ)
extern void egg_outer_condition(int floor,int dir);//��ӡegg��汾�����ⲿ������״̬��ʾ(floorΪ¥�� dirΪ���� 1�� -1�� 0ͣ -2����)
extern int egg_tips();//��ӡegg��汾�ĳ�ʼ����ʾ��Ϣ
int Time=1;//��¼��ǰ����ʱ��
Input input[1001];//��¼�û�����������ָ��,�±��һ��ʼ
int size=0;//input����ĵ�ǰԪ�ظ���
int State=1;//��ʾ���ݵ�ǰ��״̬��/*0ֹͣ*/ 1���� -1�½� -2���У�
int output[1001]={0};//����ÿ������ʱ�̵ĵ���״̬�����飬�±��ʾʱ�䣨��output[0]=1��ʾ�����ڵ�0�봦�ڵ�һ�㣩
static Output position[1001];//��¼����1000�ڵ��������
int go=0;//=1��ʾGO�������� 
int delay=1000;//ÿ���ж��ȴ�ʱ��
int ratio=5;//�ȴ�ʱ��������ʱ��ı���
static int t=0;//=0��ʾget_input��������
static int output_way=1;//1��ʾ������ʽ��2��ʾ���ٷ�ʽ��3��ʾ��ȫ��ʽ
int strategy=1;//��ǰ��ȡ�Ĳ��Ժ�
HEGG main_egg;//�����ľ��
int step=0;//��Χ1-CUT ���߶���
int initial=0;
int ng=0;
int ask(char order);//�����û��������ָ��ж��Ƿ����ظ���ָ��,�ظ�����1�����򷵻�0
void getinput();//�����û����������룬��д�뵽��Ӧ�Ľṹ��������(*size ָ���Ӧ��ǰinput����Ĵ�С)
void state_d();//ת���������,������Ӧ�����input�е�is_done����
void hint();//��ӡ�û�����ָ����ʾ
void locate(int x, int y);//��λ����y�еĵ�x��
void clear();//XP�µĴ���system("command/ccls")����������
void print_s();//��ӡ���ݵ�����״��
int legal(char order);//�ж������Ƿ�Ϸ�,h�Ϸ�����1�����򷵻�0
void time_control(int inner[],int outer_up[],int outer_down[]);//�����������ڱ���ת�����������
void Order();//��ӡʣ���ָ��
//void deploy();//���е�������
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

										{'1',1103,133,1138,95,"bitmap//�ڲ�1.bmp","bitmap//�ڲ�1-1.bmp"},
										{'2',1103,202,1138,164,"bitmap//�ڲ�2.bmp","bitmap//�ڲ�2-1.bmp"},
										{'3',1103,268,1138,230,"bitmap//�ڲ�3.bmp","bitmap//�ڲ�3-1.bmp"},
										{'4',1103,336,1138,298,"bitmap//�ڲ�4.bmp","bitmap//�ڲ�4-1.bmp"},
										{'5',1022,133,1057,95,"bitmap//�ڲ�5.bmp","bitmap//�ڲ�5-1.bmp"},
										{'6',1022,202,1057,164,"bitmap//�ڲ�6.bmp","bitmap//�ڲ�6-1.bmp"},
										{'7',1022,268,1057,230,"bitmap//�ڲ�7.bmp","bitmap//�ڲ�7-1.bmp"},
										{'8',1022,336,1057,298,"bitmap//�ڲ�8.bmp","bitmap//�ڲ�8-1.bmp"},
										{'9',1022,405,1057,367,"bitmap//�ڲ�9.bmp","bitmap//�ڲ�9-1.bmp"},

										{'0',1116,460,1165,418,"bitmap//GO2.bmp","bitmap//GO1.bmp"},/*GO��*/
										{'Z',1047,457,1100,417,"bitmap//��GO2","bitmap//��GO1"},/*��GO��*/


										{'O',572,699,628,657,"",""},/*S1*/
										{'P',479,656,535,614,"",""},/*S2*/
										{'L',502,557,558,515,"",""},/*S3*/
										{'N',640,557,696,515,"",""},/*S4*/
										{'M',666,656,722,614,"",""}/*S5*/
														};
int main()
{	
	DWORD Thread1;
	HANDLE thread1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)getinput,NULL,0,&Thread1);//���߳�1
	DWORD Thread2;
	HANDLE thread2=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)mouse_input,NULL,0,&Thread2);//���߳�2(egg����)
	EggStart(1200,700);
	main_egg=LayEgg();
	//ShowConsoleWindow(0);
	initial=1;//��ɳ�ʼ��
	DrawBitmap("bitmap//����.bmp");
	ShowConsoleWindow(1);
    mciSendString("play zombie.wma repeat","",0,NULL);
	t=1;//��ʾgetinput��������
	output[1]=1;//������ݳ�ʼ״̬
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
     	    orders(output,input,Time,size,&State);//�����ȷ������
     	}
		else
		{
			int i;
			for(i=1;i<=size;i++)
				printf("%d %c %d\n",input[i].time,input[i].order,input[i].is_done);
			assist(output,Time,&State,input,size);//˳��������    
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
		Time++;//����ʱ������ƽ�
	}
	return 0;
}
void getinput()//�����û����������룬��д�뵽��Ӧ�Ľṹ��������(*size ָ���Ӧ��ǰinput����Ĵ�С)
{
	char ch[50];//�����ַ���
	int i=0;
	while(t==0);//�ȴ�����������
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
		while(ch[i]!='\0')//'\0'��ʾ�������
		{
			if(ch[i]=='O'||ch[i]=='o')//�����ȷ���
				strategy=1;
			if(ch[i]=='P'||ch[i]=='p')//˳�����
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
					State=1;//��ʼ��Ϊ����
			}
			i++;
		}
	}
}
void state_d()//ת���������,������Ӧ�����input�е�is_done����
{
	position[Time].floor=output[Time];
	if(output[Time+1]==output[Time]&&State!=-2)//��һ��ʱ�̺͵�ǰʱ�̵ĵ��ݲ�����ͬ�����ƶ���
	{
		int flag=0;//�ȴ�GO��ʱ��		
		go=0;
		position[Time].statue=0;
not_go://���²�GO��
		egg_outer_condition(output[Time],0);
		egg_inner_condition(output[Time],0);
		move_lift(0);
		SetActiveEgg(main_egg);
		while(bitmap==1);
		while(action==1);
		ng=1;
		MovePen(1013,461);
		DrawBitmap("bitmap//��GO2.bmp");
		ng=0;
		while(go==0&&flag<=ratio-2)//GO����û�б�����
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
			DrawBitmap("bitmap//GO1.bmp");//͵����
			ng=0;
			move_lift(2);
			while(bitmap==1);
			while(action==1);
			ng=1;
			SetActiveEgg(main_egg);
			MovePen(1096,461);
			DrawBitmap("bitmap//GO2.bmp");//͵����
			ng=0;
		}
		else//û��GO��
		{
			move_lift(2);
			go=1;
		}
		if(go!=1)//���˲�GO��
		{
			while(bitmap==1);
			while(action==1);
			ng=1;
			SetActiveEgg(main_egg);
			MovePen(1013,461);
			DrawBitmap("bitmap//��GO1.bmp");
			ng=0;
			goto not_go;
		}
		position[Time].statue=2;
		go=0;
	}
	else if(output[Time+1]==100*output[Time]||State==-2)//����
	{
		egg_outer_condition(output[Time],-2);
		egg_inner_condition(output[Time],-2);
		move_lift(-2);
		output[Time+1]=output[Time];
		position[Time].statue=-2;
	}
	else if(output[Time+1]>output[Time])//����Ҫ����
	{
		egg_outer_condition(output[Time],1);
		egg_inner_condition(output[Time],1);
		move_lift(1);
		State=1;
		position[Time].statue=1;
	}
	else//����Ҫ�½�
	{
		egg_outer_condition(output[Time],-1);
		egg_inner_condition(output[Time],-1);
		State=-1;
		position[Time].statue=-1;
		move_lift(-1);
	}
}
void print_s()//�������״̬
{
	int i;
	int min;
    min=max(1,Time-10);//��ӡ���11����¼
    printf("================�����������");
    for(i=1;i<=52;i++)
		printf("=");
	for(i=min;i<=Time;i++)
	{
		if(position[i].statue==-2||State==-2)//��ǰʱ��Ϊ����
			printf("��%dʱ��:������%d¥�����ڿ���״̬\n",i,position[i].floor);
		else if(position[i].statue==0)//��ǰʱ�̵��ݿ��ŵȴ�
			printf("��%dʱ��:������%d¥���ŵȴ�\n",i,position[i].floor);
		else if(position[i].statue==2)//����
			printf("��%dʱ��:������%d¥����\n",i,position[i].floor);
		else//��ǰʱ�̵���Ҫ���������½�
		    printf("��%dʱ��:���ݴ�%d¥��%d¥\n",i,position[i].floor,position[i].floor+position[i].statue);
	}
}
int ask(char order)//�����û��������ָ��ж��Ƿ����ظ���ָ��,�ظ�����1�����򷵻�0
{
	int i;
	for(i=1;i<=size;i++)
		if(input[i].order==order&&input[i].is_done==0)
			return 1;
    return 0;
}
void hint()//��ӡ�û�����ָ����ʾ
{
	printf("              |            ��������ʱ�л�����:                |\r\n");
	printf("              |  ��o��Ϊ�����ȷ�����ԣ�p��Ϊ˳��������     |\r\n");
	printf("              |    1-9��������ڳ˿Ͱ�Ŀ�갴ť,0����GO��      |\r\n");
	printf("              |  q��w��e��r��t��y��u��i��Ӧ8�㵽1����������� |\r\n");
	printf("              |  a��s��d��f��g��h��j��k��Ӧ9�㵽2����������� |\r\n");
	printf("              =================================================\r\n");
	printf("��������������ָ������س���:\n");
}
int legal(char order)//�ж������Ƿ�Ϸ�,�Ϸ�����1�����򷵻�0
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
void clear()//��������
{
	int i;
    locate(0,0);
	for(i=1;i<=250;i++)
		printf("\t");
	locate(0,0);
    return;
}
void locate(int x,int y)//��λ����y�еĵ�x��
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
void time_control(int inner[],int outer_up[],int outer_down[])//����ʱ�䣬�������������ڱ���ת�����������
{  
	int i;
	int floor=0;
    for(i=1;i<=size;i++)
	{
		if(input[i].is_done==0)//û�б���Ӧ������
		{
			if(input[i].order<='9'&&input[i].order>='1')//�ڲ�����
				inner[input[i].order-48]=1;
            else//�ⲿ����
			{
				switch(input[i].order)
				{
				    case 'q'://�˲�����
					    outer_up[8]=1;
					    break;
				    case 'w'://�߲�����
					    outer_up[7]=1;
					    break;
				    case 'e'://��������
					    outer_up[6]=1;
					    break;
				    case 'r'://�������
					    outer_up[5]=1;
					    break;
				    case 't'://�Ĳ�����
					    outer_up[4]=1;
					    break;
				    case 'y'://��������
					    outer_up[3]=1;
					    break;
				    case 'u'://��������
					    outer_up[2]=1;
					    break;
				    case 'i'://һ������
					    outer_up[1]=1;
					    break;
				    case 'a'://�Ų�����
					    outer_down[9]=1;
					    break;
				    case 's'://�˲�����
					    outer_down[8]=1;
					    break;
				    case 'd'://�߲�����
					    outer_down[7]=1;
					    break;
				    case 'f'://��������
					    outer_down[6]=1;
					    break;
				    case 'g'://�������
					    outer_down[5]=1;
					    break;
			        case 'h'://�Ĳ�����
					    outer_down[4]=1;
					    break;
				    case 'j'://��������
					    outer_down[3]=1;
					    break;
				    case 'k'://��������
					    outer_down[2]=1;
					    break;
				    default:
					    break;
				}//ʱ��������(����ת�����)
			}
		}
	}
}
void Order()//��ӡʣ���ָ��
{
	int inner[10]={0};//1��9¥���ڲ�����0�� 1�У�
	int outer_up[10]={0};//1��8¥���ⲿ��������0�� 1�У�
	int outer_down[10]={0};//2��9¥���ⲿ��������0�� 1�У�
	int i;
    time_control(inner,outer_up,outer_down);//����ʣ���ʱ��ָ��
    for(i=1;i<=80;i++)
		printf("=");
	printf("�����ڲ�δ���ָ��:");
	for(i=1;i<=9;i++)
		if(inner[i]==1)
			printf("%d  ",i);
	printf("\t\t��ǰ���õĲ���Ϊ:");
	switch (strategy)
	{
	    case 1:
		    printf("�����ȷ������");
		    break;
	    case 2:
		    printf("˳��������");
		    break;
	    default:
		    break;
	}
    printf("\n");
	printf("�����ⲿδ���ָ��:");
	for(i=1;i<=8;i++)
		if(outer_up[i]==1)
			printf("%d¥����  ",i);
	printf("\n");
	printf("\t\t");
	for(i=2;i<=9;i++)
		if(outer_down[i]==1)
			printf("%d¥����  ",i);
	printf("\n");
	for(i=1;i<=80;i++)
		printf("=");
}

