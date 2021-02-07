#pragma once
#include<stdio.h>
#include<stdlib.h>
#define ElemType int


//带头节点的单链表

typedef struct _LNode
{
	ElemType data;
	struct _LNode *next;
}LNode, *LinkList;

//初始化一个空的单链表
bool InitList(LinkList &L)
{
	L = (LNode *)malloc(sizeof(LNode));
	if (L == NULL)
	{
		return false;	//如果L==NULL 说明内存申请失败 故反汇false;
	}
	L->next = NULL;
	return true;

}

//判断单链表是否为空

bool Empty(LinkList L)
{
	if (L->next == NULL)
		return true;
	else
		return false;
}

//在第 i 个位置插入元素e(带头节点)
bool ListInsert(LinkList &L, int i, ElemType e)
{
	if (i < 1)
	{
		return false;
	}

	LNode *p = GetElemByNode(L, i - 1);		//指针p指向当前扫描到的节点
	

	return InsertNextNode(p, e);

}


//后插操作：在p节点之后插入元素e 
bool InsertNextNode(LNode *p, ElemType e)
{

	if (p == NULL)
	{
		return false;
	}

	LNode *s = (LNode *)malloc(sizeof(LNode));

	if (s == NULL)		//内存分配失败
	{
		return false;
	}

	s->data = e;
	s->next = p->next;		//将节点s连接到p之后
	p->next = s;

	return true;
}


//前插操作：在p节点之前插入元素e
bool InsertPriorNode(LNode *p, ElemType e)
{

	if (p == NULL)
	{
		return false;
	}
	LNode *s = (LNode *)malloc(sizeof(LNode));

	if (s == NULL)		//内存分配失败
	{
		return false;
	}
	s->next = p->next;		//将节点s连接到p之后
	p->next = s;

	s->data = p->data;		//将p中元素复制到s中
	p->data = e;			//p中元素覆盖为e
	return true;

}

//在第 i 个位置删除元素e(带头节点)
bool ListDelete(LinkList &L, int i, ElemType &e)
{
	if (i < 1)
	{
		return false;
	}

	LNode *p = GetElemByNode(L, i - 1);		//指针p指向当前扫描到的节点


	if (p == NULL)		//i值不合法
	{
		return false;
	}
	if (p->next == NULL)	//第i-1个结点之后已无其他结点
	{
		return false;
	}

	LNode *q = p->next;		//令q指向被删除结点
	e = q->data;			//用e返回元素的值
	p->next = q->next;		//将*q结点从链中断开
	free(q);				//释放结点的储存空间
	return true;

}


bool DeleteNode(LNode *p)
{
	if (p == NULL)
	{
		return false;
	}

	LNode *q = p->next;
	p->data = p->next->data;
	p->next = q->next;
	free(q);
	return true;

}


//按位查找，返回第i个结点(带头结点)
LNode *GetElemByNode(LinkList &L, int i)
{
	if (i < 0)
	{
		return NULL;
	}
	LNode *p;		//指针p指向当前扫描到的节点
	int j = 0;		//当前p指向的是第几个节点
	p = L;			//L指向头节点，头节点是第0个节点(不存数据)
	while (p != NULL && j < i)	//循环找到第i个节点
	{
		p = p->next;
		j++;
	}

	return p;

}


//按值查找，找到数据域==e的结点
LNode * GetElemByValue(LinkList &L, ElemType e)
{
	
	LNode *p = L->next;		
	//从第1个结点开始查找数据域为e的结点
	while (p != NULL && p->data!= e)	
	{
		p = p->next;
	}

	return p;	//找到后返回该结点指针，否则返回NULL

}

int Length(LinkList L)
{
	int len = 0;
	LNode *p = L;
	while (p->next!=NULL)
	{
		p = p->next;
		len++;
	}
	return len;
}




LinkList List_TailInsert(LinkList &L)			//正向建立单链表
{
	int x;										//设ElemType为整数型
	L = (LinkList)malloc(sizeof(LNode));		//建立头结点
	LNode *s, *r = L;								//r为表尾指针
	scanf("%d", &x);							//输入节点的值
	while (x != 9999)								//输入9999表示结束
	{
		s = (LNode *)malloc(sizeof(LNode));
		r->data = x;
		r->next = s;
		r = s;									//r指向新的表尾结点
		scanf("%d", &x);
	}
	r->next = NULL;								//尾结点指针置空
	return L;

}


LinkList List_HeadInsert(LinkList &L)			//逆向建立单链表
{
	int x;
	LNode *s;
	L = (LNode *)malloc(sizeof(LNode));			//创建头节点
	L->next = NULL;								//初始为空链表
	scanf("%d", &x);							//输入节点的值
	while (x!=9999)								//输入9999表示结束
	{	
		s= (LNode *)malloc(sizeof(LNode));		//创建新节点
		s->data = x;
		s->next = L->next;
		L->next = s;
		scanf("%d", &x);						//将新节点插入表中，L为头指针
	}

	return L;

}