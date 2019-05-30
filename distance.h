#pragma once
#include <stdio.h>
#include <math.h>
#define PI                      3.1415926
#define EARTH_RADIUS            6378.137        //地球近似半径

double radian(double d);
double get_distance(double lat1, double lng1, double lat2, double lng2);

const float B = 4 / PI;
const float C = -4 / (PI*PI);
const float P = 0.225;



// 求弧度
double radian(double d)
{
	return d * PI / 180.0;   //角度1? = π / 180
}


double mysin(double x);
double mycos(double x);
//计算距离
double get_distance(double lat1, double lng1, double lat2, double lng2);
double distance(double lat1, double lng1, double lat2, double lng2);
float get_diff_time(int a, int b); //a大b小

/*计算时间等的函数*/
//找到最长直道的方向角等数据
void get_straight_dire(Node* head);

//找到最长直道信息后，用此函数找出数据中符合方向角，经纬度要求的起点节点，后续可能要用此节点的时间等信息
Node* get_start_point(Node *head);

//判断当前起点是否越过了真正起点
bool iscrossed(Node *p);

//计算圈时,公式为（t2-delta_t2）-(t1-delata_t1),t1为上圈时间，delta_t1为上一圈插值
float laptime(Node *last_start, Node* this_start);

//判断当前节点是不是离起点距离最短的
//abandoned(三次计算distance吃不消)
void set_start(Node*lap, Node*new_circle);

void update_dis(float&prior_dis, float&dis, float&next_dis, Node*p);

float sum_dis(Node*a, Node*b);

void update_mileage(float&seg_mileage, float&mileage, Node *p);

//更新最快圈数据，包含加载数据，距离，时间，已经整体更新
float* load_fast_speed(Node*start, Node*last, float fast[500], float lat[500], float lng[500]);


/*最快圈时储存每两个节点之间的距离，后期如果优化计算负载可以在此函数内不用distance计算*/
/*因为在计算总里程的时候更新过,但需要额外的空间来保存dis变量，以空间换时间*/
float* load_fast_dis(Node*start, Node*last, float fast[500]);

int* load_fast_time(Node*start, Node*last, int time[500]);

void update_fast_lap(float lap_time, float &minlaptime, Node*last_start, Node*p);

//dis为当前车走过的总距离，start_time_lap是本圈起始时的时间，now_seconds是当前时间
float get_timediff(float dis, int start_time_lap, int now_seconds);


float get_timediff1(float lat, float lng, int start_time_lap, int now_seconds, int &new_index);
/*测试区代码，使用时需重写*/
void load_data(float direction[5000], float lat[5000], float lng[5000], int time[5000], float speed[5000]);



/*distance中函数的定义*/


double mysin(double x)                //泰勒展开求sin、cos，调用数学库函数单片机吃不消 
{
	float y = B * x + C * x * abs(x);
	y = P * (y * abs(y) - y) + y;
	return y;
}
double mycos(double x)
{
	return mysin(x + PI / 2);
}



//计算距离
double get_distance(double lat1, double lng1, double lat2, double lng2)                       //单位是km 
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



float get_diff_time(int a, int b) //a大b小                                //返回最小毫秒的两个时间的时间差 
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







/*load_data2node.h函数实现*/
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
	else printf("dire文件打开失败");
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
	else printf("lat文件打开失败");
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
	else printf("lng文件打开失败");
	return 0;
}
void load_data(const char*dire_path, const char* lat_path, const char*lng_path, Node*p)
{
	read_dire2node(dire_path, p);
	read_lat2node(lat_path, p);
	read_lng2node(lng_path, p);
}
/*一次只读一个*/

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
	else printf("dire文件打开失败");
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
	else printf("dire文件打开失败");
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
	else printf("dire文件打开失败");
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
	else printf("time文件打开失败");
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
	else printf("speed文件打开失败");
}










