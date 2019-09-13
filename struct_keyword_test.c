#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	char name[20];
	int age;
	struct node * next;
}Node;

void test(int i)
{
	static int b[15];
	int a[i];
	memset(a,0,sizeof(a));
	for(int j=0; j<i; j++)
	{
		a[i] = j;
		printf("the j is %d\n",a[i]);
	}
}


int main()
{
	test(10);

	Node *a,*b;
	a = (Node*)malloc(sizeof(Node));
	a->next = NULL;
	b = a;
	printf("the address of b is %p\n",b);
	printf("the address of b->next is %p\n",b->next);
//	printf("the address of b->next->next is %p\n",b->next->next);
	
	int *p ;
//	printf("the value of p without malloc the memory is %d\n",*p);
	p = (int*) malloc (sizeof(int));
	printf("the value of p with one memory without initialize value is %d\n",*p);
	memset(p,0,sizeof(p)/sizeof(int));
	printf("the value of p is %d\n",*p);
	return 0;
}
