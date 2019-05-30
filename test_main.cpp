//??????????（这表情也可以放这？？？）
#pragma once
#include "pch.h"
#include <windows.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include "load_data2node.h"
#include "distance.h"
#define direction_change 2                          //定义在直道内的允许偏差，超过此值意味着开始转弯，偏离直道			
#define dis_limit 0.005								//在计算是否到达终点时，首先两点之间距离至少要小于5米
#define enumber 12345                               //错误数据，初始化时使用
#define time_find_start  500                        //在收到500个节点之后才开始在其中寻找直道和起点
float max_straight_length                       = enumber;
float start_point_lat                           = enumber;
float start_point_lng                           = enumber;
float start_point_direction                     = enumber;
int lap_count                                   = 0;
int time_compare_node_index                     = 0;//记录当前节点在本圈中的序号，在计算时间差时用来指示当前搜索到了最快圈的哪个节点
Node*fast_start                                 = NULL, *fast_end = NULL;
float fastest_lap_speed[500];                       //最快圈的速度集合
float fastest_lap_lat[500];
float fastest_lap_lng[500];
float fastest_lap_dis[500];
int fastest_lap_time[500];
float real_segtime[500]                         = { 0 };
int real_segtime_index                          = 0;//计算每次与最快圈差距时的实际时间差，显示时为滤波时间


/*测试区end*/
int main()
{
	float direction[5000];
	float lat[5000];
	float lng[5000];
	int	  time[5000];
	float speed[5000];
	int	index           = 0, fast_index = 0, start_time_lap = 0;   //节点索引，最快圈索引,本圈起始时间
	float dis           = 0, next_dis = 0, prior_dis = 0, minlaptime = enumber;
	float mileage       = 0, seg_mileage = 0;                      //当前圈里程和当前圈当前段里程  
	float last_time_diff = 0;					                   //上次时间差，用来滤波
	Node*lap            = create_list(1);                          //新建节点为整个过程起点
	Node*new_circle     = NULL;                                    //保存第一圈起点
	Node*p              = NULL;                                    //计算时间时指向当前节点
	Node*last_start     = NULL;                                    //指向上一次的起点

	                                                                                                  
	load_data(direction, lat, lng, time, speed);													  //加载模拟数据
	while (index < 4724)
	{
		                                                                                              //每次进入先新建节点
		Node*new_node = create_node();
		/*调用小尘接口（放在参数里）*/
		fill_node_once(direction[index], lat[index], lng[index], time[index], speed[index], new_node);
		if (start_point_lat == enumber && index % 10 != 0)                                            //在第一圈开始时每次只一秒记录一个值
		{
			index++;
			insert_list(lap, new_node);
			continue;
		}
		insert_list(lap, new_node);
		/*当50秒之后开始找起点
		if (len_list(lap) >= time_find_start && start_point_lat == enumber)
		{
			get_straight_dire(lap);                                                                   //找到直道数据
			new_circle = get_start_point(lap);                                                        //找到后面圈的起点
			set_start(new_circle);                                                                    //设置起点信息，当前圈数
			start_time_lap = new_circle->seconds;                                                     //当前圈起始时间
		}
		*/
		/*寻找每圈的闭环，用新点和旧的点进行比较*/
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
		/*以速度值找起点
		if (new_node->prior!=NULL && new_node->prior->speed > 90 && start_point_lat == enumber) 
		{
			new_circle = new_node->prior;
			set_start(new_circle);
			start_time_lap = new_circle->seconds;
		}
		*/
		if (new_circle)
		{
			/*首次初始化,完成后在new_circle和第500个节点之间试图寻找一圈终点*/
			if (!p)
			{
				p = new_circle->next;
				//记录上一圈的起点节点，用来计算下一圈的时间
				last_start = new_circle;
				/*在new_circle和第500个节点之间试图寻找一圈终点*/
				while (p!=NULL && p->next != NULL)
				{
					//上段距离，这里计算上段距离有原因，因为下面p = new_node->prior之后调整过来计算当前段了
					update_mileage(seg_mileage, mileage, p->prior);
					//dis们的更新
					update_dis(prior_dis, dis, next_dis, p->next);
					//距离限度，在限度内认为是起点
					if (dis < dis_limit&&dis < next_dis&&dis < prior_dis)
					{
						printf("距离为：%f  时间是：%d 速度是：%f\n", dis, p->seconds, p->speed);
						printf("本圈时间为：%.2f 本圈距离：%.3f km\n", laptime(last_start, p), mileage);//计算此圈圈速
						last_start = p;                                                      //上一个起点的更新
						start_time_lap = p->seconds;                                         //更新起始时间
					}
					p = p->next;
					fast_index++;
				}
				/*试图寻找结束*/
			}

			//在这之前从上一个if出来p==new_node,需要调整
			p = new_node->prior;//p指向最新节点的前一个，因为需要与后一个节点判断距离差（assert p->next!=NULL）,一开始p是第500个node
			//新节点更新里程
			update_mileage(seg_mileage, mileage, p);
			//dis们的更新,寻找离起点最近的点
			update_dis(prior_dis, dis, next_dis, new_node);
			//打印当前点相对最快圈时间差距
			//get_timediff(mileage,start_time_lap,p->seconds);
			last_time_diff = get_timediff1(p->latitude, p->longitude, start_time_lap, p->seconds, time_compare_node_index, last_time_diff);

			if (dis < dis_limit&&dis < next_dis&&dis < prior_dis) //距离限度
			{
				if (fast_end != NULL)
				{
					//compare_time(fast_start, fast_end, last_start, p);
				}
				float lap_time = laptime(last_start, p);

				printf("最终领先时间%.2f\n", minlaptime - lap_time);
				/*更新最快圈信息*/
				update_fast_lap(lap_time, minlaptime, last_start, p);

				printf("本圈时间为：%.2f\n", lap_time);//打印此圈时间
				printf("本圈距离：%.3f km  dis:%f  \n", mileage, distance(p->latitude, p->longitude, start_point_lat, start_point_lng));

				/*新的一圈清零处*/
				lap_count++;                //圈数加一
				last_start = p;             //上一个起点的更新
				start_time_lap = p->seconds;//
				mileage = 0;                //总里程清零
				time_compare_node_index = 0;
				                            //恢复记录真实时间差
				for (int i = 0; i < 500; i++)
					real_segtime[i] = 0;
				real_segtime_index = 0;
				last_time_diff = 0;
			}
			p = p->next;
								            //开始计算实时时间差
		}
		index++;
	}
}
