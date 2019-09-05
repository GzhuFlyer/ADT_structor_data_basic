/*
 * @Author: gzhuflyer 
 * @Date: 2019-09-03 18:40:11 
 * @Last Modified by: gzhuflyer
 * @Last Modified time: 2019-09-04 18:15:02
 */

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "tree.h"

//局部数据类型
typedef struct pair
{
    Node * parent;
    Node * child;
}Pair;

//局部函数的原型
static Node * MakeNode(const Item * pi);
static bool ToLeft(const Item * i1, const Item * i2);
static bool ToRight(const Item * i1, const Item * i2);
static void AddNode(Node * new_node, Node * root);
static void InOrder(const Node * root, void (*pfun)(Item item));
static Pair SeekItem(const Item * pi,const Tree * ptree);
static void DeleteNode(Node ** ptr);
static void DeleteAllNodes(Node * ptr);

void InitializeTree(Tree * ptree)
{
    ptree->root = NULL;
    ptree->size = 0;
}

bool TreeIsEmpty(const Tree * ptree)
{
    if(ptree->root == NULL)
        return true;
    else 
        return false;
}

bool TreeIsFull(const Tree * ptree)
{
    if(ptree->size == MAXITEMS)
        return true;
    else 
        return false;
}

int TreeItemCount(const Tree * ptree)
{
    return ptree->size;
}

/*
 * 添加节点过程：
 * 1，先判断树是否已经满叶，满叶的话退出不添加。
 * 2，使用搜索函数搜索该项目是否已经在树中，是的话不添加。
 * 3，创建一个包含该项目内容的节点，树中记录叶子节点数目的函数变量值加1。
 * 4，将该节点添加到树中。
 */
bool AddItem(const Item * pi, Tree * ptree)
{
    Node * new_node;
    if(TreeIsFull(ptree))
    {
        fprintf(stderr,"树已经满叶\n");
        return false;   //提前返回
    }
    if(SeekItem(pi,ptree).child != NULL)
    {
        fprintf(stderr,"添加宠物失败，您添加的宠物名称和类别已包含在俱乐部里面\n");
        return false;
    }
    new_node = MakeNode(pi);
    if(new_node == NULL)
    {
        fprintf(stderr,"不能生成新的节点\n");
        return false;
    }
    //成功创建一个新的节点
    ptree->size++;

    if(ptree->root == NULL)     //情况1：树为空树
        ptree->root = new_node; //新节点即为树的根节点
    else                        //情况2：树非空
        AddNode(new_node,ptree->root);     //把新节点添加到树中
    return true;                           //成功返回
}

bool InTree(const Item * pi, const Tree * ptree)
{
    return(SeekItem(pi,ptree).child == NULL)?false:true;
}

bool DeleteItem(const Item * pi, Tree * ptree)
{
    Pair look;
    look = SeekItem(pi,ptree);
    if(look.child == NULL)  
        return false;
    
    if(look.parent == NULL) //删除根项目，树上面只有一个节点
        DeleteNode(&ptree->root);
    else if(look.parent->left == look.child)
        DeleteNode(&look.parent->left);
    else 
        DeleteNode(&look.parent->right);
    ptree->size;

    return true;
}

void Traverse(const Tree * ptree,void(*pfun)(Item item))
{
    if(ptree != NULL)
        InOrder(ptree->root,pfun);
}

/*
 * 通过递归寻到树的底部
 * 在树的底部添加项目节点
 */
static void  AddNode(Node * new_node, Node * root)
{
    //新节点new_node->item字符比root->item的小，因此将他复制到树的左边
    if(ToLeft(&new_node->item,&root->item))
    {
        if(root->left == NULL)  //空子树
            root->left = new_node;  //因此把节点添加到此处
        else 
            AddNode(new_node,root->left);   //否则处理该子树ls
    }
    else if(ToRight(&new_node->item,&root->item)) 
    {
        if(root->right == NULL)
            root->right = new_node;
        else 
            AddNode(new_node,root->right);
    }
    else    //不应含有相同节点的项目
    {
        fprintf(stderr,"在函数AddNode中出现错误，退出操作!");
        exit(1);
    }
}

static bool ToLeft(const Item * i1,const Item * i2)
{
    int comp1;
    
    if((comp1 = strcmp(i1->petname,i2->petname)) < 0)
        return true;
    else if(comp1 == 0 && strcmp(i1->petkind,i2->petkind) < 0)
        return true;
    else 
        return false;
}

static bool ToRight(const Item * i1, const Item * i2)
{
    int comp1;
    if((comp1 = strcmp(i1->petname,i2->petname)) > 0)
        return true;
    else if(comp1 == 0 && strcmp(i1->petkind,i2->petkind) > 0)
        return true;
    else 
        return false;
}

/*
 *  通过给定的项目Item
 *  为它申请内存并且生成一个新的节点
 */
static Node * MakeNode(const Item * pi)
{
    Node * new_node;

    new_node = (Node*) malloc (sizeof(Node));
    if(new_node != NULL)
    {
        new_node->item = *pi;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

/*
 * 参数值:pi:指向要查找项目的地址
 *       ptree：树结构体指针
 * 返回值：返回一个包含两个指向节点指针的结构体。
 * 作用：在树中查找该树是否有包含该项目的子节点。
 *      有的话，返回值look里面的child指向该结构体。
 *      没有的话，返回值look里面的child指向为NULL。
 * 备注：通过这个函数：
 *      可以查找项目是否在树中（废话）；
 *      在进行节点添加时候，可以先查找要添加的项目是否在树中；
 *      在删除节点的时候，可以确定节点的位置。
 *      
 */
static Pair SeekItem(const Item * pi,const Tree * ptree)
{
    Pair look;
    look.parent = NULL;
    look.child = ptree->root;

    //当look.child为NULL的时候表示该树为空
    if(look.child == NULL)
        return look;
    //通过look作为中间变量不断向树的下面进行寻找
    //当look.child为NULL的时候说明已经到达树的底部了
    while (look.child != NULL)
    {
        if(ToLeft(pi,&(look.child->item)))  //比较该项目是否在给定节点的右边
        {
            //通过下面这两行代码的赋值和while循环，起到向左遍历的效果
            look.parent = look.child;
            look.child = look.child->left;
        }
        else if(ToRight(pi,&(look.child->item)))
        {
            look.parent = look.child;
            look.child = look.child->right;
        }
        else 
            break;  //look.child是目标项目节点的地址
    }               //到这里出了循环部分代码，look.child=NULL，说明该项目不在节点上。
    return look;    //成功返回
}

static void DeleteNode(Node **ptr)
{
    //*ptr是指向目标节点的父节点指针成员的地址
    Node * temp;
    // puts((*ptr)->item.petname);
    if((*ptr)->left == NULL)        //如果树只有一个根节点，运行到这里根节点的左右字数都为空，下面这段代码运行完就结束了。
    {
        temp = *ptr;
        *ptr = (*ptr)->right;
        free(temp);
    }
    else if((*ptr)->right == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->left; 
        free(temp);
    }
    else
    {
        //找到右子树的依附位置
        for(temp = (*ptr)->left;temp->right != NULL;\
                    temp=temp->right)
            continue;
        temp->right = (*ptr)->right;
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }  
}
//使用递归逐个进行删除操作。
static void DeleteAllNodes(Node * root)
{
    Node * pright;
    if(root != NULL)
    {
        pright = root->right;
        DeleteAllNodes(root->left);
        free(root);
        DeleteAllNodes(pright);
    }
}

void DeleteAll(Tree * ptree)
{
    if(ptree != NULL)
        DeleteAllNodes(ptree->root);
    ptree->root = NULL;
    ptree->size = 0;
}


/*
 * 二叉树特点：左节点中的项目是父节点中项目的前序项
 *           右节点中的项目是父节点中项目的后续项
 * 遍历思路：从树根向左开始寻找最底部的节点，显示该节点(其左右指向为NULL)
 *         然后再显示其父亲节点，再显示其兄弟节点，以此类推！ 
 */
static void InOrder(const Node * root,void(*pfun)(Item item))
{
    if(root != NULL)
    {
        InOrder(root->left,pfun);   
        (*pfun)(root->item);    
        InOrder(root->right,pfun);
    }
}
