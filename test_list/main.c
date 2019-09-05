/*
 * @Author: gzhuflyer 
 * @Date: 2019-09-02 01:17:05 
 * @Last Modified by: gzhuflyer
 * @Last Modified time: 2019-09-02 01:17:58
 */

#include<stdio.h>
#include<stdlib.h>
#include "list/list.h"
void showmovies(Item item);

int main()
{
    List movies;
    Item temp;

    InitializeList(&movies);    //初始化操作
    if(ListIsFull(&movies))
    {
        fprintf(stderr,"内存申请失败，将退出程序!\n");
        exit(1);
    }

    //收集并存储
    puts("请输入第一部电影的标题\n");
    while(fgets(temp.title,sizeof(temp.title),stdin)!=NULL && temp.title[0] != '\n')
    {
        puts("输入电影的等级<0 - 10 >:");
        scanf("%d",&temp.rating);
        while (getchar() != '\n')
            continue;
        if(AddItem(temp,&movies) == false)
        {
            fprintf(stderr,"程序申请内存的过程中出现错误\n");
            break;
        }
        if(ListIsFull(&movies))
        {
            puts("该列表已经满了\n.");
            break;
        }
        puts("输入下一部电影的名称（输入空行将停止程序）:");
    }

    if(ListIsEmpty(&movies))
        printf("暂无数据输入\n");
    else
    {
        printf("下面将显示列表清单: \n");
        Traverse(&movies,showmovies);
    }
    printf("你总共输入了 %d 部电影 \n",ListItemCount(&movies));
    
    //清除
    EmptyTheList(&movies);
    printf("清空程序列表\n");
    return 0;
}

void showmovies(Item item)
{
    printf("电影名称: %s 等级排名:%d\n",item.title,item.rating);
}