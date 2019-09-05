/*
 * @作者: www.gzhuflyer.top 
 * @日期: 2019-08-31 20:29:59  
 */

#include<stdio.h>
#include "queue/queue.h"

// #define MAIN 1

int main(void) 
{
    Queue line; //定义一个队列，后面将对该队列进行添加，删除
    Item temp;  //定义一个临时变量
    char ch;    //用于接受输入字符串

    InitializeQueue(&line);      
    puts("进行队列接口的测试操作，键入字符 a 用于添加一个值");
    puts("键入字符 d 用于删除一个值，键入字符 q 用于停止测试操作");
    /*
     *说明:此处存在bug,当终端输入是字符串而不是字符的时候，程序并不能检查出来，
     *	   下面这行代码获取到的是输入的第一个字符，键盘输入的数据将被放入缓存中，
     *	   下次调用getchar()函数的时候将获取到之前键盘输入的缓冲数据。
     * */
    while( (ch = getchar()) != 'q')	
    {
        setbuf(stdin, NULL);    /*清空缓冲区*/
        //如果从终端上输入的字符不是 a 或者 d,将跳过continue后面的操作
        if(ch != 'a' && ch !='d')
            continue;   
        if(ch == 'a')   
        {
            //下面这部分代码将对队列进行添加操作
            printf("请输入一个需要添加到队列里面的整数\n");
            scanf("%d",&temp);
            if(!QueueIsFull(&line))
            {
                printf("正在将整数 %d 添加到队列里面\n",temp);
                EnQueue(temp,&line);
            }else
            {
                puts("队列已经满了");
            }
        }else  
        {
            //下面这部分代码将对队列进行删除操作
            if(QueueIsEmpty(&line))
                puts("队列是空的，没有什么东西可以删除\n");
            else
            {
                //队列里面要被删除的值将会被复制到temp变量里面
                DeQueue(&temp,&line);
                // delete_from_rear(&temp,&line);
                printf("已将数值 %d 从队列中移除\n",temp);
            }
        }
        
        printf("队列里面的节点数量为 %d\n",QueueItemCount(&line));
        puts("键入字符 a 进行队列添加操作，字符 d 用来进行队列删除操作，字符 q 将退出程序\n");
    }

    EmptyTheQueue(&line);
    puts("程序运行结束\n");

    return 0;
}
