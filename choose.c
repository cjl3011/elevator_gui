#include<stdio.h>
#include"elevator.h"
#include"egg.h"
HEGG hEggs[6];
extern HEGG main_egg;
void choose()
{
	SetActiveEgg(main_egg);
    switch(strategy)
	{
  		case 1:	
			while(bitmap==1);
			ng=1;
			hEggs[1]=LayEgg();
			SetActiveEgg(main_egg);
  		    MovePen(395,450);
  		    DrawBitmap("bitmap//strategy1.bmp");
			ng=0;
  		    break;
        case 2:
			while (bitmap==1);
			ng=1;
            hEggs[2]=LayEgg();
			SetActiveEgg(main_egg);
  		    MovePen(395,450);
  		    DrawBitmap("bitmap//strategy2.bmp");
			ng=0;
  		    break;
        default:
            break;
      }	
}
