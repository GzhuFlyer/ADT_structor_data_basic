/*
 * @Author: gzhuflyer 
 * @Date: 2019-09-03 06:53:49 
 * @Last Modified by: gzhuflyer
 * @Last Modified time: 2019-09-04 18:14:24
 */

//使用二叉搜索树

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "tree/tree.h"

char menu(void);
void addpet(Tree * pt);
void droppet(Tree *pt);
void showpets(const Tree * pt);
void findpet(const Tree * pt);
void printitem(Item item);
void uppercase(char * str);

int main(void)
{
    Tree pets;
    char choice;

    InitializeTree(&pets);
    while ((choice = menu()) != 'q')
    {
        switch(choice)
        {
            case 'a':addpet(&pets);
                    break;
            case 'l':showpets(&pets);
                    break;
            case 'f':findpet(&pets);
                    break;
            case 'n':printf("%d 只宠物在广大飞鸟俱乐部里面\n",\
                            TreeItemCount(&pets));
                    break;
            case 'd':droppet(&pets);
                    break;
            default : puts("Switching error");
        }
    }
    DeleteAll(&pets);
    puts("退出程序，再见！");
    return 0;
    
}

char menu(void)
{
    int ch;
    puts("\n广大飞鸟宠物俱乐部成员项目");
    puts("请根据下列操作选项输入相对应的字母");
    puts("a)添加一只宠物      1)显示宠物清单");
    puts("n)显示宠物数量      f)查找宠物");
    puts("d)删除一只宠物      q)停止操作");
    while( (ch = getchar()) != EOF)    
    {
        while (getchar() != '\n')   //丢弃输入行的剩余部分
            continue;
        ch = tolower(ch);
        //strchr函数会在字符串中查找匹配的字符并返回匹配到的第一个字符
        //如果没有匹配到任何字符，将返回NULL
        if(strchr("alrfndq",ch) == NULL)
            puts("请输在字母 a,l,f,n,d,q 中选择一个进行输入 ");
        else 
            break;        
    }
    if(ch == EOF)   //令EOF导致程序退出
        ch = 'q';
    return ch;
}   

void addpet(Tree * pt)
{
    Item temp;

    if(TreeIsFull(pt))
    puts("俱乐部里面没有房间了！");
    else
    {
        puts("请输入宠物的名字：");
        fgets(temp.petname,sizeof(temp.petname),stdin);
        puts("请输入宠物的类别：");
        fgets(temp.petkind,sizeof(temp.petkind),stdin);
        uppercase(temp.petname);
        uppercase(temp.petkind);
        AddItem(&temp,pt);
    }
}

void showpets(const Tree * pt)
{
    if(TreeIsEmpty(pt))
        puts("俱乐部里面没有任何宠物名单\n");
    else 
        Traverse(pt,printitem); //回调函数，将函数名作为参数
}

void printitem(Item item)
{
    printf("宠物名字: %-19s 种类：%-19s\n",item.petname,\
            item.petkind);
}

void findpet(const Tree * pt)
{
    Item temp;
    if(TreeIsEmpty(pt))
    {
        puts("俱乐部里面没有任何宠物名单");
        return;
    }
    puts("请输入你想要查找的宠物名称：");
    fgets(temp.petname,sizeof(temp.petname),stdin);
    puts("请输入你想要查找的宠物种类：");
    fgets(temp.petkind,sizeof(temp.petkind),stdin);
    uppercase(temp.petname);
    uppercase(temp.petkind);
    printf("名字是%s种类为%s的宠物",temp.petname,temp.petkind);
    if(InTree(&temp,pt))
        printf("是俱乐部里面的成员\n");
    else 
        printf("不是里面的成员\n");
}

void droppet(Tree * pt)
{
    Item temp;

    if(TreeIsEmpty(pt))
    {
        puts("俱乐部里面没有任何宠物名单");
        return;
    }
    //使用fgets函数时候，通过stdin获取到字符串会包含有回车符号在字符串里面。
    //暂时没有想去改变。
    puts("请输入你想删除的宠物名字：");
    fgets(temp.petname,sizeof(temp.petname),stdin);
    puts("请输入你想删除的宠物的种类");
    fgets(temp.petkind,sizeof(temp.petkind),stdin);
    uppercase(temp.petname);
    uppercase(temp.petkind);
    printf("名字是%s种类为%s的宠物",temp.petname,temp.petkind);
    if(DeleteItem(&temp,pt))
        printf("已经从俱乐部名单里面删除了\n");
    else 
        printf("不是俱乐部的成员. \n");
}
//将字符串里面的字符全部转换成大写字母
void uppercase(char * str)
{
    while(*str)
    {
        *str = toupper(*str);
        str++;
    }
}

