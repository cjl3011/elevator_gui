#include"egg.h"
#include"elevator.h"
typedef struct key_info
{
	int leftup_x;
	int leftup_y;
	int rightdown_x;
	int rightdown_y;
	char bitmapR_name[27];
	char bitmapB_name[27];
}KEY;
extern HEGG main_egg;//�����ľ��
void act_string(char *string,int delay);//����Ҫ��ӡ���ַ����������ֵ�ʱ����,���ַ���̬��ӡ(Ҫ����<string.h>)
void egg_inner_condition(int floor,int dir)//��ӡegg��汾�����ڲ�������״̬��ʾ(floorΪ¥�� dirΪ���� 1�� -1�� 0ͣ -2����)
{
	while(bitmap==1);
	ng=1;
	SetActiveEgg(main_egg);
	while(bitmap==1);
	MovePen(1022,615);
	if(dir!=-2)//���ǿ���
	{
		switch(floor)
		{
			case 1:
				DrawBitmap("bitmap//��1.bmp");
				break;
			case 2:
				DrawBitmap("bitmap//��2.bmp");
				break;
				case 3:
				DrawBitmap("bitmap//��3.bmp");
				break;
			case 4:
				DrawBitmap("bitmap//��4.bmp");
				break;
			case 5:
				DrawBitmap("bitmap//��5.bmp");
				break;
			case 6:
				DrawBitmap("bitmap//��6.bmp");
				break;
			case 7:
				DrawBitmap("bitmap//��7.bmp");
				break;
			case 8:
				DrawBitmap("bitmap//��8.bmp");
				break;
			case 9:
				DrawBitmap("bitmap//��9.bmp");
				break;
			default:
				break;
		}
	}
	ng=0;
	while(bitmap==1);
	ng=0;
	MovePen(1022,548);
	if(dir==1)
		DrawBitmap("bitmap//�ڲ�����.bmp");
	else if(dir==-1)
		DrawBitmap("bitmap//�ڲ�����.bmp");
	else if(dir==-2)
	{
		MovePen(1022,615);
		DrawBitmap("bitmap//�ڲ�����.bmp");
	}
	else//=0
		DrawBitmap("bitmap//�ڲ�ͣ.bmp");
	ng=1;
	return;
}
void egg_outer_condition(int floor,int dir)//��ӡegg��汾�����ⲿ������״̬��ʾ(floorΪ¥�� dirΪ���� 1�� -1�� 0ͣ -2����)
{
	while(bitmap==1);
	ng=1;
	SetActiveEgg(main_egg);
	if(dir==1)
	{
		MovePen(843,326);
		DrawBitmap("bitmap//�ⲿ��2.bmp");
		MovePen(843,260);
		DrawBitmap("bitmap//�ⲿ��1.bmp");
	}
	else if(dir==-1)
	{
		MovePen(843,326);
		DrawBitmap("bitmap//�ⲿ��1.bmp");
		MovePen(843,260);
		DrawBitmap("bitmap//�ⲿ��2.bmp");
	}
	else
	{
		MovePen(843,326);
		DrawBitmap("bitmap//�ⲿ��1.bmp");
		MovePen(843,260);
		DrawBitmap("bitmap//�ⲿ��1.bmp");
	}
	ng=0;
	while(bitmap==1);
	ng=1;
	MovePen(843,192);
	switch(floor)
	{
		case 1:	
			DrawBitmap("bitmap//�ⲿ1.bmp");
			break;
		case 2:	
			DrawBitmap("bitmap//�ⲿ2.bmp");
			break;
		case 3:	
			DrawBitmap("bitmap//�ⲿ3.bmp");
			break;
		case 4:	
			DrawBitmap("bitmap//�ⲿ4.bmp");
			break;
		case 5:	
			DrawBitmap("bitmap//�ⲿ5.bmp");
			break;
		case 6:	
			DrawBitmap("bitmap//�ⲿ6.bmp");
			break;
		case 7:	
			DrawBitmap("bitmap//�ⲿ7.bmp");
			break;
		case 8:	
			DrawBitmap("bitmap//�ⲿ8.bmp");
			break;
		case 9:	
			DrawBitmap("bitmap//�ⲿ9.bmp");
			break;
		default:
			break;
	}
	ng=0;
	return;
}
