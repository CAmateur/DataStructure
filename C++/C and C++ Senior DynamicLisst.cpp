//类模板实现方法必须和类创建的地方一致
//第一个不能为默认值

//待解决的问题：
//1、类型的判断还不完善
//2、待实现重载


#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include"MyException.h"
using namespace std;

#define InitSize 10		//顺序表的初始长度

template<typename T>
class LineList
{


public:
	LineList(int Size);
	LineList();
	~LineList();
	bool ListInsert(int i, T e);
	bool ListDelete(int i, T &e);
	bool Empty();
	bool IncreaseSize(int i);
	int LocateElem(T e);
	int Length();
	int GetElem(int i);
	void PrintList();
	int maxSize();
private:
	T *data = NULL;		//指示动态分配数组的指针
	int MaxSize;		//顺序表的最大容量
	int length;
};


template<typename T>
LineList<T>::LineList(int Size) :length(0), MaxSize(Size)
{
	//用malloc 函数申请一片连续的储存空间
	data = (T *)malloc(Size * sizeof(T));
	memset(data, 0, Size * sizeof(T));

}
template<typename T>
LineList<T>::LineList() :length(0), MaxSize(InitSize)
{
	//用malloc 函数申请一片连续的储存空间
	data = (T *)malloc(InitSize * sizeof(T));
	memset(data, 0, InitSize * sizeof(T));

}

template<typename T>
LineList<T>::~LineList()
{
	free(data);
}

template<typename T>
bool LineList<T>::ListInsert(int i, T e)
{

	//提高代码的健壮性
	if (length >= MaxSize)	//数据长度不能溢出
		return false;
	if (i <= 0 || i > length + 1)	//插入的位置不能越界
		return false;

	for (int z = length; z >= i; z--)
		data[z] = data[z - 1];
	data[i - 1] = e;
	length++;
	return true;

}
template<typename T>
bool LineList<T>::ListDelete(int i, T & e)
{
	//提高代码的健壮性
	if (length == 0)	//数据长度不能溢出
		return false;
	if (i <= 0 || i > length)	//删除的位置不能越界
		return false;
	e = data[i - 1];
	for (int z = i; z < length; z++)
		data[z - 1] = data[z];
	length--;
	return true;
}
template<typename T>
int LineList<T>::LocateElem(T e)
{

	for (int i = 0; i < length; i++)
		if (data[i] == e)
			return i + 1;
	return 0;		//函数返回值为0代表找不到
}
template<typename T>
int LineList<T>::GetElem(int i)
{
	//提高代码健壮性
	if (i <= 0 || i >= length + 1)
		throw MyException("GetElem(" + std::to_string(i) + ")填写的范围不正确!");
	return  data[i - 1];
}
template<typename T>
int LineList<T>::Length()
{
	return  length;
}

template<typename T>
void LineList<T>::PrintList()
{
	for (int i = 0; i < length; i++)
		printf("%d ", data[i]);
	printf("\n");
}

template<typename T>
int LineList<T>::maxSize()
{
	return MaxSize;
}
template<typename T>
bool LineList<T>::Empty()
{
	if (length == 0)
		return true;
	return false;
}

template<typename T>
bool LineList<T>::IncreaseSize(int i)
{
	T *p = data;	//暂存原来的指针
	data = (T *)malloc((i + MaxSize) * sizeof(T));

	if (data == NULL)		//增加代码的健壮性
	{
		data = p;			//如果申请内存失败恢复原来的状态
		return false;
	}

	MaxSize += i;

	for (int z = 0; z < MaxSize; z++)
		data[z] = 0;		//将申请的所有内存值初始化为0

	for (int z = 0; z < length; z++)	//将原来的数据复制到新内存中
		data[z] = p[z];

	free(p);
	return true;
}