#include <stdio.h>
#include <time.h>
//time_t��һ��������������long int������tm��ϵͳ�Զ����һ���ṹ��

/*struct tm�Ķ��� 
struct tm{
	      int tm_sec;        �� �C ȡֵ����Ϊ[0,59] 
          int tm_min;       �� - ȡֵ����Ϊ[0,59] 
          int tm_hour;      ʱ - ȡֵ����Ϊ[0,23] 
          int tm_mday;       һ�����е����� - ȡֵ����Ϊ[1,31] 
          int tm_mon;        �·ݣ���һ�¿�ʼ��0����һ�£�- ȡֵ����Ϊ[0,11] 
          int tm_year;       ��ݣ���ֵ����ʵ����ݼ�ȥ1900
          int tm_wday;       ���ڨC ȡֵ����Ϊ[0,6]������0���������죬1��������һ���Դ����� 
          int tm_yday;       ��ÿ���1��1�տ�ʼ������ �C ȡֵ����Ϊ[0,365]������0����1��1�գ�1����1��2�գ��Դ����� 
          int tm_isdst;      ����ʱ��ʶ����ʵ������ʱ��ʱ��tm_isdstΪ������ʵ������ʱ�Ľ���tm_isdstΪ0�����˽����ʱ��tm_isdst()Ϊ����
};                  */

//     time_t   mktime(const  tm*  timeptr);         ��tmʱ��飬ת��Ϊʱ���time_t,�õ�timeptr��ʾ��Э������ʱ��ʱ�����
//	   char*  ctime��const time_t *  timep��         ��time_tת��Ϊ�ַ���                                                         ע����Щ���������Լ������ڴ棬�����ٿ��ڴ� 
//     char * asctime(const tm*  timeptr)            ��tm�ṹ��ת��Ϊ�ַ���
//     tm* localtime(const  time_t*  timep)          ��time_tת��Ϊ�ṹ��ʱ�� 
//     clock_t clock(void)                           ��ȡϵͳʱ�䣬���س�����clock_t���͵ı���
//     time_t time(time_t *t)                        ���ر�׼ʱ�䵽���ڵ�ʱ��� 

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
