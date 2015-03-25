#ifndef CMC_H

#define CMC_H
//��������
typedef struct
{
	int time;//��Ӧ�û�����ķ���ʱ��
	char order;//��Ӧ�û�������ָ��
	int is_done;//1��ʾ�Ѿ�����ɣ�0��ʾû�б����
}Input;
//main�����д����û�ָ��Ľṹ��

typedef struct
{
	int floor;//ǰһ״̬��¥��
	int statue;//��һ��ʱ�����Ҫִ�е�״̬��=0������ =1���� =-1�½� =-2���У�
}Output;
//main�����м�¼��������Ľṹ������

typedef struct
{
	char order;//��Ӧ�ĵ�һ�汾�е��ַ�
	int leftup_x;//���Ͻ������xֵ
	int leftup_y;//���Ͻ������yֵ
	int rightdown_x;//���½������xֵ
	int rightdown_y;//���½������yֵ
	char bitmap_name1[25];//�����Ӧ��ͼƬ1�����֣���ʼ��
	char bitmap_name2[25];//�����Ӧ��ͼƬ2�����֣�������
}mouse;

extern const mouse key_position[];//�±��0��ʼ����¼ÿ��������Ϣ

extern int Time;//��¼��ǰ����ʱ��
extern Input input[1001];//��¼�û�����������ָ��,�±��һ��ʼ
extern int size;//input����ĵ�ǰԪ�ظ���
extern int delay;//ÿ���ж��ȴ�ʱ��
extern int strategy;//��ǰ��ȡ�Ĳ��Ժ�
extern int go;//=1��ʾGO��������
extern int timer;//��Χ1-CUT ���߶������ߵڼ���
extern int output[1001];//����ÿ������ʱ�̵ĵ���״̬�����飬�±��ʾʱ�䣨��output[0]=1��ʾ�����ڵ�0�봦�ڵ�һ�㣩
extern int State;//��ʾ���ݵ�ǰ��״̬��/*0ֹͣ*/ 1���� -1�½� -2���У� 
extern int ratio;//�ȴ�ʱ��������ʱ��ı���
extern int bitmap;//=0��ʾ������ͼ =1��ʾ����ͼ
extern int action;//=0��ʾ���ڶ��� =1��ʾ�ڶ���
extern int initial;
extern int ng;

#define KEY_AMOUNT 33//����
#define CUT 20//��Ƭ��
#define NAME1 "bitmap//�ⲿ����2.bmp"
#define NAME2 "bitmap//�ⲿ����2.bmp"
#define NAME3 "bitmap//�ⲿ����.bmp"
#define NAME4 "bitmap//�ⲿ����.bmp"

//��������
#endif

