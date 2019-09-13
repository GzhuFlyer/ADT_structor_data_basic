#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

//使用static关键字进行申明，局部函数，仅本文件可以使用该函数
static void CopyToNode(Item item, Node * pn);
static void CopyToItem(Node * pn, Item * pi);

void InitializeQueue(Queue * pq)
{
    pq->front = pq->rear = NULL;
    pq->items = 0;
}

//注意这里使用了关键字const,防止无意间对pq进行修改
bool QueueIsFull(const Queue * pq)
{
    //判断items的数目是否是最大的，如果是的话返回True
    return pq->items == MAXQUEUE;
}

bool QueueIsEmpty(const Queue * pq)
{
    return pq->items == 0;
}

int QueueItemCount(const Queue * pq)
{
    return pq->items;
}

bool EnQueue(Item item, Queue * pq)
{
    Node * pnew;

    if (QueueIsFull(pq))    
    {
        return false;
    }
    pnew = (Node *) malloc (sizeof(Node));
    if(pnew == NULL)
    {
        fprintf(stderr,"申请内存失败!\n");
        exit(1);
    }
    CopyToNode(item,pnew);
    pnew->next = NULL;
    if(QueueIsEmpty(pq))
    {
        pq->front = pnew;
    }else
    {
        pq->rear->next = pnew;
    }
    pq->rear = pnew;
    pq->items++;
    return true;   
}

bool DeQueue(Item * pitem, Queue * pq)
{
    Node * pt;
    if(QueueIsEmpty(pq))
        return false;
    CopyToItem(pq->front,pitem);
    pt = pq->front;     //让pq->front和pt指向同一个内存区域
    pq->front = pq->front->next;    //pq->front和指向pq->front->next指向的内存
    free(pt);           //释放掉pq->front指向的内存区域，也就是删除掉一个节点。
    pq->items --;
    if(pq->items == 0)
    {
        pq->rear = NULL;    //当items为0时，之前rear指向的内存已经被删除了，需要赋值为NULL
    }
    return true;
}


/*
 *备注：该调用函数从队尾对函数进行相关删除操作
 	按照队列的定义（先进先出规则)，队列里面
	是没有这个操作函数的，此处仅做编程练习
	使用。
 * */
bool delete_from_rear(Item * pitem, Queue * pq)
{
    //定义两个节点，作为中间指针；
    Node * pt1_temp;
    if(QueueIsEmpty(pq))
        return false;
    CopyToItem(pq->rear,pitem);
    pt1_temp = pq->front;    
    if(pq->items > 2)   //当队列里面的节点数量大于2的时候
        for(int i=1;i<pq->items-1;i++)  //通过下面循环，将原先队列中倒数第二个节点赋值给pt1_temp
            pt1_temp = pt1_temp->next;
    free(pt1_temp->next);   //释放掉最后一个节点所占用的内存
    pt1_temp->next = NULL;
    pq->rear = pt1_temp;    //将尾节点赋值给队列里面的rear指针。
    pq->items --;
    if(pq->items == 0)
    {
        pq->rear = NULL;    //当items为0时，之前rear指向的内存已经被删除了，需要赋值为NULL
    }    
    return true;
}

//清空队列
void EmptyTheQueue(Queue * pq)
{
    Item dummy;
    while(!QueueIsEmpty(pq))
        DeQueue(&dummy,pq);
}

static void CopyToNode(Item item, Node * pn)
{
    pn->item = item;
}

static void CopyToItem(Node * pn, Item * pi)
{
    *pi = pn->item;
}
