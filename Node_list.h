#pragma once
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef signed char int8_t;
typedef signed short int  int16_t;
typedef signed int  int32_t;
typedef signed long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int  uint32_t;
typedef unsigned long long uint64_t;


//节点结构体，每个节点分别保存了一个指向前一个节点的指针和指向后一个节点的指针，以及保存数据的指针

//定义双向链表的节点 
typedef struct Node
{
	struct Node *prior;
	struct Node *next;
	float longitude; //经度
	float latitude;  //纬度
	float speed;     //速度
	uint32_t seconds;//unix 时间戳
	uint16_t millisecondes;//毫秒数
	float direction; //方位角，正北为0度
};

//初始化一个链表的节点
Node* create_node(void);

//建立含有N个结点的双向链表
Node* create_list(int n);


//链表的长度
int len_list(Node * node);


//定位到链表的任意位置
Node* pos_list(Node *head, int n);


//正向遍历一个链表
void out_front_list(Node *head);

//反向遍历一个链表
void out_reverse_list(Node *head);

//在链表的头部插入结点
Node* start_insert_list(Node *head);

//将现有节点插入现有链表末尾
void insert_list(Node *head, Node *p);


//在链表的尾部插入结点
Node* end_insert_list(Node *head);


//插入到任意位置之前
Node* insert_befor_list(Node *head, int a);

//插入到任意位置之后 
Node* insert_after_list(Node *head, int a);

//删除头结点
Node* delect_start_list(Node *head);


//删除尾结点
Node* delect_end_list(Node *head);


//删除指定位置的节点
Node* delect_list(Node *head, int i);

//填充数据到节点
void fill_node_once(float dire, float lat, float lng, int time, float speed, Node * head);

//写数据到文件
void write_lap(float timediff);

//两个节点之间的距离
int dis_node(Node* start, Node* end);

//转到后面的第n个节点，若后面没有n个节点，则返回最后一个节点
Node* jump_node_forward(Node* p, int n);

Node* jump_node_back(Node* p, int n);


/*代码实现*/ 
Node* create_node(void)
{
	Node *p;
	p = (Node*)malloc(sizeof(Node));
	if (p == NULL)
	{
		printf("动态内存分配失败！\n");
		exit(0);
	}
	p->prior = NULL;
	p->next = NULL;
	return (p);
}

//建立含有N个结点的双向链表
Node* create_list(int n)
{
	Node *p = NULL, *new1 = NULL, *head = NULL;
	int i;
	if (n >= 1)                    //结点的个数 >= 1 的时候，先生成第一个结点 
	{
		new1 = create_node();
		head = new1;
		p = new1;
	}
	for (i = 2; i <= n; i++)    //生成第一个结点以后的结点，并建立双向链表的关系 
	{
		new1 = create_node();
		p->next = new1;
		new1->prior = p;
		p = new1;
	}
	if (n >= 1)
		return (head);
	else
		return 0;
}

//链表的长度
int len_list(Node * node)
{
	Node*p = node;
	int len = 0;
	while (p != NULL)
	{
		p = p->next;
		len++;
	}
	return len;
}

//定位到链表的任意位置
Node* pos_list(Node *head, int n)
{
	int i = 1;
	Node *p = NULL;
	if (i <= n)
	{
		p = head;
		for (i = 2; i <= n; i++)
			p = p->next;
	}
	return p;
}

//正向遍历一个链表
void out_front_list(Node *head)
{
	if (head == NULL)
	{
		printf("输入的链表信息有误，链表不存在！\n");
	}
	else
	{
		Node *p;
		p = head;
		while (p != NULL)
		{
			printf("%d  ", p->seconds);
			p = p->next;
		}
	}
}

//反向遍历一个链表
void out_reverse_list(Node *head)
{
	if (head == NULL)
	{
		printf("输入的链表信息有误，链表不存在！\n");
	}
	else
	{
		int n;
		n = len_list(head);
		Node *p;
		p = pos_list(head, n);
		while (p != NULL)
		{
			printf("%d  ", p->seconds);
			p = p->prior;
		}
	}
}

//在链表的头部插入结点
Node* start_insert_list(Node *head)
{
	Node *p;
	p = create_node();
	p->next = head;
	head->prior = p;
	head = p;
	return (p);
}
//将现有节点插入现有链表末尾
void insert_list(Node *head, Node *p)
{
	int n;
	n = len_list(head);
	head = pos_list(head, n);
	p->prior = head;
	head->next = p;
}

//在链表的尾部插入结点
Node* end_insert_list(Node *head)
{
	int n;
	n = len_list(head);
	Node *p, *new1;
	new1 = create_node();
	p = pos_list(head, n);
	p->next = new1;
	new1->prior = p;
	return (head);
}

//插入到任意位置之前
Node* insert_befor_list(Node *head, int a)
{
	int  newlen;
	Node *pos, *p;
	newlen = len_list(head);
	if (a > newlen)
	{
		head = end_insert_list(head);
	}
	else
	{
		if (a <= 1)
		{
			head = start_insert_list(head);
		}
		else
		{
			pos = pos_list(head, a);
			p = create_node();
			pos->prior->next = p;
			p->prior = pos->prior;
			p->next = pos;
			pos->prior = p;
		}
	}
	return (head);
}

//插入到任意位置之后 
Node* insert_after_list(Node *head, int a)
{
	int  newlen;
	Node *pos, *p;
	newlen = len_list(head);
	if (a >= newlen)
	{
		head = end_insert_list(head);
	}
	else
	{
		if (a < 1)
		{
			head = start_insert_list(head);
		}
		else
		{
			pos = pos_list(head, a);
			p = create_node();
			p->next = pos->next;
			pos->next->prior = p;
			pos->next = p;
			p->prior = pos;
		}
	}
	return (head);
}
//删除头结点
Node* delect_start_list(Node *head)
{
	Node *pos;
	pos = head;
	head = head->next;
	head->prior = NULL;
	free(pos);
	return(head);
}

//删除尾结点
Node* delect_end_list(Node *head)
{
	Node *p, *pos;
	int newlen;
	newlen = len_list(head);
	pos = pos_list(head, newlen);
	p = pos;
	p = p->prior;
	p->next = NULL;
	free(pos);
	return (head);
}

//删除指定位置的节点
Node* delect_list(Node *head, int i)
{
	int newlen;
	Node *pos;
	newlen = len_list(head);
	if (i <= 1)
		head = delect_start_list(head);
	else if (i >= newlen)
		head = delect_end_list(head);
	else
	{
		pos = pos_list(head, i);
		pos->prior->next = pos->next;
		pos->next->prior = pos->prior;
		free(pos);
	}
	return(head);
}
//填充数据到节点
void fill_node_once(float dire, float lat, float lng, int time, float speed, Node * head)
{
	head->direction = dire;
	head->latitude = lat;
	head->longitude = lng;
	head->seconds = time;
	head->speed = speed;
}
void write_lap(float timediff)
{
	FILE*f = fopen("C:\\Users\\Administrator\\Desktop\\2.txt", "a");
	fprintf(f, "%.2f\n", timediff);
	fclose(f);
}
int dis_node(Node* start, Node* end)               //求节点之间的距离 
{
	if (start == NULL || end == NULL) 
	{
		printf("求节点之间距离是参数为NULL");
		return 0;
	}
	int dis = 0;
	while (start != end) 
	{
		dis++;
		start = start->next;
		if (dis > 1000000) 
		{
			printf("节点之间距离过大");
			return 1000000;
		}
		return dis;
	}
}
Node* jump_node_forward(Node* p, int n)                              //跳到第n个节点之后 
{
	for (int i = 0; i < n; i++)
	{
		if (p->next != NULL)
			p = p->next;
		else return p;
	}
	return p;
}
Node* jump_node_back(Node * p, int n)                               //跳到第n个节点之前 
{
	for (int i = 0; i < n; i++)
	{
		if (p->prior != NULL)
			p = p->prior;
		else return p;
	}
	return p;
}

/*其他函数*/
void get_straight_dire(Node* head)
{
	Node*p                     = head;
	Node*max_length_start_node = NULL;//最长直道起始节点
	Node*max_length_end_node   = NULL;//最长直道末尾节点
	int maxlength              = 0;   //最长直道长度
	while (p->next)
	{
		int temp_maxlength = 0;                 //最长方向角不变的节点长度
		Node*q = p;
		float dire = p->direction;
		float a = q->next->direction;
		while (abs(dire - a) < direction_change)//方向角没动
		{
			q = q->next;
			if (q->next != NULL)
			{
				temp_maxlength++;
				a = q->next->direction;
			}
			else break;
		}
		if (temp_maxlength > maxlength)         //当前为最大长度
		{
			maxlength = temp_maxlength;
			max_length_start_node = p;
			max_length_end_node = q;
			start_point_direction = dire;
		}
		p = p->next;
	}
	//根据最长直道端点计算直道长度,起点经纬度，方向角
	max_straight_length = distance(max_length_start_node->latitude, max_length_start_node->longitude, max_length_end_node->latitude, max_length_end_node->longitude);
	start_point_lat = (max_length_start_node->latitude + max_length_end_node->latitude) / 2;
	start_point_lng = (max_length_start_node->longitude + max_length_end_node->longitude) / 2;
}

//找到最长直道信息后，用此函数找出数据中符合方向角，经纬度要求的起点节点，后续可能要用此节点的时间等信息
Node* get_start_point(Node *head)
{
	if (head == NULL)
	{
		printf("ERROR in get_start_point：参数节点为空");
		return NULL;
	}
	int num = 0;
	Node * p = NULL;
	while (head->next != NULL)
	{
		if (abs(head->direction - start_point_direction) < 2) //方向角差距小于2
		{
			bool dec = head->latitude >= start_point_lat && head->next->latitude < start_point_lat;         //候选点的纬度和next的纬度包含起点纬度
			bool inc = head->latitude <= start_point_lat && head->next->latitude > start_point_lat;         //候选点的经度和next的经度包含起点经度 
			if (dec | inc)
			{
				num++;
				printf("候选点：lat:%f，lng:%f,time:%d\n", head->latitude, head->longitude, head->seconds);
				p = head;
			}
		}
		head = head->next;
	}
	if (num == 1)
	{
		printf("起点 lat:%f,lng:%f,dire:%f\n", p->latitude, p->longitude, p->direction);
		return p;
	}
	else if (num == 0)
	{
		printf("未找到起始节点");
		return NULL;
	}
	else
	{
		printf("存在多个候选节点！，请更改候选节点选择模式 候选节点数：%d", num);
		return NULL;
	}
}

/*判断当前起点是否越过了真正起点*/
bool iscrossed(Node *p)                               //keneng 
{
	if (p == NULL)
	{
		printf("ERROR in iscrossed：参数节点为空");
		return NULL;
	}
	float last_node_dis = 0, next_node_dis = 0;
	last_node_dis = distance(p->prior->latitude, p->prior->longitude, start_point_lat, start_point_lng);
	next_node_dis = distance(p->next->latitude, p->next->longitude, start_point_lat, start_point_lng);
	if (last_node_dis < next_node_dis)
	{
		return true;
	}
	else return false;
}
/*计算圈时,公式为（t2-delta_t2）-(t1-delata_t1),t1为上圈时间，delta_t1为上一圈插值*/
float laptime(Node *last_start, Node* this_start) //
{
	if (last_start == NULL || this_start == NULL)
	{
		printf("ERROR in laptime：参数节点为空");
		return 0;
	}
	float delta_t1 = 0, delta_t2 = 0, t1 = 0, t2 = 0;
	delta_t1 = 1000 * distance(last_start->latitude, last_start->longitude, start_point_lat, start_point_lng) / last_start->speed;
	delta_t2 = 1000 * distance(this_start->latitude, this_start->longitude, start_point_lat, start_point_lng) / this_start->speed;
	if (!iscrossed(last_start)) //上一个节点是没越过的
	{
		delta_t1 = -delta_t1;
	}
	if (!iscrossed(this_start)) //本次节点未越过起点
	{
		delta_t2 = -delta_t2;
	}
	printf("插值时间%f(-)", delta_t2 - delta_t1);
	return get_diff_time(this_start->seconds, last_start->seconds) - delta_t2 + delta_t1;
}
/*判断当前节点是不是离起点距离最短的*/
void set_start(Node*new_circle)
{
	start_point_lat = new_circle->latitude;//找到后更新起点位置数据（旧起点是平均值，没有准确时间）
	start_point_lng = new_circle->longitude;
	lap_count = 1;//当前为第一圈
}
void update_dis(float&prior_dis, float&dis, float&next_dis, Node*p)
{
	prior_dis = dis;
	dis = next_dis;
	next_dis = distance(start_point_lat, start_point_lng, p->latitude, p->longitude);
}
float sum_dis(Node*a, Node*b)
{
	float sum = 0;
	if (a == NULL || b == NULL)
	{
		printf("ERROR in sun_dis:参数为空");
		return 0;
	}
	while (a != b)
	{
		sum += distance(a->latitude, a->longitude, a->next->latitude, a->next->longitude);
		a = a->next;
	}
	return sum;
}
void update_mileage(float&seg_mileage, float&mileage, Node *p)
{
	seg_mileage = distance(p->latitude, p->longitude, p->next->latitude, p->next->longitude);
	//总里程
	mileage += seg_mileage;
}
/*更新最快圈数据，包含加载数据，距离，时间，已经整体更新*/
float* load_fast_speed(Node*start, Node*last, float fast[500], float lat[500], float lng[500])
{
	int i = 0;

	while (start->prior != last)
	{
		fast[i] = start->speed;
		lat[i] = start->latitude;
		lng[i] = start->longitude;
		i++;
		start = start->next;
	}
	/*将最后所有数据填充为最后一个速度，方便之后实时计算时间*/
	int last_index = i - 1;
	for (i; i < 500; i++)
	{
		fast[i] = fast[last_index];
		lat[i] = enumber;
		lng[i] = enumber;
	}
	return fast;
}

/*最快圈时储存每两个节点之间的距离，后期如果优化计算负载可以在此函数内不用distance计算
  因为在计算总里程的时候更新过,但需要额外的空间来保存dis变量，以空间换时间*/
float* load_fast_dis(Node*start, Node*last, float fast[500])
{
	int i = 1;
	fast[0] = 0;//待优化，可以由是否越过起始点和距离起始点距离来改进
	float temp_dis;
	while (start->prior != last)
	{
		temp_dis = distance(start->latitude, start->longitude, start->next->latitude, start->next->longitude);
		fast[i] = temp_dis + fast[i - 1];
		//printf("目前距离为：%f\n", fast[i]);
		i++;
		start = start->next;
	}
	//将最后所有数据填充为最后一个速度，方便之后实时计算时间
	int last_index = i - 1;
	for (i; i < 500; i++)
	{
		fast[i] = fast[last_index];
	}
	return fast;
}
int* load_fast_time(Node*start, Node*last, int time[500])
{
	int i = 0;

	while (start->prior != last)
	{
		time[i] = start->seconds;
		i++;
		start = start->next;
	}
	//将最后所有数据填充为enumber
	int last_index = i - 1;
	for (i; i < 500; i++)
	{
		time[i] = enumber;

	}
	return time;

}
void update_fast_lap(float lap_time, float &minlaptime, Node*last_start, Node*p)
{
	if (lap_time < minlaptime)
	{
		minlaptime = lap_time;
		load_fast_speed(last_start, p, fastest_lap_speed, fastest_lap_lat, fastest_lap_lng);//更新最快圈速度,经纬度
		load_fast_dis(last_start, p, fastest_lap_dis);//更新最快圈每段距离
		load_fast_time(last_start, p, fastest_lap_time);//更新最快圈每段时间戳
		fast_start = last_start;
		fast_end = p;
	}
}
//dis为当前车走过的总距离，start_time_lap是本圈起始时的时间，now_seconds是当前时间
float get_timediff(float dis, int start_time_lap, int now_seconds)
{
	float now_time = get_diff_time(now_seconds, start_time_lap);//当前圈当前用时
	if (lap_count == 1)
	{
		printf("当前为第一圈");
		return 0;
	}
	for (int i = 0; i < 499; i++)
	{

		if (fastest_lap_dis[i] <= dis && fastest_lap_dis[i + 1] > dis)
		{
			//最快圈在这个距离时  时间的计算方式有多种。
			//在最快圈每两点中寻找点，当前点里程在两点之间，算出最快圈在那的时间
			//最快圈的时间可能不可以由i得出
			float acceleration = (fastest_lap_speed[i + 1] - fastest_lap_speed[i]) / 0.1;//加速度
			float fast_node_time = get_diff_time(fastest_lap_time[i], fastest_lap_time[0]);//最快圈当前节点时间，还要加上动力学系统插值时间
			float fast_time = 0;//当前里程真正时间
			float diff_dis = dis - fastest_lap_dis[i];
			if (acceleration != 0)
				fast_time = (sqrt(fastest_lap_speed[i] * fastest_lap_speed[i] + 2 * acceleration*diff_dis) - fastest_lap_speed[i]) / acceleration * 3600 + fast_node_time;//动力学模型 公式
			else
				fast_time = diff_dis / fastest_lap_speed[i] * 3600 + fast_node_time;
			float timediff = fast_time - now_time;
			printf("当前时间%d,当前圈当前时间：%.2f,最快圈当前时间：%.2f,领先时间：%.2f\n", now_seconds, now_time, fast_time, timediff);
			return timediff;//单位为秒
		}
	}
	printf("里程未找到 里程为%f 时间为%d\n", dis, now_seconds);
	return 0;
}

float get_timediff1(float lat, float lng, int start_time_lap, int now_seconds, int &new_index,float last)
{
	/*lap 1*/
	if (lap_count == 1)
	{
		printf("当前为第一圈");
		return 0;
	}
	

	int close_index       = 0;                                                                           //寻找最快圈节点时使用的下标，计算新的一圈时需置零 
	bool flag_close_edge  = false;                                                                       //最近点序号,flag为1代表是离最快圈旧点更近
	float *now_time		  = (float *)malloc(sizeof(float));		                             //当前圈当前用时
	float *close_dis      = (float *)malloc(sizeof(float));                                              //三角中最近点距离
	float *dis            = (float *)malloc(sizeof(float));                                              //三角中另一点距离
	float *across_dis     = (float *)malloc(sizeof(float));                                              //垂线时差值距离
	float *acceleration   = (float *)malloc(sizeof(float));                                              //加速度
	float *fast_node_time = (float *)malloc(sizeof(float));                                              //最快圈到此节点时所用时间
	float *dis0           = (float *)malloc(sizeof(float));                                              //离当前节点最近的两个最快圈节点之间的距离
	float *fast_time      = (float *)malloc(sizeof(float));                                              //最快圈在当前节点所在位置的估计时间
	float timediff        = 0;
	*now_time             =get_diff_time(now_seconds, start_time_lap);
	*close_dis            = enumber;
	*dis                  = enumber;
	*across_dis           = 0;
	*acceleration         = 0;
	*fast_node_time       = 0;
	*dis0                 = 0;
	*fast_time            = 0;
	/*找到一个下标close_index*/
	for (int i = new_index; i < 499; i++)
	{
		float temp_dis = distance(fastest_lap_lat[i], fastest_lap_lng[i], lat, lng);
		/*搜索最近的两个点*/
		if (temp_dis < *close_dis)
		{
			*close_dis = temp_dis;
		
			bool end = fastest_lap_lat[i + 1] == enumber;
			float dis2 = distance(fastest_lap_lat[i + 1], fastest_lap_lng[i + 1], lat, lng);//后一个点的距离
			float dis3 = distance(fastest_lap_lat[i - 1], fastest_lap_lng[i - 1], lat, lng);//前一个
			if (end || dis2 > dis3)                                                         //离旧点更近，或到终点
			{
				close_index = i - 1;
				*dis = dis3;
				flag_close_edge = true;
			}
			else
			{
				close_index = i;
				*dis = dis2;
			}
			
		}
		flag_close_edge = false; 
		new_index = i;
	}
	/*搜索结束时close_dis是最小距离，dis是第二小距离，二者必相邻，close_index是前一个点下标*/
	*dis0 = distance(fastest_lap_lat[close_index], fastest_lap_lng[close_index], fastest_lap_lat[close_index + 1], fastest_lap_lng[close_index + 1]);
	if (*dis0 == 0)
		return real_segtime[real_segtime_index - 1];
	if (!flag_close_edge)
	{
		*across_dis = (pow(*dis, 2) + pow(*dis0, 2) - pow(*close_dis, 2)) / 2 / *dis0;                    //余弦函数计算插值距离,close在下
		if (*across_dis < 0)
		{
			printf("it do happen:%f",*dis);
			*across_dis = -*across_dis + *dis0;
		}
	}
	else
	{
		*across_dis = (pow(*close_dis, 2) + pow(*dis0, 2) - pow(*dis, 2)) / 2 / *dis0;				     //余弦函数计算插值距离，close在上
	}
	*acceleration = (fastest_lap_speed[close_index + 1] - fastest_lap_speed[close_index]) / 0.1;//加速度
	*fast_node_time = get_diff_time(fastest_lap_time[close_index], fastest_lap_time[0]);
	if (*fast_node_time == 0)
	{
		printf("fast_node_time=0 %d  %d", close_index, fastest_lap_time[0]);
		//return last;
	}


	if (*acceleration != 0)
		*fast_time = (sqrt(fastest_lap_speed[close_index] * fastest_lap_speed[close_index] + 2 * (*acceleration)*(*across_dis)) - fastest_lap_speed[close_index]) / (*acceleration) * 3600 + (*fast_node_time);//动力学模型 公式
	else
		*fast_time = *across_dis / fastest_lap_speed[close_index] * 3600 + *fast_node_time;
	timediff = *fast_time - *now_time;
	real_segtime[real_segtime_index] = *fast_time - *now_time;
	if (fastest_lap_lat[close_index + 2] == enumber)
		printf("meet the end of fastest_lap");
	
	
	/*滤波*/
	if (abs(timediff - last) >= 0.03)
	{
		printf("被迫滤波%f", last );
		if (timediff > last)
			timediff = last+0.01 ;
		else
			timediff = last-0.01 ;
	}
	/*写入文件*/

	new_index = close_index;
	real_segtime_index++;
	printf("当前时间%d,当前圈当前时间：%.2f,最快圈当前时间：%.2f,插值时间：%f,插值距离%f,领先时间：%.2f\n ",
		now_seconds, *now_time, *fast_node_time, *fast_time - *fast_node_time, *dis0, timediff);
	if (lap_count == 3)
		write_lap(timediff);
	/*释放申请的空间*/
	free(now_time);
	free(close_dis);
	free(across_dis);
	free(acceleration);
	free(fast_node_time);
	free(dis0);
	free(fast_time);
	free(dis);
	return timediff;//单位为秒
}
/*测试区代码，使用时需重写*/
void load_data(float direction[5000], float lat[5000], float lng[5000], int time[5000], float speed[5000])
{
	read_dire2node_once("C:\\Users\\Administrator\\Desktop\\data\\dire_long.txt", direction);
	read_lat2node_once("C:\\Users\\Administrator\\Desktop\\data\\lat_long.txt", lat);
	read_lng2node_once("C:\\Users\\Administrator\\Desktop\\data\\lng_long.txt", lng);
	read_time2node_once("C:\\Users\\Administrator\\Desktop\\data\\time.txt", time);
	read_speed2node_once("C:\\Users\\Administrator\\Desktop\\data\\speed.txt", speed);
}





