//类模板实现方法必须和类创建的地方一致
//第一个不能为默认值

#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<memory>
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


	//深拷贝构造函数
	LineList(LineList<T> &rhs);
	//移动拷贝构造函数
	LineList(LineList<T> &&rhs);
	//深拷贝赋值构造函数
	LineList<T> & operator=(LineList<T> &rhs);
	//移动赋值函数
	LineList<T> & operator=(LineList<T> &&rhs);

	friend ostream& operator<<(ostream &os, LineList<T> &rhs)
	{
		auto p = rhs.data.get();
		for (int i = 0; i < rhs.length; i++)
			os << p[i] + " ";
		return os;
	}

	bool ListInsert(int i, T e);
	bool ListDelete(int i, T &e);
	bool Empty();
	bool IncreaseSize(int i);
	int LocateElem(T e);
	int GetLength();
	int GetElem(int i);
	void PrintList();
	int GetMaxSize();
private:
	//T *data = NULL;		//普通---指示动态分配数组的指针
	std::unique_ptr<T> data;	//智能指针---指示动态分配数组的指针
	int MaxSize;		//顺序表的最大容量
	int length;
};



template<typename T>
LineList<T>::LineList(LineList<T> &rhs)
{
	printf("深拷贝构造函数\n");
	this->data.reset((T *)malloc(rhs.GetMaxSize() * sizeof(T)));
	this->length = rhs.length;
	this->MaxSize = rhs.MaxSize;


	memset(this->data.get(), 0, this->MaxSize * sizeof(T));

	memcpy(this->data.get(), rhs.data.get(), this->length * sizeof(T));
}


template<typename T>
LineList<T>::LineList(LineList<T> &&rhs)
{
	printf("移动构造函数\n");

	this->data = move(rhs.data);
	this->length = rhs.length;
	this->MaxSize = rhs.MaxSize;
	rhs.length = 0;
	rhs.MaxSize = 0;

}



template<typename T>
inline LineList<T> & LineList<T>::operator=(LineList<T> &rhs)
{
	printf("赋值重载=\n");
	if (this == &rhs)
	{
		return *this;
	}
	this->data.reset((T *)malloc(rhs.GetMaxSize() * sizeof(T)));
	this->length = rhs.length;
	this->MaxSize = rhs.MaxSize;


	memset(this->data.get(), 0, this->MaxSize * sizeof(T));

	memcpy(this->data.get(), rhs.data.get(), this->length * sizeof(T));
	return *this;
}



template<typename T>
inline LineList<T> & LineList<T>::operator=(LineList<T> && rhs)
{
	printf("移动重载=\n");
	if (this == &rhs)
	{
		return *this;
	}
	this->data = move(rhs.data);
	this->length = rhs.length;
	this->MaxSize = rhs.MaxSize;
	rhs.length = 0;
	rhs.MaxSize = 0;
	return *this;
}



template<typename T>
LineList<T>::LineList(int Size) :length(0), MaxSize(Size)
{
	//用malloc 函数申请一片连续的储存空间
	data.reset((T *)malloc(Size * sizeof(T)));//智能指针---指示动态分配数组的指针
	memset(data.get(), 0, Size * sizeof(T));

}
template<typename T>
LineList<T>::LineList() :length(0), MaxSize(InitSize)
{
	//用malloc 函数申请一片连续的储存空间
	data.reset((T *)malloc(InitSize * sizeof(T)));//智能指针---指示动态分配数组的指针
	memset(data.get(), 0, InitSize * sizeof(T));

}

template<typename T>
LineList<T>::~LineList()
{

}

template<typename T>
bool LineList<T>::ListInsert(int i, T e)
{

	//提高代码的健壮性
	if (length >= MaxSize)	//数据长度不能溢出
		return false;
	if (i <= 0 || i > length + 1)	//插入的位置不能越界
		return false;

	auto pData = data.get();
	for (int z = length; z >= i; z--)
		pData[z] = pData[z - 1];
	pData[i - 1] = e;
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
	auto pData = data.get();
	e = pData[i - 1];
	for (int z = i; z < length; z++)
		pData[z - 1] = pData[z];
	length--;
	return true;
}
template<typename T>
int LineList<T>::LocateElem(T e)
{
	auto pData = data.get();
	for (int i = 0; i < length; i++)
		if (pData[i] == e)
			return i + 1;
	return 0;		//函数返回值为0代表找不到
}
template<typename T>
int LineList<T>::GetElem(int i)
{
	//提高代码健壮性
	if (i <= 0 || i >= length + 1)
		throw MyException("GetElem(" + std::to_string(i) + ")填写的范围不正确!");
	return  data.get()[i - 1];
}
template<typename T>
int LineList<T>::GetLength()
{
	return  length;
}

template<typename T>
void LineList<T>::PrintList()
{
	auto pData = data.get();
	for (int i = 0; i < length; i++)
		printf("%d ", pData[i]);
	printf("\n");
}

template<typename T>
int LineList<T>::GetMaxSize()
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
	unique_ptr<T> p(move(data));	//暂存原来的指针

	data.reset((T *)malloc((i + MaxSize) * sizeof(T)));


	if (data == NULL)		//增加代码的健壮性
	{
		data = move(p);			//恢复原来的指针
		return false;
	}

	MaxSize += i;

	memset(data.get(), 0, MaxSize * sizeof(T));
	memcpy(data.get(), p.get(), length * sizeof(T));//将原来的数据复制到新内存中

	return true;
}