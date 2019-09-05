/*
 * @作者: www.gzhuflyer.top 
 * @日期: 2019-08-31 20:29:59  
 */

/*queue.h -- 队列接口 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include<stdbool.h>

// #define MAIN    1
#define MALL    1


#ifdef MAIN
typedef int Item;   //对Item的数据类型进行定义
#elif MALL
typedef struct item
{
    long arrive;    //一位顾客加入队列的时间
    int processtime;    //该顾客需要咨询的时间
}Item;
#endif

#define MAXQUEUE 10     //设置队列里面最大的节点数

//定义一个数据节点类型的结构，结构体里面包含
//数据项目和指向结构体数据类型的指针
typedef struct node
{
    Item item;
    struct node * next;
}Node;

typedef struct queue
{
    Node * front;   //指向该队列第一个节点的结构体指针
    Node * rear;    //指向该队列最后一个节点的结构体指针
    int items;      //用于记录队列中项目的个数
}Queue;

//操作：初始化队列
//操作前：pq指向一个队列(p：pointer单词指针的头一个字母，q：单词queue的头一个字母)
//操作后：该队列被初始化为空队列
void InitializeQueue(Queue * pq);

//操作：检查队列是否已满
//操作前：pq指向一个先前已初始化过的队列
//操作后：如果该队列已满，则返回True;否则返回False
bool QueueIsFull(const Queue * pq);

//操作：检查队列是否为空
//操作前：pq指向一个先前已初始化过的队列
//操作后：如果该队列为空，则返回True；否则返回False
bool QueueIsEmpty(const Queue * pq);

//操作：确定队列中项目的个数
//操作前：pq指向一个先前已初始化过的队列
//操作后：返回队列中项目的个数
int QueueItemCount(const Queue * pq);

//操作：向队列尾端添加项目
//操作前：pq指向一个先前已初始化过的队列, item 是要添加到队列尾端的项目
//操作后：如果队列未满，item被添加到队列尾部，函数返回true;否则，不改变
//       不改变队列，函数返回False
bool EnQueue(Item item, Queue * pq);

//从队列首端删除项目
//操作前：pq指向一个先前已初始化过的队列
//操作后：如果队列为非空，队列首端的项目被复制到*pitem,并被从队列中删除，
//       函数返回True；如果这个操作是队列为空，把队列重置为空队列，如果
//       队列开始时为空，不改变队列，函数返回False
bool DeQueue(Item * pitem, Queue * pq);

//操作：清空队列
//操作前：pq指向一个先前已初始化过的队列
//操作后：队列被清空
void EmptyTheQueue(Queue * pq);


//从队列尾端删除项目
//操作前：pq指向一个先前已初始化过的队列
//操作后：如果队列为非空，队列尾端的项目被复制到*pitem,并被从队列中删除，
//       函数返回True；如果这个操作是队列为空，把队列重置为空队列，如果
//       队列开始时为空，不改变队列，函数返回False
bool delete_from_rear(Item * pitem, Queue * pq);

#endif