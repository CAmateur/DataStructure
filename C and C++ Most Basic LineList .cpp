#include<stdio.h>
#include<stdlib.h>

#define MaxSize 10
#define ElemType int

struct _LineList
{
	ElemType data[MaxSize];
	int length;

}SqList;


void InitList(_LineList &L)
{
	for (int i = 0; i < MaxSize; i++)
		L.data[i] = 0;   //将所有数据元素设置为默认初始值
	L.length = 0;			//顺序表初始长度为0
}


void DestoryList(_LineList &L)
{
	for (int i = 0; i < L.length; i++)
		L.data[i] = 0;   //将所有数据元素设置为默认初始值
	L.length = 0;		//顺序表初始长度为0

}

bool ListInsert(_LineList &L, int i, ElemType e)
{
	//提高代码的健壮性
	if (L.length >= MaxSize)	//数据长度不能溢出
		return false;
	if (i <= 0 || i > L.length+1)	//插入的位置不能越界
		return false;

	for (int z = L.length; z >= i; z--)
		L.data[z] = L.data[z - 1];
	L.data[i - 1] = e;
	L.length++;
	return true;
}

bool ListDelete(_LineList &L, int i, ElemType &e)
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


int LocateElem(_LineList L, ElemType e)
{

	for (int i = 0; i < L.length; i++)
		if (L.data[i] == e)
			return i + 1;
	return -1;		//函数返回值为-1代表找不到
}

ElemType GetElem(_LineList L, int i)
{
	//提高代码健壮性
	if (i <= 0 || i >= L.length + 1)
		return ElemType(0);
	return L.data[i - 1];
}


int Length(_LineList L)
{
	return L.length;
}

void PrintList(_LineList L)
{
	for (int i = 0; i < L.length; i++)
		printf("%d ", L.data[i]);
	printf("\n");
}

bool Empty(_LineList L)
{
	if (L.length == 0)
		return true;
	return false;
}

int main()
{
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
	for(int i=1;i<=MaxSize;i++)
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