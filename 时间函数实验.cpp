#include <stdio.h>
#include <time.h>
//time_t是一个长整型整数（long int），而tm是系统自定义的一个结构体

/*struct tm的定义 
struct tm{
	      int tm_sec;        秒 – 取值区间为[0,59] 
          int tm_min;       分 - 取值区间为[0,59] 
          int tm_hour;      时 - 取值区间为[0,23] 
          int tm_mday;       一个月中的日期 - 取值区间为[1,31] 
          int tm_mon;        月份（从一月开始，0代表一月）- 取值区间为[0,11] 
          int tm_year;       年份，其值等于实际年份减去1900
          int tm_wday;       星期– 取值区间为[0,6]，其中0代表星期天，1代表星期一，以此类推 
          int tm_yday;       从每年的1月1日开始的天数 – 取值区间为[0,365]，其中0代表1月1日，1代表1月2日，以此类推 
          int tm_isdst;      夏令时标识符，实行夏令时的时候，tm_isdst为正。不实行夏令时的进候，tm_isdst为0；不了解情况时，tm_isdst()为负。
};                  */

//     time_t   mktime(const  tm*  timeptr);         将tm时间块，转换为时间戳time_t,得到timeptr表示的协调世界时的时间戳。
//	   char*  ctime（const time_t *  timep）         将time_t转换为字符串                                                         注意这些函数都会自己开辟内存，不用再开内存 
//     char * asctime(const tm*  timeptr)            将tm结构体转换为字符串
//     tm* localtime(const  time_t*  timep)          将time_t转换为结构体时间 
//     clock_t clock(void)                           获取系统时间，返回长整型clock_t类型的变量
//     time_t time(time_t *t)                        返回标准时间到现在的时间差 

main(){
	time_t t1,t2,t3;
	tm ts1,ts2,ts3;
	clock_t c1,c2,c3;
	tm *pts;
	char *p;
	p=ctime(&t1);
	printf("%s",p);
	time(&t1);
	c1=clock();
	printf("%ld--%ld\n",t1,c1);
	pts=localtime(&t1);
	printf("%d--%d--%d--%d--%d--%d--%d--%d--%d\n",pts->tm_hour,pts->tm_isdst,pts->tm_mday,pts->tm_min,pts->tm_mon,pts->tm_sec,pts->tm_wday,pts->tm_yday,pts->tm_year);
}
