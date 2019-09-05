#include<stdio.h>
#include<stdlib.h>  //为rand()和srand()函数提供原型
#include<time.h>    //为time()函数提供原型
#include "queue/queue.h"    //改变Item的typedef
#define MIN_PER_HR 60.0

bool newcustomer(double x);     
Item customertime(long when);   //设置顾客参量

int main()
{
    Queue line;
    Item temp;      //关于新顾客的数据
    int hours;      //模拟的小时数
    int perhour;    //每小时顾客平均数
    long cycle,cyclelimit;  //循环计数器，计数器的上界
    long turnaways = 0;     //因队列已满而被拒绝的顾客数
    long customers = 0;     //被加入队列的顾客数
    long served = 0;        //在模拟期间得到服务的顾客数
    long sum_line = 0;      //累计的队列长度
    int wait_time = 0;      //从当前到Sigmund空闲所需的时间
    double min_per_cust;    //顾客到来的平均间隔时间
    long line_wait = 0;     //队列累计等待时间 

    InitializeQueue(&line);
    srand(time(0));         //随机初始化rand()函数
    puts("学习例子：Sigmund Lander's在摊位上给人提供建议");
    puts("请输入模拟小时数: ");
    scanf("%d",&hours);
    cyclelimit = MIN_PER_HR * hours;
    puts("请输入平均每小时顾客到来的数量: ");
    scanf("%d",&perhour);
    min_per_cust = MIN_PER_HR / perhour;

    //让时间以一分钟为单位递增
    for(cycle = 0; cycle < cyclelimit; cycle++)
    {
        //在每分钟里检查是否有一个新的顾客到来
        if(newcustomer(min_per_cust))
        {
            //队列已满，拒绝该客户加入队列中并做记录处理
            if(QueueIsFull(&line))
                turnaways++;
            else   //如果有顾客到来，将此顾客添加到队列
            {
                customers++;
                //将此顾客的到达时间和咨询时间记录到一个
                //Item结构中，再将此项目入列
                temp = customertime(cycle);
                EnQueue(temp,&line);
            }
        }
        //如果Sugmund有空，并且有顾客在等待
        if(wait_time <= 0 && !QueueIsEmpty(&line))
        {
            //此时为顾客提供服务，项目出队列
            DeQueue(&temp,&line);
            //正在提供服务的顾客所需要的咨询时间
            wait_time = temp.processtime;
            //队列累计等待的时间为：每一位顾客等待的时间
            //每一位顾客等待的时间=该顾客开始接受服务的时间点
            // 减去 该顾客加入队列的时间点
            line_wait += cycle - temp.arrive;
            served ++;  //接受服务器的顾客数量加一
        }
        //每经过一分钟时间，正在咨询的顾客被服务的时间也随之减少一分钟
        if(wait_time > 0)
            wait_time --;
        sum_line = sum_line + QueueItemCount(&line);
    }

    if(customers > 0)
    {
        printf("接受客户数为：%ld\n",customers);
        printf("服务的客户数为：%ld\n",served);
        printf("被拒绝服务（没有在队列里面）的顾客数量 %ld\n",turnaways);
        printf("队列的平均大小为：%.2f\n",(double)sum_line/cyclelimit);
        printf("平均等待的时间： %.2f minutes\n",(double)line_wait / served);
    }
    else 
    {
        puts("没有顾客到来!\n");
    }
    EmptyTheQueue(&line);
    puts("程序运行结束，再见！\n");
    
    return 0;
}

//确定在这一分钟内是否有顾客到来
//x是顾客到来的平均间隔时间（以秒计）
//如果这1分钟内有顾客到来，则返回true
//备注说明：rand()函数将产生一个在0~RAND_MAX之间的随机数。
//假设平均每20分钟来一位顾客，那么rand()*20/RAND_MAX的取值
//范围为（0,20）,if语句里面的<表示，上面的值在（0,1）的范围内
bool newcustomer(double x)
{
    if(rand() * x / RAND_MAX < 1)
        return true;
    else
        return false;
}

//when是顾客到来的时间
//函数返回一个Item结构，该结构的顾客到来时间设置为when
//需要的咨询时间设置为一个范围在1到3之间的随机值
Item customertime(long when)
{
    Item cust;
    cust.processtime = rand()%3 + 1;
    cust.arrive = when;
    return cust;
}