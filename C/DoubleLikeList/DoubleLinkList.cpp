#pragma once
#include<stdio.h>
#include<stdlib.h>
#define ElemType int
typedef struct _DNode
{
	ElemType data;
	struct _DNode *prior, *next;
}DNode, *DLinkList;

bool InitDLinkList(DLinkList &L)
{
	L = (DNode *)malloc(sizeof(DNode));	//分配一个头节点
	if (L == NULL)						//内存不足，分配失败
		return false;
	L->prior = NULL;					//头节点的prior永远指向NULL
	L->next = NULL;						//头节点之后暂时还没有结点
	return true;

}

bool InsertNextDNode(DNode *p, DNode *s)
{
	if (p == NULL || s == NULL)		//非法参数
		return false;

	s->next = p->next;

	if (p->next != NULL)			//如果p结点有后继结点
		p->next->prior = s;

	s->prior = p;
	p->next = s;
	return true;
}
//产出p结点的后继结点
bool DeleteNextDNode(DNode *p)
{
	if (p == NULL)			//参数非法
		return false;
	DNode *q = p->next;
	if (q == NULL)
		return false;		//没有后继结点

	p->next = q->next;
	if (q->next != NULL)
		q->next->prior = p;
	free(q);
	return true;
}

void DestoryList(DLinkList &L)
{
	//循环释放各个数据结点
	while (L->next != NULL)
		DeleteNextDNode(L);	//从头结点开始删除
	free(L);				//释放头节点
	L = NULL;				//头指针指向NULL
}

//遍历数据
void ErgodicList(DLinkList &L)
{
	DNode *p = L;
	int i = 0;
	while (p->next != NULL)	//跳过头节点
	{
		//处理数据的逻辑代码
		i++;
		p = p->next;
	}
}