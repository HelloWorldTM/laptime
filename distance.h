#pragma once
#include <stdio.h>
#include <math.h>
#define PI                      3.1415926
#define EARTH_RADIUS            6378.137        //������ư뾶

double radian(double d);
double get_distance(double lat1, double lng1, double lat2, double lng2);

const float B = 4 / PI;
const float C = -4 / (PI*PI);
const float P = 0.225;



// �󻡶�
double radian(double d)
{
	return d * PI / 180.0;   //�Ƕ�1? = �� / 180
}


double mysin(double x);
double mycos(double x);
//�������
double get_distance(double lat1, double lng1, double lat2, double lng2);
double distance(double lat1, double lng1, double lat2, double lng2);
float get_diff_time(int a, int b); //a��bС

/*����ʱ��ȵĺ���*/
//�ҵ��ֱ���ķ���ǵ�����
void get_straight_dire(Node* head);

//�ҵ��ֱ����Ϣ���ô˺����ҳ������з��Ϸ���ǣ���γ��Ҫ������ڵ㣬��������Ҫ�ô˽ڵ��ʱ�����Ϣ
Node* get_start_point(Node *head);

//�жϵ�ǰ����Ƿ�Խ�����������
bool iscrossed(Node *p);

//����Ȧʱ,��ʽΪ��t2-delta_t2��-(t1-delata_t1),t1Ϊ��Ȧʱ�䣬delta_t1Ϊ��һȦ��ֵ
float laptime(Node *last_start, Node* this_start);

//�жϵ�ǰ�ڵ��ǲ�������������̵�
//abandoned(���μ���distance�Բ���)
void set_start(Node*lap, Node*new_circle);

void update_dis(float&prior_dis, float&dis, float&next_dis, Node*p);

float sum_dis(Node*a, Node*b);

void update_mileage(float&seg_mileage, float&mileage, Node *p);

//�������Ȧ���ݣ������������ݣ����룬ʱ�䣬�Ѿ��������
float* load_fast_speed(Node*start, Node*last, float fast[500], float lat[500], float lng[500]);


/*���Ȧʱ����ÿ�����ڵ�֮��ľ��룬��������Ż����㸺�ؿ����ڴ˺����ڲ���distance����*/
/*��Ϊ�ڼ�������̵�ʱ����¹�,����Ҫ����Ŀռ�������dis�������Կռ任ʱ��*/
float* load_fast_dis(Node*start, Node*last, float fast[500]);

int* load_fast_time(Node*start, Node*last, int time[500]);

void update_fast_lap(float lap_time, float &minlaptime, Node*last_start, Node*p);

//disΪ��ǰ���߹����ܾ��룬start_time_lap�Ǳ�Ȧ��ʼʱ��ʱ�䣬now_seconds�ǵ�ǰʱ��
float get_timediff(float dis, int start_time_lap, int now_seconds);


float get_timediff1(float lat, float lng, int start_time_lap, int now_seconds, int &new_index);
/*���������룬ʹ��ʱ����д*/
void load_data(float direction[5000], float lat[5000], float lng[5000], int time[5000], float speed[5000]);



/*distance�к����Ķ���*/


double mysin(double x)                //̩��չ����sin��cos��������ѧ�⺯����Ƭ���Բ��� 
{
	float y = B * x + C * x * abs(x);
	y = P * (y * abs(y) - y) + y;
	return y;
}
double mycos(double x)
{
	return mysin(x + PI / 2);
}



//�������
double get_distance(double lat1, double lng1, double lat2, double lng2)                       //��λ��km 
{
	double radLat1 = radian(lat1);
	double radLat2 = radian(lat2);
	double a = radLat1 - radLat2;
	double b = radian(lng1) - radian(lng2);
	double dst = 2 * asin((sqrt(pow(mysin(a / 2), 2) + mycos(radLat1) * mycos(radLat2) * pow(mysin(b / 2), 2))));
	//double dst = 2 * asin((sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2))));

	dst = dst * EARTH_RADIUS;
	dst = round(dst * 10000) / 10000;
	return dst;
}



double distance(double lat1, double lng1, double lat2, double lng2)
{

	double dst = get_distance(lat1, lng1, lat2, lng2);
	return dst;
}



float get_diff_time(int a, int b) //a��bС                                //������С���������ʱ���ʱ��� 
{
	int minute = a / 1000 - b / 1000;
	int second = a / 10 % 100 - b / 10 % 100;
	int msecond = a % 10 - b % 10;
	if (second < 0)
	{
		second = second + 60;
		minute -= 1;
	}
	if (msecond < 0)
	{
		msecond = msecond + 10;
		second -= 1;
	}
	float time = float(minute * 60) + float(second) + float(msecond) / 10;
	return time;
}







/*load_data2node.h����ʵ��*/
float* read_dire2node(const char *path, Node *head)
{
	FILE *f;
	fopen_s(&f, path, "r");
	Node *p = head;
	if (f != NULL)
	{
		while (p != NULL)
		{
			fscanf_s(f, "%f", &p->direction, sizeof(float));
			//printf("%f\n", p->direction);
			p = p->next;
		}
		fclose(f);
		return 0;
	}
	else printf("dire�ļ���ʧ��");
	return 0;
}
float* read_lat2node(const char *path, Node *head)
{
	FILE *f;
	fopen_s(&f, path, "r");
	Node *p = head;
	if (f != NULL)
	{
		while (p != NULL)
		{
			fscanf_s(f, "%f", &p->latitude, sizeof(float));
			//printf("%f\n", p->direction);
			p = p->next;
		}
		fclose(f);
		return 0;
	}
	else printf("lat�ļ���ʧ��");
	return 0;
}
float* read_lng2node(const char *path, Node *head)
{
	FILE *f;
	fopen_s(&f, path, "r");
	Node *p = head;
	if (f != NULL)
	{
		while (p != NULL)
		{
			fscanf_s(f, "%f", &p->longitude, sizeof(float));
			//printf("%f\n", p->direction);
			p = p->next;
		}
		fclose(f);
		return 0;
	}
	else printf("lng�ļ���ʧ��");
	return 0;
}
void load_data(const char*dire_path, const char* lat_path, const char*lng_path, Node*p)
{
	read_dire2node(dire_path, p);
	read_lat2node(lat_path, p);
	read_lng2node(lng_path, p);
}
/*һ��ֻ��һ��*/

float* read_dire2node_once(const char*path, float dire[5000])
{
	FILE *f;
	int index = 0;
	fopen_s(&f, path, "r");
	if (f != NULL)
	{
		while (EOF != fscanf_s(f, "%f", &dire[index], sizeof(float)))
		{
			index++;
		}
		fclose(f);
		return dire;
	}
	else printf("dire�ļ���ʧ��");
	return dire;
}
float* read_lat2node_once(const char*path, float lat[5000])
{
	FILE *f;
	int index = 0;
	fopen_s(&f, path, "r");
	if (f != NULL)
	{
		while (EOF != fscanf_s(f, "%f", &lat[index], sizeof(float)))
		{
			index++;
		}
		fclose(f);
		return lat;
	}
	else printf("dire�ļ���ʧ��");
	return lat;
}
float* read_lng2node_once(const char*path, float lng[5000])
{
	FILE *f;
	int index = 0;
	fopen_s(&f, path, "r");
	if (f != NULL)
	{
		while (EOF != fscanf_s(f, "%f", &lng[index], sizeof(float)))
		{
			index++;
		}
		fclose(f);
		return lng;
	}
	else printf("dire�ļ���ʧ��");
	return lng;
}

int* read_time2node_once(const char*path, int time[5000])
{
	FILE *f;
	int index = 0;
	fopen_s(&f, path, "r");
	if (f != NULL)
	{
		while (EOF != fscanf_s(f, "%d", &time[index], sizeof(int)))
		{
			index++;
		}
		fclose(f);
		return time;
	}
	else printf("time�ļ���ʧ��");
	return time;
}
void read_speed2node_once(const char*path, float speed[5000])
{
	FILE *f;
	int index = 0;
	fopen_s(&f, path, "r");
	if (f != NULL)
	{
		while (EOF != fscanf_s(f, "%f", &speed[index], sizeof(float)))
		{
			index++;
		}
		fclose(f);
	}
	else printf("speed�ļ���ʧ��");
}










