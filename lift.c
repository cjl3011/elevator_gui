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
extern HEGG main_egg;//主蛋的句柄
void act_string(char *string,int delay);//传进要打印的字符，和字与字的时间间隔,让字符动态打印(要包含<string.h>)
void egg_inner_condition(int floor,int dir)//打印egg库版本电梯内部的运行状态提示(floor为楼层 dir为方向 1上 -1下 0停 -2空闲)
{
	while(bitmap==1);
	ng=1;
	SetActiveEgg(main_egg);
	while(bitmap==1);
	MovePen(1022,615);
	if(dir!=-2)//不是空闲
	{
		switch(floor)
		{
			case 1:
				DrawBitmap("bitmap//内1.bmp");
				break;
			case 2:
				DrawBitmap("bitmap//内2.bmp");
				break;
				case 3:
				DrawBitmap("bitmap//内3.bmp");
				break;
			case 4:
				DrawBitmap("bitmap//内4.bmp");
				break;
			case 5:
				DrawBitmap("bitmap//内5.bmp");
				break;
			case 6:
				DrawBitmap("bitmap//内6.bmp");
				break;
			case 7:
				DrawBitmap("bitmap//内7.bmp");
				break;
			case 8:
				DrawBitmap("bitmap//内8.bmp");
				break;
			case 9:
				DrawBitmap("bitmap//内9.bmp");
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
		DrawBitmap("bitmap//内部上行.bmp");
	else if(dir==-1)
		DrawBitmap("bitmap//内部下行.bmp");
	else if(dir==-2)
	{
		MovePen(1022,615);
		DrawBitmap("bitmap//内部空闲.bmp");
	}
	else//=0
		DrawBitmap("bitmap//内部停.bmp");
	ng=1;
	return;
}
void egg_outer_condition(int floor,int dir)//打印egg库版本电梯外部的运行状态提示(floor为楼层 dir为方向 1上 -1下 0停 -2空闲)
{
	while(bitmap==1);
	ng=1;
	SetActiveEgg(main_egg);
	if(dir==1)
	{
		MovePen(843,326);
		DrawBitmap("bitmap//外部上2.bmp");
		MovePen(843,260);
		DrawBitmap("bitmap//外部下1.bmp");
	}
	else if(dir==-1)
	{
		MovePen(843,326);
		DrawBitmap("bitmap//外部上1.bmp");
		MovePen(843,260);
		DrawBitmap("bitmap//外部下2.bmp");
	}
	else
	{
		MovePen(843,326);
		DrawBitmap("bitmap//外部上1.bmp");
		MovePen(843,260);
		DrawBitmap("bitmap//外部下1.bmp");
	}
	ng=0;
	while(bitmap==1);
	ng=1;
	MovePen(843,192);
	switch(floor)
	{
		case 1:	
			DrawBitmap("bitmap//外部1.bmp");
			break;
		case 2:	
			DrawBitmap("bitmap//外部2.bmp");
			break;
		case 3:	
			DrawBitmap("bitmap//外部3.bmp");
			break;
		case 4:	
			DrawBitmap("bitmap//外部4.bmp");
			break;
		case 5:	
			DrawBitmap("bitmap//外部5.bmp");
			break;
		case 6:	
			DrawBitmap("bitmap//外部6.bmp");
			break;
		case 7:	
			DrawBitmap("bitmap//外部7.bmp");
			break;
		case 8:	
			DrawBitmap("bitmap//外部8.bmp");
			break;
		case 9:	
			DrawBitmap("bitmap//外部9.bmp");
			break;
		default:
			break;
	}
	ng=0;
	return;
}
