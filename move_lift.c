#include"egg.h"
#include"elevator.h"
extern HEGG main_egg;//�����ľ��
int action=0;//=0��ʾ���ڶ��� =1��ʾ�ڶ���
void move_lift(int act)//ʵ�ֵ��ݵĶ�������(act=1 ��ʾ����һ�� act=-1��ʾ�½�1�� act=0ͣ�����л�ͼƬ act=2��ʾ����׼������ act=-2��ʾ����)
{
	static HEGG egg1=NULL;//���ݵ������ר���ڵ��ݵĶ���
	int i;
	static int flag=0;//û����
	if(egg1==NULL)
	{
		while(bitmap==1);
		egg1=LayEgg();
		MovePen(11,114);
		DrawBitmap("bitmap//����1.bmp");
	}//���ݵ��ĳ�ʼ��
	switch (act)
	{
	case 1://��һ��
		if(flag==1)
		{
			while(bitmap==1);
			action=1;
			SetActiveEgg(egg1);
			MovePen(GetPenXPos()-265,GetPenYPos());
			DrawBitmap("bitmap//����1.bmp");
			action=0;
			SetActiveEgg(main_egg);
			flag=0;
		}
		for(i=1;i<=CUT;i++)
		{
			while(bitmap==1);
			action=1;
			SetActiveEgg(egg1);
			MoveEgg(GetEggXPos(),GetEggYPos()+3.175);
			action=0;
			WaitFor(delay/CUT);
		}
		break;
	case -1://��һ��
		if(flag==1)
		{
			while(bitmap==1);
			SetActiveEgg(egg1);
			action=1;
			MovePen(GetPenXPos()-265,GetPenYPos());
			DrawBitmap("bitmap//����1.bmp");
			action=0;
			flag=0;
			SetActiveEgg(main_egg);
		}
		for(i=1;i<=CUT;i++)
		{
			while(bitmap==1);
			action=1;
			SetActiveEgg(egg1);
			MoveEgg(GetEggXPos(),GetEggYPos()-3.175);
			action=0;
			WaitFor(delay/CUT);
		}
		break;
	case 0://ͣ��
		while(bitmap==1);
		SetActiveEgg(egg1);
		MovePen(GetPenXPos()-265,GetPenYPos());
		DrawBitmap("bitmap//����2.bmp");

	{
		SetActiveEgg(main_egg);
		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������1.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������2.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������3.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������4.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������5.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������6.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������7.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������8.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������9.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������10.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������11.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		MovePen(391,349);
		DrawBitmap("bitmap//������12.bmp");
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������13.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������14.bmp");
		action=0;
		WaitFor(delay/CUT);

		
		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������15.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������16.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������17.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������18.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������19.bmp");
		action=0;
		WaitFor(delay/CUT);

		while(bitmap==1);
		action=1;
		MovePen(391,349);
		DrawBitmap("bitmap//������20.bmp");
		action=0;
	}//һ�׵��ݿ��Ŷ���
		break;
	case 2://���ų���
		while(bitmap==1);
		SetActiveEgg(egg1);
		MovePen(GetPenXPos()-265,GetPenYPos());
		DrawBitmap("bitmap//����1.bmp");
		{
			SetActiveEgg(main_egg);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������20.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������19.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������18.bmp");
			action=0;
			WaitFor(delay/CUT);

			
			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������17.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������16.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������15.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������14.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������13.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������12.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������11.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������10.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������9.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������8.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������7.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������6.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������5.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������4.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������3.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������2.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������1.bmp");
			action=0;
			WaitFor(delay/CUT);

			while(bitmap==1);
			action=1;
			MovePen(391,349);
			DrawBitmap("bitmap//������.bmp");
			action=0;
		}
		break;
	case -2://����
		flag=1;//������
		while(bitmap==1);
		SetActiveEgg(egg1);
		MovePen(GetPenXPos()-265,GetPenYPos());
		DrawBitmap("bitmap//����0.bmp");
		WaitFor(delay);
		break;
	default:
		break;
	}
	SetActiveEgg(main_egg);
	return;
}
