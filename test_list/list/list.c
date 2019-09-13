#include<stdio.h>
#include<stdlib.h>
#include "list.h"

//局部函数原型
static void CopyToNode(Item item, Node * pnode);

//接口函数
//把列表设置为空列表
void InitializeList(List * plist)
{
    *plist = NULL;
}

//如果列表为空则返回真
bool ListIsEmpty(const List * plist)
{
    if(*plist == NULL)
        return true;
    else
        return false;    
}

bool ListIsFull(const List * plist)
{
    Node * pt;
    bool full;

    pt = (Node *) malloc (sizeof(Node));
    if(pt == NULL )
        full = true;
    else
    {
        full = false;
    }
    free(pt);
    return full;
}

//返回节点数
unsigned int ListItemCount(const List * plist)
{
    unsigned int count = 0;
    Node * pnode = *plist;      //设置到列表的开始处
    while (pnode != NULL)
    {
        ++count;
        pnode = pnode->next;
    }
    return count;
}

//创建存放项目的节点，并把他添加到有plist指向的
//列表（较慢的实现方法）尾部
bool AddItem(Item item, List * plist)
{
    Node * pnew;
    Node * scan = *plist;

    pnew = (Node*)malloc(sizeof(Node));
    if(pnew == NULL)
        return false;       //申请内存失败时退出函数
    CopyToNode (item,pnew);
    pnew->next = NULL;
    if(scan  == NULL)
        *plist = pnew;
    else	//从队尾插入项目，时间复杂度为O(n)
    {
        while(scan->next != NULL)
            scan = scan->next;
        scan->next = pnew;
    }
    return true;
}

//访问每个节点并对他们分别执行有pfun指向的函数。
void Traverse(const List * plist, void (*pfun)(Item item))
{
    Node * pnode = *plist;  //设置到列表的开始处
    while(pnode != NULL)
    {
         (*pfun)(pnode->item);  //把函数作用于列表中的项目
         pnode = pnode->next;   //前进到列表的下一项
    }
}

//释放由malloc()分配的内存
//把列表指针设置为NULL
void EmptyTheList(List * plist)
{
    Node * psave;
    while(*plist != NULL)
    {
        psave = (*plist)->next;     //保存下一个节点的地址
        free(*plist);               //释放当前节点
        *plist = psave;             //前进到下一个节点
    }
}

//把一个项目复制到一个节点中。
static void CopyToNode(Item item,Node * pnode)
{
    pnode->item = item; 
}

