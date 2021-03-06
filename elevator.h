#ifndef CMC_H

#define CMC_H
//声明部分
typedef struct
{
	int time;//对应用户请求的仿真时间
	char order;//对应用户的请求指令
	int is_done;//1表示已经被完成，0表示没有被完成
}Input;
//main函数中储存用户指令的结构体

typedef struct
{
	int floor;//前一状态的楼层
	int statue;//这一个时间段需要执行的状态（=0开关门 =1上升 =-1下降 =-2空闲）
}Output;
//main函数中记录电梯输出的结构体数组

typedef struct
{
	char order;//对应的第一版本中的字符
	int leftup_x;//左上角坐标的x值
	int leftup_y;//左上角坐标的y值
	int rightdown_x;//右下角坐标的x值
	int rightdown_y;//右下角坐标的y值
	char bitmap_name1[25];//储存对应的图片1的名字（初始）
	char bitmap_name2[25];//储存对应的图片2的名字（有请求）
}mouse;

extern const mouse key_position[];//下表从0开始，记录每个键的信息

extern int Time;//记录当前仿真时间
extern Input input[1001];//记录用户的输入请求指令,下标从一开始
extern int size;//input数组的当前元素个数
extern int delay;//每次行动等待时间
extern int strategy;//当前采取的策略号
extern int go;//=1表示GO键被按下
extern int timer;//范围1-CUT 告诉动画该走第几步
extern int output[1001];//储存每个仿真时刻的电梯状态的数组，下标表示时间（如output[0]=1表示电梯在第0秒处于第一层）
extern int State;//表示电梯当前的状态（/*0停止*/ 1上升 -1下降 -2空闲） 
extern int ratio;//等待时间与上升时间的比例
extern int bitmap;//=0表示不在贴图 =1表示在贴图
extern int action;//=0表示不在动画 =1表示在动画
extern int initial;
extern int ng;

#define KEY_AMOUNT 33//键数
#define CUT 20//切片数
#define NAME1 "bitmap//外部上行2.bmp"
#define NAME2 "bitmap//外部下行2.bmp"
#define NAME3 "bitmap//外部上行.bmp"
#define NAME4 "bitmap//外部下行.bmp"

//声明部分
#endif

