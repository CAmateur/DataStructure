#include<stdio.h>
#include<stdlib.h>

#define ElemType int
#define InitSize 10		//顺序表的初始长度
typedef struct
{
	ElemType *data;		//指示动态分配数组的指针
	int MaxSize;		//顺序表的最大容量
	int length;			//顺序表的当前长度
}SeqList;				//顺序表的类型定义（动态分配方式）


void InitList(SeqList &L)
{
	//用malloc 函数申请一片连续的储存空间
	L.data = (ElemType *)malloc(InitSize * sizeof(ElemType));
	for (int i = 0; i < InitSize; i++)		//等价于memset(L.data,0,InitSize);
		L.data[i] = 0;
	L.length = 0;			//数据初始长度为0
	L.MaxSize = InitSize;
}


void DestoryList(SeqList &L)
{
	for (int i = 0; i < L.length; i++)
		L.data[i] = 0;   //将所有数据元素设置为默认初始值
	L.length = 0;		//顺序表初始长度为0

}

bool ListInsert(SeqList &L, int i, ElemType e)
{
	//提高代码的健壮性
	if (L.length >= L.MaxSize)	//数据长度不能溢出
		return false;
	if (i <= 0 || i > L.length + 1)	//插入的位置不能越界
		return false;

	for (int z = L.length; z >= i; z--)
		L.data[z] = L.data[z - 1];
	L.data[i - 1] = e;
	L.length++;
	return true;
}

bool ListDelete(SeqList &L, int i, ElemType &e)
{
	//提高代码的健壮性
	if (L.length == 0)	//数据长度不能溢出
		return false;
	if (i <= 0 || i > L.length)	//删除的位置不能越界
		return false;
	e = L.data[i - 1];
	for (int z = i; z < L.length; z++)
		L.data[z - 1] = L.data[z];
	L.length--;
	return true;
}


int LocateElem(SeqList L, ElemType e)
{

	for (int i = 0; i < L.length; i++)
		if (L.data[i] == e)
			return i + 1;
	return 0;		//函数返回值为0代表找不到
}

ElemType GetElem(SeqList L, int i)
{
	//提高代码健壮性
	if (i <= 0 || i >= L.length + 1)
		return ElemType(0);
	return L.data[i - 1];
}


int Length(SeqList L)
{
	return L.length;
}

void PrintList(SeqList L)
{
	for (int i = 0; i < L.length; i++)
		printf("%d ", L.data[i]);
	printf("\n");
}

bool Empty(SeqList L)
{
	if (L.length == 0)
		return true;
	return false;
}

bool IncreaseSize(SeqList &L, int i)
{
	ElemType *p = L.data;	//暂存原来的指针
	L.data = (ElemType *)malloc((i + L.MaxSize) * sizeof(ElemType));

	if (L.data == NULL)		//增加代码的健壮性
	{
		L.data = p;			//如果申请内存失败恢复原来的状态
		return false;
	}

	L.MaxSize += i;

	for (int z = 0; z < L.MaxSize; z++)
		L.data[z] = 0;		//将申请的所有内存值初始化为0

	for (int z = 0; z < L.length; z++)	//将原来的数据复制到新内存中
		L.data[z] = p[z];

	free(p);
	return true;
}
int main()
{
	SeqList SqList;
	InitList(SqList);
	if (Empty(SqList))
		printf("List is empty.That indicate the list Init success!\n");


	if (ListInsert(SqList, 0, 1))
		printf("Inserted at place:%d,the number:%d is inserted successfully!\n", 0, 1);
	else
		printf("Inserted at place:%d,the number:%d is inserted failedly!\n", 0, 1);


	if (ListInsert(SqList, 1, 2))
		printf("Inserted at place:%d,the number:%d is inserted successfully!\n", 1, 2);
	else
		printf("Inserted at place:%d,the number:%d is inserted failedly!\n", 1, 2);




	PrintList(SqList);


	IncreaseSize(SqList, 2);

	for (int i = 1; i <= InitSize; i++)
		if (ListInsert(SqList, i, i))
			printf("Inserted at place:%d,the number:%d is inserted successfully!\n", i, i);
		else
			printf("Inserted at place:%d,the number:%d is inserted failedly!\n", i, i);

	if (ListInsert(SqList, 1, 2))
		printf("Inserted at place:%d,the number:%d is inserted successfully!\n", 1, 2);
	else
		printf("Inserted at place:%d,the number:%d is inserted failedly!\n", 1, 2);




	PrintList(SqList);
	int temp = 0;

	if (ListDelete(SqList, 1, temp))
		printf("Deleted at place:%d,the number:%d is deleted successfully!\n", 1, temp);
	else
		printf("Deleted at place:%d,the number:%d is deleted failedly!\n", 1, temp);

	PrintList(SqList);

	if (ListDelete(SqList, 9, temp))
		printf("Deleted at place:%d,the number:%d is deleted successfully!\n", 9, temp);
	else
		printf("Deleted at place:%d,the number:%d is deleted failedly!\n", 9, temp);

	PrintList(SqList);


	return 0;
}