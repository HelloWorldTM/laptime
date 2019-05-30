//??????????�������Ҳ���Է��⣿������
#pragma once
#include "pch.h"
#include <windows.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include "load_data2node.h"
#include "distance.h"
#define direction_change 2                          //������ֱ���ڵ�����ƫ�������ֵ��ζ�ſ�ʼת�䣬ƫ��ֱ��			
#define dis_limit 0.005								//�ڼ����Ƿ񵽴��յ�ʱ����������֮���������ҪС��5��
#define enumber 12345                               //�������ݣ���ʼ��ʱʹ��
#define time_find_start  500                        //���յ�500���ڵ�֮��ſ�ʼ������Ѱ��ֱ�������
float max_straight_length                       = enumber;
float start_point_lat                           = enumber;
float start_point_lng                           = enumber;
float start_point_direction                     = enumber;
int lap_count                                   = 0;
int time_compare_node_index                     = 0;//��¼��ǰ�ڵ��ڱ�Ȧ�е���ţ��ڼ���ʱ���ʱ����ָʾ��ǰ�����������Ȧ���ĸ��ڵ�
Node*fast_start                                 = NULL, *fast_end = NULL;
float fastest_lap_speed[500];                       //���Ȧ���ٶȼ���
float fastest_lap_lat[500];
float fastest_lap_lng[500];
float fastest_lap_dis[500];
int fastest_lap_time[500];
float real_segtime[500]                         = { 0 };
int real_segtime_index                          = 0;//����ÿ�������Ȧ���ʱ��ʵ��ʱ����ʾʱΪ�˲�ʱ��


/*������end*/
int main()
{
	float direction[5000];
	float lat[5000];
	float lng[5000];
	int	  time[5000];
	float speed[5000];
	int	index           = 0, fast_index = 0, start_time_lap = 0;   //�ڵ����������Ȧ����,��Ȧ��ʼʱ��
	float dis           = 0, next_dis = 0, prior_dis = 0, minlaptime = enumber;
	float mileage       = 0, seg_mileage = 0;                      //��ǰȦ��̺͵�ǰȦ��ǰ�����  
	float last_time_diff = 0;					                   //�ϴ�ʱ�������˲�
	Node*lap            = create_list(1);                          //�½��ڵ�Ϊ�����������
	Node*new_circle     = NULL;                                    //�����һȦ���
	Node*p              = NULL;                                    //����ʱ��ʱָ��ǰ�ڵ�
	Node*last_start     = NULL;                                    //ָ����һ�ε����

	                                                                                                  
	load_data(direction, lat, lng, time, speed);													  //����ģ������
	while (index < 4724)
	{
		                                                                                              //ÿ�ν������½��ڵ�
		Node*new_node = create_node();
		/*����С���ӿڣ����ڲ����*/
		fill_node_once(direction[index], lat[index], lng[index], time[index], speed[index], new_node);
		if (start_point_lat == enumber && index % 10 != 0)                                            //�ڵ�һȦ��ʼʱÿ��ֻһ���¼һ��ֵ
		{
			index++;
			insert_list(lap, new_node);
			continue;
		}
		insert_list(lap, new_node);
		/*��50��֮��ʼ�����
		if (len_list(lap) >= time_find_start && start_point_lat == enumber)
		{
			get_straight_dire(lap);                                                                   //�ҵ�ֱ������
			new_circle = get_start_point(lap);                                                        //�ҵ�����Ȧ�����
			set_start(new_circle);                                                                    //���������Ϣ����ǰȦ��
			start_time_lap = new_circle->seconds;                                                     //��ǰȦ��ʼʱ��
		}
		*/
		/*Ѱ��ÿȦ�ıջ������µ�;ɵĵ���бȽ�*/
		if (new_node != NULL && start_point_lat == enumber && len_list(lap)>200 )
		{
			Node* q = lap;
			Node* now_node = new_node->prior;
			Node* last_node2compare = jump_node_back(now_node,100);
			while (q != last_node2compare) 
			{
				if (abs(q->direction - now_node->direction) < 4 && distance(q->latitude, q->longitude, now_node->latitude, now_node->longitude) < 0.005)
				{
					new_circle = now_node;
					set_start(now_node);
					start_time_lap = now_node->seconds;
					printf("start_time:%d,%d",start_time_lap,q->seconds);
					break;
				}
					q = jump_node_forward(q,10);
			}

		}
		/*���ٶ�ֵ�����
		if (new_node->prior!=NULL && new_node->prior->speed > 90 && start_point_lat == enumber) 
		{
			new_circle = new_node->prior;
			set_start(new_circle);
			start_time_lap = new_circle->seconds;
		}
		*/
		if (new_circle)
		{
			/*�״γ�ʼ��,��ɺ���new_circle�͵�500���ڵ�֮����ͼѰ��һȦ�յ�*/
			if (!p)
			{
				p = new_circle->next;
				//��¼��һȦ�����ڵ㣬����������һȦ��ʱ��
				last_start = new_circle;
				/*��new_circle�͵�500���ڵ�֮����ͼѰ��һȦ�յ�*/
				while (p!=NULL && p->next != NULL)
				{
					//�϶ξ��룬��������϶ξ�����ԭ����Ϊ����p = new_node->prior֮������������㵱ǰ����
					update_mileage(seg_mileage, mileage, p->prior);
					//dis�ǵĸ���
					update_dis(prior_dis, dis, next_dis, p->next);
					//�����޶ȣ����޶�����Ϊ�����
					if (dis < dis_limit&&dis < next_dis&&dis < prior_dis)
					{
						printf("����Ϊ��%f  ʱ���ǣ�%d �ٶ��ǣ�%f\n", dis, p->seconds, p->speed);
						printf("��Ȧʱ��Ϊ��%.2f ��Ȧ���룺%.3f km\n", laptime(last_start, p), mileage);//�����ȦȦ��
						last_start = p;                                                      //��һ�����ĸ���
						start_time_lap = p->seconds;                                         //������ʼʱ��
					}
					p = p->next;
					fast_index++;
				}
				/*��ͼѰ�ҽ���*/
			}

			//����֮ǰ����һ��if����p==new_node,��Ҫ����
			p = new_node->prior;//pָ�����½ڵ��ǰһ������Ϊ��Ҫ���һ���ڵ��жϾ���assert p->next!=NULL��,һ��ʼp�ǵ�500��node
			//�½ڵ�������
			update_mileage(seg_mileage, mileage, p);
			//dis�ǵĸ���,Ѱ�����������ĵ�
			update_dis(prior_dis, dis, next_dis, new_node);
			//��ӡ��ǰ��������Ȧʱ����
			//get_timediff(mileage,start_time_lap,p->seconds);
			last_time_diff = get_timediff1(p->latitude, p->longitude, start_time_lap, p->seconds, time_compare_node_index, last_time_diff);

			if (dis < dis_limit&&dis < next_dis&&dis < prior_dis) //�����޶�
			{
				if (fast_end != NULL)
				{
					//compare_time(fast_start, fast_end, last_start, p);
				}
				float lap_time = laptime(last_start, p);

				printf("��������ʱ��%.2f\n", minlaptime - lap_time);
				/*�������Ȧ��Ϣ*/
				update_fast_lap(lap_time, minlaptime, last_start, p);

				printf("��Ȧʱ��Ϊ��%.2f\n", lap_time);//��ӡ��Ȧʱ��
				printf("��Ȧ���룺%.3f km  dis:%f  \n", mileage, distance(p->latitude, p->longitude, start_point_lat, start_point_lng));

				/*�µ�һȦ���㴦*/
				lap_count++;                //Ȧ����һ
				last_start = p;             //��һ�����ĸ���
				start_time_lap = p->seconds;//
				mileage = 0;                //���������
				time_compare_node_index = 0;
				                            //�ָ���¼��ʵʱ���
				for (int i = 0; i < 500; i++)
					real_segtime[i] = 0;
				real_segtime_index = 0;
				last_time_diff = 0;
			}
			p = p->next;
								            //��ʼ����ʵʱʱ���
		}
		index++;
	}
}
