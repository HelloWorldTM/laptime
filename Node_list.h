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


//�ڵ�ṹ�壬ÿ���ڵ�ֱ𱣴���һ��ָ��ǰһ���ڵ��ָ���ָ���һ���ڵ��ָ�룬�Լ��������ݵ�ָ��

//����˫������Ľڵ� 
typedef struct Node
{
	struct Node *prior;
	struct Node *next;
	float longitude; //����
	float latitude;  //γ��
	float speed;     //�ٶ�
	uint32_t seconds;//unix ʱ���
	uint16_t millisecondes;//������
	float direction; //��λ�ǣ�����Ϊ0��
};

//��ʼ��һ������Ľڵ�
Node* create_node(void);

//��������N������˫������
Node* create_list(int n);


//����ĳ���
int len_list(Node * node);


//��λ�����������λ��
Node* pos_list(Node *head, int n);


//�������һ������
void out_front_list(Node *head);

//�������һ������
void out_reverse_list(Node *head);

//�������ͷ��������
Node* start_insert_list(Node *head);

//�����нڵ������������ĩβ
void insert_list(Node *head, Node *p);


//�������β��������
Node* end_insert_list(Node *head);


//���뵽����λ��֮ǰ
Node* insert_befor_list(Node *head, int a);

//���뵽����λ��֮�� 
Node* insert_after_list(Node *head, int a);

//ɾ��ͷ���
Node* delect_start_list(Node *head);


//ɾ��β���
Node* delect_end_list(Node *head);


//ɾ��ָ��λ�õĽڵ�
Node* delect_list(Node *head, int i);

//������ݵ��ڵ�
void fill_node_once(float dire, float lat, float lng, int time, float speed, Node * head);

//д���ݵ��ļ�
void write_lap(float timediff);

//�����ڵ�֮��ľ���
int dis_node(Node* start, Node* end);

//ת������ĵ�n���ڵ㣬������û��n���ڵ㣬�򷵻����һ���ڵ�
Node* jump_node_forward(Node* p, int n);

Node* jump_node_back(Node* p, int n);


/*����ʵ��*/ 
Node* create_node(void)
{
	Node *p;
	p = (Node*)malloc(sizeof(Node));
	if (p == NULL)
	{
		printf("��̬�ڴ����ʧ�ܣ�\n");
		exit(0);
	}
	p->prior = NULL;
	p->next = NULL;
	return (p);
}

//��������N������˫������
Node* create_list(int n)
{
	Node *p = NULL, *new1 = NULL, *head = NULL;
	int i;
	if (n >= 1)                    //���ĸ��� >= 1 ��ʱ�������ɵ�һ����� 
	{
		new1 = create_node();
		head = new1;
		p = new1;
	}
	for (i = 2; i <= n; i++)    //���ɵ�һ������Ժ�Ľ�㣬������˫������Ĺ�ϵ 
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

//����ĳ���
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

//��λ�����������λ��
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

//�������һ������
void out_front_list(Node *head)
{
	if (head == NULL)
	{
		printf("�����������Ϣ�����������ڣ�\n");
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

//�������һ������
void out_reverse_list(Node *head)
{
	if (head == NULL)
	{
		printf("�����������Ϣ�����������ڣ�\n");
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

//�������ͷ��������
Node* start_insert_list(Node *head)
{
	Node *p;
	p = create_node();
	p->next = head;
	head->prior = p;
	head = p;
	return (p);
}
//�����нڵ������������ĩβ
void insert_list(Node *head, Node *p)
{
	int n;
	n = len_list(head);
	head = pos_list(head, n);
	p->prior = head;
	head->next = p;
}

//�������β��������
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

//���뵽����λ��֮ǰ
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

//���뵽����λ��֮�� 
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
//ɾ��ͷ���
Node* delect_start_list(Node *head)
{
	Node *pos;
	pos = head;
	head = head->next;
	head->prior = NULL;
	free(pos);
	return(head);
}

//ɾ��β���
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

//ɾ��ָ��λ�õĽڵ�
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
//������ݵ��ڵ�
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
int dis_node(Node* start, Node* end)               //��ڵ�֮��ľ��� 
{
	if (start == NULL || end == NULL) 
	{
		printf("��ڵ�֮������ǲ���ΪNULL");
		return 0;
	}
	int dis = 0;
	while (start != end) 
	{
		dis++;
		start = start->next;
		if (dis > 1000000) 
		{
			printf("�ڵ�֮��������");
			return 1000000;
		}
		return dis;
	}
}
Node* jump_node_forward(Node* p, int n)                              //������n���ڵ�֮�� 
{
	for (int i = 0; i < n; i++)
	{
		if (p->next != NULL)
			p = p->next;
		else return p;
	}
	return p;
}
Node* jump_node_back(Node * p, int n)                               //������n���ڵ�֮ǰ 
{
	for (int i = 0; i < n; i++)
	{
		if (p->prior != NULL)
			p = p->prior;
		else return p;
	}
	return p;
}

/*��������*/
void get_straight_dire(Node* head)
{
	Node*p                     = head;
	Node*max_length_start_node = NULL;//�ֱ����ʼ�ڵ�
	Node*max_length_end_node   = NULL;//�ֱ��ĩβ�ڵ�
	int maxlength              = 0;   //�ֱ������
	while (p->next)
	{
		int temp_maxlength = 0;                 //�����ǲ���Ľڵ㳤��
		Node*q = p;
		float dire = p->direction;
		float a = q->next->direction;
		while (abs(dire - a) < direction_change)//�����û��
		{
			q = q->next;
			if (q->next != NULL)
			{
				temp_maxlength++;
				a = q->next->direction;
			}
			else break;
		}
		if (temp_maxlength > maxlength)         //��ǰΪ��󳤶�
		{
			maxlength = temp_maxlength;
			max_length_start_node = p;
			max_length_end_node = q;
			start_point_direction = dire;
		}
		p = p->next;
	}
	//�����ֱ���˵����ֱ������,��㾭γ�ȣ������
	max_straight_length = distance(max_length_start_node->latitude, max_length_start_node->longitude, max_length_end_node->latitude, max_length_end_node->longitude);
	start_point_lat = (max_length_start_node->latitude + max_length_end_node->latitude) / 2;
	start_point_lng = (max_length_start_node->longitude + max_length_end_node->longitude) / 2;
}

//�ҵ��ֱ����Ϣ���ô˺����ҳ������з��Ϸ���ǣ���γ��Ҫ������ڵ㣬��������Ҫ�ô˽ڵ��ʱ�����Ϣ
Node* get_start_point(Node *head)
{
	if (head == NULL)
	{
		printf("ERROR in get_start_point�������ڵ�Ϊ��");
		return NULL;
	}
	int num = 0;
	Node * p = NULL;
	while (head->next != NULL)
	{
		if (abs(head->direction - start_point_direction) < 2) //����ǲ��С��2
		{
			bool dec = head->latitude >= start_point_lat && head->next->latitude < start_point_lat;         //��ѡ���γ�Ⱥ�next��γ�Ȱ������γ��
			bool inc = head->latitude <= start_point_lat && head->next->latitude > start_point_lat;         //��ѡ��ľ��Ⱥ�next�ľ��Ȱ�����㾭�� 
			if (dec | inc)
			{
				num++;
				printf("��ѡ�㣺lat:%f��lng:%f,time:%d\n", head->latitude, head->longitude, head->seconds);
				p = head;
			}
		}
		head = head->next;
	}
	if (num == 1)
	{
		printf("��� lat:%f,lng:%f,dire:%f\n", p->latitude, p->longitude, p->direction);
		return p;
	}
	else if (num == 0)
	{
		printf("δ�ҵ���ʼ�ڵ�");
		return NULL;
	}
	else
	{
		printf("���ڶ����ѡ�ڵ㣡������ĺ�ѡ�ڵ�ѡ��ģʽ ��ѡ�ڵ�����%d", num);
		return NULL;
	}
}

/*�жϵ�ǰ����Ƿ�Խ�����������*/
bool iscrossed(Node *p)                               //keneng 
{
	if (p == NULL)
	{
		printf("ERROR in iscrossed�������ڵ�Ϊ��");
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
/*����Ȧʱ,��ʽΪ��t2-delta_t2��-(t1-delata_t1),t1Ϊ��Ȧʱ�䣬delta_t1Ϊ��һȦ��ֵ*/
float laptime(Node *last_start, Node* this_start) //
{
	if (last_start == NULL || this_start == NULL)
	{
		printf("ERROR in laptime�������ڵ�Ϊ��");
		return 0;
	}
	float delta_t1 = 0, delta_t2 = 0, t1 = 0, t2 = 0;
	delta_t1 = 1000 * distance(last_start->latitude, last_start->longitude, start_point_lat, start_point_lng) / last_start->speed;
	delta_t2 = 1000 * distance(this_start->latitude, this_start->longitude, start_point_lat, start_point_lng) / this_start->speed;
	if (!iscrossed(last_start)) //��һ���ڵ���ûԽ����
	{
		delta_t1 = -delta_t1;
	}
	if (!iscrossed(this_start)) //���νڵ�δԽ�����
	{
		delta_t2 = -delta_t2;
	}
	printf("��ֵʱ��%f(-)", delta_t2 - delta_t1);
	return get_diff_time(this_start->seconds, last_start->seconds) - delta_t2 + delta_t1;
}
/*�жϵ�ǰ�ڵ��ǲ�������������̵�*/
void set_start(Node*new_circle)
{
	start_point_lat = new_circle->latitude;//�ҵ���������λ�����ݣ��������ƽ��ֵ��û��׼ȷʱ�䣩
	start_point_lng = new_circle->longitude;
	lap_count = 1;//��ǰΪ��һȦ
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
		printf("ERROR in sun_dis:����Ϊ��");
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
	//�����
	mileage += seg_mileage;
}
/*�������Ȧ���ݣ������������ݣ����룬ʱ�䣬�Ѿ��������*/
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
	/*����������������Ϊ���һ���ٶȣ�����֮��ʵʱ����ʱ��*/
	int last_index = i - 1;
	for (i; i < 500; i++)
	{
		fast[i] = fast[last_index];
		lat[i] = enumber;
		lng[i] = enumber;
	}
	return fast;
}

/*���Ȧʱ����ÿ�����ڵ�֮��ľ��룬��������Ż����㸺�ؿ����ڴ˺����ڲ���distance����
  ��Ϊ�ڼ�������̵�ʱ����¹�,����Ҫ����Ŀռ�������dis�������Կռ任ʱ��*/
float* load_fast_dis(Node*start, Node*last, float fast[500])
{
	int i = 1;
	fast[0] = 0;//���Ż����������Ƿ�Խ����ʼ��;�����ʼ��������Ľ�
	float temp_dis;
	while (start->prior != last)
	{
		temp_dis = distance(start->latitude, start->longitude, start->next->latitude, start->next->longitude);
		fast[i] = temp_dis + fast[i - 1];
		//printf("Ŀǰ����Ϊ��%f\n", fast[i]);
		i++;
		start = start->next;
	}
	//����������������Ϊ���һ���ٶȣ�����֮��ʵʱ����ʱ��
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
	//����������������Ϊenumber
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
		load_fast_speed(last_start, p, fastest_lap_speed, fastest_lap_lat, fastest_lap_lng);//�������Ȧ�ٶ�,��γ��
		load_fast_dis(last_start, p, fastest_lap_dis);//�������Ȧÿ�ξ���
		load_fast_time(last_start, p, fastest_lap_time);//�������Ȧÿ��ʱ���
		fast_start = last_start;
		fast_end = p;
	}
}
//disΪ��ǰ���߹����ܾ��룬start_time_lap�Ǳ�Ȧ��ʼʱ��ʱ�䣬now_seconds�ǵ�ǰʱ��
float get_timediff(float dis, int start_time_lap, int now_seconds)
{
	float now_time = get_diff_time(now_seconds, start_time_lap);//��ǰȦ��ǰ��ʱ
	if (lap_count == 1)
	{
		printf("��ǰΪ��һȦ");
		return 0;
	}
	for (int i = 0; i < 499; i++)
	{

		if (fastest_lap_dis[i] <= dis && fastest_lap_dis[i + 1] > dis)
		{
			//���Ȧ���������ʱ  ʱ��ļ��㷽ʽ�ж��֡�
			//�����Ȧÿ������Ѱ�ҵ㣬��ǰ�����������֮�䣬������Ȧ���ǵ�ʱ��
			//���Ȧ��ʱ����ܲ�������i�ó�
			float acceleration = (fastest_lap_speed[i + 1] - fastest_lap_speed[i]) / 0.1;//���ٶ�
			float fast_node_time = get_diff_time(fastest_lap_time[i], fastest_lap_time[0]);//���Ȧ��ǰ�ڵ�ʱ�䣬��Ҫ���϶���ѧϵͳ��ֵʱ��
			float fast_time = 0;//��ǰ�������ʱ��
			float diff_dis = dis - fastest_lap_dis[i];
			if (acceleration != 0)
				fast_time = (sqrt(fastest_lap_speed[i] * fastest_lap_speed[i] + 2 * acceleration*diff_dis) - fastest_lap_speed[i]) / acceleration * 3600 + fast_node_time;//����ѧģ�� ��ʽ
			else
				fast_time = diff_dis / fastest_lap_speed[i] * 3600 + fast_node_time;
			float timediff = fast_time - now_time;
			printf("��ǰʱ��%d,��ǰȦ��ǰʱ�䣺%.2f,���Ȧ��ǰʱ�䣺%.2f,����ʱ�䣺%.2f\n", now_seconds, now_time, fast_time, timediff);
			return timediff;//��λΪ��
		}
	}
	printf("���δ�ҵ� ���Ϊ%f ʱ��Ϊ%d\n", dis, now_seconds);
	return 0;
}

float get_timediff1(float lat, float lng, int start_time_lap, int now_seconds, int &new_index,float last)
{
	/*lap 1*/
	if (lap_count == 1)
	{
		printf("��ǰΪ��һȦ");
		return 0;
	}
	

	int close_index       = 0;                                                                           //Ѱ�����Ȧ�ڵ�ʱʹ�õ��±꣬�����µ�һȦʱ������ 
	bool flag_close_edge  = false;                                                                       //��������,flagΪ1�����������Ȧ�ɵ����
	float *now_time		  = (float *)malloc(sizeof(float));		                             //��ǰȦ��ǰ��ʱ
	float *close_dis      = (float *)malloc(sizeof(float));                                              //��������������
	float *dis            = (float *)malloc(sizeof(float));                                              //��������һ�����
	float *across_dis     = (float *)malloc(sizeof(float));                                              //����ʱ��ֵ����
	float *acceleration   = (float *)malloc(sizeof(float));                                              //���ٶ�
	float *fast_node_time = (float *)malloc(sizeof(float));                                              //���Ȧ���˽ڵ�ʱ����ʱ��
	float *dis0           = (float *)malloc(sizeof(float));                                              //�뵱ǰ�ڵ�������������Ȧ�ڵ�֮��ľ���
	float *fast_time      = (float *)malloc(sizeof(float));                                              //���Ȧ�ڵ�ǰ�ڵ�����λ�õĹ���ʱ��
	float timediff        = 0;
	*now_time             =get_diff_time(now_seconds, start_time_lap);
	*close_dis            = enumber;
	*dis                  = enumber;
	*across_dis           = 0;
	*acceleration         = 0;
	*fast_node_time       = 0;
	*dis0                 = 0;
	*fast_time            = 0;
	/*�ҵ�һ���±�close_index*/
	for (int i = new_index; i < 499; i++)
	{
		float temp_dis = distance(fastest_lap_lat[i], fastest_lap_lng[i], lat, lng);
		/*���������������*/
		if (temp_dis < *close_dis)
		{
			*close_dis = temp_dis;
		
			bool end = fastest_lap_lat[i + 1] == enumber;
			float dis2 = distance(fastest_lap_lat[i + 1], fastest_lap_lng[i + 1], lat, lng);//��һ����ľ���
			float dis3 = distance(fastest_lap_lat[i - 1], fastest_lap_lng[i - 1], lat, lng);//ǰһ��
			if (end || dis2 > dis3)                                                         //��ɵ���������յ�
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
	/*��������ʱclose_dis����С���룬dis�ǵڶ�С���룬���߱����ڣ�close_index��ǰһ�����±�*/
	*dis0 = distance(fastest_lap_lat[close_index], fastest_lap_lng[close_index], fastest_lap_lat[close_index + 1], fastest_lap_lng[close_index + 1]);
	if (*dis0 == 0)
		return real_segtime[real_segtime_index - 1];
	if (!flag_close_edge)
	{
		*across_dis = (pow(*dis, 2) + pow(*dis0, 2) - pow(*close_dis, 2)) / 2 / *dis0;                    //���Һ��������ֵ����,close����
		if (*across_dis < 0)
		{
			printf("it do happen:%f",*dis);
			*across_dis = -*across_dis + *dis0;
		}
	}
	else
	{
		*across_dis = (pow(*close_dis, 2) + pow(*dis0, 2) - pow(*dis, 2)) / 2 / *dis0;				     //���Һ��������ֵ���룬close����
	}
	*acceleration = (fastest_lap_speed[close_index + 1] - fastest_lap_speed[close_index]) / 0.1;//���ٶ�
	*fast_node_time = get_diff_time(fastest_lap_time[close_index], fastest_lap_time[0]);
	if (*fast_node_time == 0)
	{
		printf("fast_node_time=0 %d  %d", close_index, fastest_lap_time[0]);
		//return last;
	}


	if (*acceleration != 0)
		*fast_time = (sqrt(fastest_lap_speed[close_index] * fastest_lap_speed[close_index] + 2 * (*acceleration)*(*across_dis)) - fastest_lap_speed[close_index]) / (*acceleration) * 3600 + (*fast_node_time);//����ѧģ�� ��ʽ
	else
		*fast_time = *across_dis / fastest_lap_speed[close_index] * 3600 + *fast_node_time;
	timediff = *fast_time - *now_time;
	real_segtime[real_segtime_index] = *fast_time - *now_time;
	if (fastest_lap_lat[close_index + 2] == enumber)
		printf("meet the end of fastest_lap");
	
	
	/*�˲�*/
	if (abs(timediff - last) >= 0.03)
	{
		printf("�����˲�%f", last );
		if (timediff > last)
			timediff = last+0.01 ;
		else
			timediff = last-0.01 ;
	}
	/*д���ļ�*/

	new_index = close_index;
	real_segtime_index++;
	printf("��ǰʱ��%d,��ǰȦ��ǰʱ�䣺%.2f,���Ȧ��ǰʱ�䣺%.2f,��ֵʱ�䣺%f,��ֵ����%f,����ʱ�䣺%.2f\n ",
		now_seconds, *now_time, *fast_node_time, *fast_time - *fast_node_time, *dis0, timediff);
	if (lap_count == 3)
		write_lap(timediff);
	/*�ͷ�����Ŀռ�*/
	free(now_time);
	free(close_dis);
	free(across_dis);
	free(acceleration);
	free(fast_node_time);
	free(dis0);
	free(fast_time);
	free(dis);
	return timediff;//��λΪ��
}
/*���������룬ʹ��ʱ����д*/
void load_data(float direction[5000], float lat[5000], float lng[5000], int time[5000], float speed[5000])
{
	read_dire2node_once("C:\\Users\\Administrator\\Desktop\\data\\dire_long.txt", direction);
	read_lat2node_once("C:\\Users\\Administrator\\Desktop\\data\\lat_long.txt", lat);
	read_lng2node_once("C:\\Users\\Administrator\\Desktop\\data\\lng_long.txt", lng);
	read_time2node_once("C:\\Users\\Administrator\\Desktop\\data\\time.txt", time);
	read_speed2node_once("C:\\Users\\Administrator\\Desktop\\data\\speed.txt", speed);
}





